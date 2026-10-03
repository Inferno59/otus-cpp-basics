#pragma once

#include "percentile.hpp"

namespace statistics {

  class Pct95 final : public Percentile {
    public:
      Pct95() : Percentile(95.0) {}
      ~Pct95() = default;
    private:
      // Запрет копирования и перемещения
      Pct95(const Pct95&) = delete;
      Pct95& operator=(const Pct95&) = delete;
      Pct95(Pct95&&) = delete;
      Pct95& operator=(Pct95&&) = delete;    
  };

}; // namespace statistics