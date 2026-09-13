#pragma once

#include "Point.hpp"
#include "Color.hpp"

struct Particle {
  Point pos;
  Point vel;
  Color color;
  double radius;
  double lifetime;
  double age = 0;

  bool alive() const { return age < lifetime; }
};

