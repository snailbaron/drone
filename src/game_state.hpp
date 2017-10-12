#pragma once

#include "screen.hpp"

#include <SFML/Window.hpp>

class GameState {
public:
    virtual void processInputEvent(const sf::Event& event) = 0;
    virtual void update(double delta) = 0;
    virtual void render(Screen& screen) const = 0;
};