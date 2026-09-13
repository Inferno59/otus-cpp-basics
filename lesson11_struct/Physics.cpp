#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 = collisionDistance * collisionDistance;

            // Столкновение, если хотя бы один шар "твёрдый"
            if ((a->isCollibadle() || b->isCollibadle()) &&
                (distanceBetweenCenters2 < collisionDistance2)) {
                processCollision(*a, *b, distanceBetweenCenters2);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point p = ball.getCenter();
        const double r = ball.getRadius();
        Point v = ball.getVelocity().vector();

        bool wasX = false, wasY = false;

        if (p.x - r < topLeft.x) {
            p.x = topLeft.x + r;
            wasX = true;
        } else if (p.x + r > bottomRight.x) {
            p.x = bottomRight.x - r;
            wasX = true;
        }

        if (p.y - r < topLeft.y) {
            p.y = topLeft.y + r;
            wasY = true;
        } else if (p.y + r > bottomRight.y) {
            p.y = bottomRight.y - r;
            wasY = true;
        }

        // Только если шар сталкиваемый — меняем скорость
        if (ball.isCollibadle()) {
            if (wasX) v.x = -v.x;
            if (wasY) v.y = -v.y;
        }

        ball.setCenter(p);
        ball.setVelocity(v);
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * b.getMass()));
    b.setVelocity(Velocity(bV + normal * p * a.getMass()));
}
