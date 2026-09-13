#include <cmath>
#include <algorithm>
#include "Dust.hpp"

Dust::Dust(const Point& start_point, const Point& normal, double radius, double impact_speed) 
    : start_point_{start_point}
    , normal_{normal}
    , color_{0.72, 0.58, 0.48}
    , radius_{radius}
    , impact_speed_{impact_speed}
    , particles_{} {

    // Количество брызг зависит от силы удара
    int count = static_cast<int>(std::clamp(impact_speed_ * 0.5, 1.0, 4.0));

    for (int i = 0; i < count; ++i) {
        Particle p;
        p.pos      = start_point;
        p.color    = color_;
        p.radius   = radius_;
        p.lifetime = randomDouble(3000.0, 10000.0);

        double angle  = randomDouble(-1.0, 1.0);
        double speed  = randomDouble(1000.0, 10000.0) * std::min(impact_speed / 2000.0, 1.0);

        // Поворачиваем нормаль на случайный угол
        double cs = std::cos(angle), sn = std::sin(angle);
        // Выбираем случайное направление: по нормали или против
        double sign = (randomDouble(0, 1) > 0.5) ? 1.0 : -1.0;

        p.vel.x = sign * (normal.x * cs - normal.y * sn) * speed;
        p.vel.y = sign * (normal.x * sn + normal.y * cs) * speed;

        particles_.push_back(p);
    }    
}

// Вызывается каждый кадр из World::update
void Dust::update(double tick) {
    for (auto& p : particles_) {
        p.age  += tick;
        p.pos  = p.pos + p.vel * tick;
        p.vel  = p.vel * 0.96;  // торможение
        p.radius *= 0.995;      // уменьшение
    }
    // Удаляем мёртвые
    particles_.erase(
        std::remove_if(particles_.begin(), particles_.end(),
                        [](const Particle& p) { return !p.alive(); }),
        particles_.end());
}

// Вызывается из World::show
void Dust::draw(Painter& painter) const {
    for (const auto& p : particles_) {
        if (!p.alive()) continue;

        // Затухание цвета к прозрачному
        double t = 1.0 - p.age / p.lifetime;
        Color faded{
            color_.red()   * t,
            color_.green() * t,
            color_.blue()  * t
        };
        painter.draw(p.pos, p.radius, faded);
    }
}
