#pragma once

#include <iostream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

    friend inline std::istream& operator>>(std::istream& os, Color& color) {
      os >> color.r >> color.g >> color.b;
      return os;
    }
  private:
    double r{};
    double g{};
    double b{};
};

