#pragma once

#include <random>
#include "Painter.hpp"
#include "Point.hpp"
#include "Particles.hpp"

class Dust {
public:
    explicit Dust() = default;
    Dust(const Point& start_point, const Point& normal, double radius, double impact_speed);

    void draw(Painter& painter) const;
    void update(double tick);
private:
    inline static constexpr int kMaxParticlesCnt = 4;

    // Простой генератор случайных чисел
    static double randomDouble(double lo, double hi) {
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<double> dist(lo, hi);
        return dist(rng);
    }

    Point start_point_;
    Point normal_;
    Color color_;
    double radius_;
    double impact_speed_;
    std::vector<Particle> particles_;
};
