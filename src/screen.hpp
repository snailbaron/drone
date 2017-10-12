#pragma once

#include "vector.hpp"

#include <SFML/Graphics.hpp>

#include <optional>

class Screen {
public:
    Screen();

    std::optional<sf::Event> pollEvent();

    Vector<int> size() const;

    void clear();
    void present();
    void close();

    sf::RenderTarget& window() { return _window; }

private:
    sf::RenderWindow _window;
};