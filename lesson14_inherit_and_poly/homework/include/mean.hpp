#pragma once

#include <limits>
#include <vector>
#include "istatistics.hpp"

namespace statistics {

class Mean : public IStatistics {
public:
  Mean()
    : mean_{0.0}
    , cnt_{0} {}

  virtual ~Mean() = default;

  // IStatistics
	virtual void update(double next) override {
    ++cnt_;
    // Алгоритм Вильфорда: численно устойчивый расчет среднего
    mean_ += (next - mean_) / static_cast<double>(cnt_);
  }

	double eval() const override {
    if (cnt_ == 0)
      return std::numeric_limits<double>::quiet_NaN();
    
    return mean_;
  }

	const char * name() const override {
    return "mean";
  }

private:
  Mean(const Mean& src) = delete;
  Mean& operator=(const Mean& src) = delete;

  Mean(Mean&& src) = delete;
  Mean& operator=(Mean&& src) = delete;

  double mean_;
  std::size_t cnt_;
};

} //  namespace statistics
