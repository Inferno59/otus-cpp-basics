#pragma once

#include <limits>
#include "istatistics.hpp"

namespace statistics {

class Min : public IStatistics {
public:
  Min()
    : min_{std::numeric_limits<double>::max()} {}

  virtual ~Min() = default;

  // IStatistics
	virtual void update(double next) override {
    if (next < min_)
      min_ = next;
  }

	double eval() const override {
    return min_;
  }

	const char * name() const override {
    return "min";
  }

private:
  Min(const Min& src) = delete;
  Min& operator=(const Min& src) = delete;

  Min(Min&& src) = delete;
  Min& operator=(Min&& src) = delete;

  double min_;
};

} //  namespace statistics
