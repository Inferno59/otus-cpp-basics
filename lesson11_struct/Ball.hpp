#pragma once

#include <iostream>
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    explicit Ball() = default;
    Ball(Point center, Velocity velocity, Color color, double radius);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollibadle() const;

private:
    Point center_;
    Velocity velocity_;
    Color color_;
    double radius_;
    bool isCollidable_;

    inline friend std::istream& operator>> (std::istream& is, Ball& ball) {
        is >> ball.center_ >> ball.velocity_ >> ball.color_ >> ball.radius_ >> std::boolalpha >> ball.isCollidable_;
        return is;
    }
};
