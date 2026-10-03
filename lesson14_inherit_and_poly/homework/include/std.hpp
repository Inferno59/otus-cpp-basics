#pragma once

#include <cmath>
#include "mean.hpp"
#include "istatistics.hpp"

namespace statistics {

class Std : public IStatistics {
public:
  Std()
    : std_{0.0}
    , mean_{}
    , m2_{0.0}
    , cnt_{0} {}

  virtual ~Std() = default;

  // IStatistics
	virtual void update(double next) override {
    ++cnt_;

    double prev_mean = mean_.eval();
    mean_.update(next);

    // Вычисляем дельты для алгоритма Вильфорда
    double delta = next - prev_mean;
    double delta2 = next - mean_.eval();
    m2_ += delta * delta2;

    std_ = (cnt_ > 1) 
        ? std::sqrt(m2_ / (cnt_ - 1)) 
        : 0.0;
  }

	double eval() const override {
    return std_;
  }

	const char * name() const override {
    return "std";
  }

private:
  Std(const Std& src) = delete;
  Std& operator=(const Std& src) = delete;

  Std(Std&& src) = delete;
  Std& operator=(Std&& src) = delete;

  double std_;
  Mean mean_;
  double m2_;  // сумма квадратов отклонений
  std::size_t cnt_;
};

} //  namespace statistics
