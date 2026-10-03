#pragma once

#include "percentile.hpp"

namespace statistics {

  class Pct90 final : public Percentile {
    public:
      Pct90() : Percentile(90.0) {}
      ~Pct90() = default;
    private:
      // Запрет копирования и перемещения
      Pct90(const Pct90&) = delete;
      Pct90& operator=(const Pct90&) = delete;
      Pct90(Pct90&&) = delete;
      Pct90& operator=(Pct90&&) = delete;    
  };

}; // namespace statistics