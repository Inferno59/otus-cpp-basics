#include "World.hpp"
#include "Painter.hpp"
#include <fstream>
#include <stdexcept>
#include <exception>
// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) 
    : topLeft{} 
    , bottomRight{} 
    , physics{} 
    , balls_{} 
    , restTime{} {
    if (worldFilePath.empty())
        throw std::runtime_error("World path is empty");

    std::ifstream stream(worldFilePath);

    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    Ball tmp_ball;

    while (stream.peek(), stream.good()) {
        stream >> tmp_ball;
        balls_.push_back(std::move(tmp_ball));
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls_) {
        ball.draw(painter);
    }

    // Вызываем отрисовку каждой пылинки
    for (const Dust& dust : dusts_) {
        dust.draw(painter);
    }    
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls_, dusts_, ticks);
}