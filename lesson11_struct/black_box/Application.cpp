#include "Application.hpp"
#include "../World.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <map>

Application::Application(const char* name)
    : window{sf::VideoMode{{1280u, 960u}},
             name,
             sf::Style::Titlebar | sf::Style::Close,
             sf::State::Windowed,
             sf::ContextSettings{0, 0, 4}},
      view({0., 0.}, 1280, 960, 0.2) {}

void Application::run(World& world) {
    time = std::chrono::system_clock::now();
    totalTime = 0.;

    while (window.isOpen()) {
        processEvents();
        updateWorld(world);
        drawWorld(world);
    }
}

void Application::processEvents() {
    // 4. SFML 3.0 uses std::optional for the event loop
    while (const auto event = window.pollEvent()) {
        
        // 5. Use type-safe event checking with is<>()
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } 
        // 6. Use getIf<>() to extract event data safely
        else if (const auto* mouseWheelScroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
            view.onZoom(mouseWheelScroll->delta);
        }
    }
}

void Application::updateWorld(World& world) {
    const auto currentTime = std::chrono::system_clock::now();
    const double delta =
        std::chrono::duration_cast<std::chrono::duration<double>>(currentTime -
                                                                  time)
            .count();
    time = currentTime;

    totalTime += delta;

    if (totalTime < 10.) {
        world.update(delta);
    }
}

void Application::drawWorld(const World& world) {
    Painter painter(window, view);
    world.show(painter);
}
