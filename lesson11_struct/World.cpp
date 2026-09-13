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
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    /**
     * TODO: хорошее место для улучшения.
     * (x, y) и (vx, vy) - составные части объекта, также
     * как и (red, green, blue). Опять же, можно упростить
     * этот код, научившись читать сразу Point, Color...
     */
    Ball tmp_ball;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор
        // его скорости (vx, vy)
        // stream >> x >> y >> vx >> vy;
        // stream >> x >> y >> vx >> vy;
        // Читаем три составляющие цвета шара
        stream >> tmp_ball;

        // TODO: место для доработки.
        // Здесь не хватает самого главного - создания
        // объекта класса Ball со свойствами, прочитанными
        // выше, и его помещения в контейнер balls

        // После того как мы каким-то образом
        // сконструируем объект Ball ball;
        // добавьте его в конец контейнера вызовом
        balls_.push_back(std::move(tmp_ball));
        //balls_.emplace_back(std::move(tmp_ball));
    }

    std::cout << "End program" << std::endl;
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls_) {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
   // std::cout << "update time: " << time << std::endl;
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

    physics.update(balls_, ticks);
}