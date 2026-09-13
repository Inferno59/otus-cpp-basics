#pragma once
#include "Point.hpp"
#include <cmath>

class Velocity {
  public:
    inline Velocity() = default;

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

  private:
    Point vec;
};

inline std::istream& operator>>(std::istream& os, Velocity& velocity) {
    Point buf_point;
    os >> buf_point.x >> buf_point.y;
    velocity.setVector(buf_point);

    std::cout << "Velocity point get x " << buf_point.x << " y: " << buf_point.y << std::endl;
    return os;
}
