#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "istatistics.hpp"

namespace statistics {

  class Percentile : public IStatistics {
    public:
      // Передаем нужный перцентиль в конструктор (например, 90.0 или 95.0)
      explicit Percentile(double p) 
        : p_{p}
        , is_sorted_{false} {
        if (p_ < 0.0 || p_ > 100.0) {
          throw std::invalid_argument("Percentile must be between 0 and 100");
        }
      }

      virtual ~Percentile() = default;

      // Сохраняем данные.
      void update(double next) override {
        data_.push_back(next);
        is_sorted_ = false; // Данные изменились, нужно будет пересортировать
      }

      // Считаем перцентиль при запросе.
      double eval() const override {
        if (data_.empty()) {
          return std::numeric_limits<double>::quiet_NaN();
        }

        // Сортируем только если данные изменились с последнего вызова eval()
        if (!is_sorted_) {
          std::sort(data_.begin(), data_.end());
          is_sorted_ = true;
        }

        // Для N элементов индексы идут от 0 до N-1
        double index = (p_ / 100.0) * (data_.size() - 1);
        
        size_t lower = static_cast<size_t>(std::floor(index));
        size_t upper = static_cast<size_t>(std::ceil(index));
        
        // Вес для интерполяции (дробная часть индекса)
        double weight = index - lower;

        // Линейная интерполяция между двумя соседними значениями
        return data_[lower] * (1.0 - weight) + data_[upper] * weight;
      }

      const char* name() const override {
        // Формируем имя, например "pct90" или "pct95"
        static char name_buf[32];
        std::snprintf(name_buf, sizeof(name_buf), "pct%.0f", p_);
        return name_buf;
      }

    private:
      // Запрет копирования и перемещения
      Percentile(const Percentile&) = delete;
      Percentile& operator=(const Percentile&) = delete;
      Percentile(Percentile&&) = delete;
      Percentile& operator=(Percentile&&) = delete;

      double p_;
      mutable std::vector<double> data_; // mutable, чтобы сортировать внутри const метода eval()
      mutable bool is_sorted_;
  };

}; //  namespace statistics