#pragma once

#include <array>
#include <memory>
#include <iostream>

#include "min.hpp"
#include "max.hpp"
#include "mean.hpp"
#include "std.hpp"

namespace statistics {

class Statistics final {
public:
  Statistics()
    : algorithms_{} {
      algorithms_[0] = std::make_unique<Min>();
      algorithms_[1] = std::make_unique<Max>();
      algorithms_[2] = std::make_unique<Mean>();
      algorithms_[3] = std::make_unique<Std>();
  }

  ~Statistics() = default;
  
	void update(double next) {
    for (auto& algorithm : algorithms_)
      algorithm->update(next);
  }

	void eval() const {
    for (auto& algorithm : algorithms_)
      std::cout << algorithm->name() << " = " << algorithm->eval() << std::endl;
  }

private:
  std::array<std::unique_ptr<IStatistics>, 4> algorithms_;
};

} // namespace statistics
