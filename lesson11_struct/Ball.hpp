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

    Ball(const Ball& ball) {
        center_ = ball.center_;
        velocity_ = ball.velocity_;
        color_ = ball.color_;
        radius_ = ball.radius_;
        isCollidable_ = ball.isCollidable_;
        std::cout << "Cope ctor Ball" << std::endl;
    }

    Ball(Ball&& ball) {
        center_ = ball.center_;
        velocity_ = ball.velocity_;
        color_ = ball.color_;
        radius_ = ball.radius_;
        isCollidable_ = ball.isCollidable_;
        std::cout << "Move ctor Ball" << std::endl;
    }

    Ball& operator=(const Ball& ball) {
        center_ = ball.center_;
        velocity_ = ball.velocity_;
        color_ = ball.color_;
        radius_ = ball.radius_;
        isCollidable_ = ball.isCollidable_;
        std::cout << "Cope operator Ball" << std::endl;

        return *this;
    }

    Ball& operator=(Ball&& ball) {
        center_ = ball.center_;
        velocity_ = ball.velocity_;
        color_ = ball.color_;
        radius_ = ball.radius_;   
        isCollidable_ = ball.isCollidable_;     
        std::cout << "Move operator Ball" << std::endl;

        return *this;
    }    
private:
    Point center_;
    Velocity velocity_;
    Color color_;
    double radius_;
    bool isCollidable_;

    inline friend std::istream& operator>> (std::istream& is, Ball& ball) {
        std::cout << "Ball get --------------- " << std::endl;
        is >> ball.center_ >> ball.velocity_ >> ball.color_ >> ball.radius_ >> std::boolalpha >> ball.isCollidable_;

        std::cout << "ball.isCollidable_ " << ball.isCollidable_ << std::endl;
        return is;
    }
};
