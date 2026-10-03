#pragma once

#include <limits>
#include "istatistics.hpp"

namespace statistics {

class Max : public IStatistics {
public:
  Max()
    : max_{std::numeric_limits<double>::min()} {}

  virtual ~Max() = default;

  // IStatistics
	virtual void update(double next) override {
    if (next > max_)
      max_ = next;
  }

	double eval() const override {
    return max_;
  }

	const char * name() const override {
    return "max";
  }

private:
  Max(const Max& src) = delete;
  Max& operator=(const Max& src) = delete;

  Max(Max&& src) = delete;
  Max& operator=(Max&& src) = delete;

  double max_;
};

} //  namespace statistics
