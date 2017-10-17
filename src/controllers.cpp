#include "controllers.hpp"

#include <iostream>

void KeyboardMovementController::processInput(const sf::Event& event)
{
    auto addition = 0;
    if (event.type == sf::Event::KeyPressed) {
        addition = 1;
    } else if (event.type == sf::Event::KeyReleased) {
        addition = -1;
    } else {
        return;
    }

    switch (event.key.code) {
        case sf::Keyboard::W: _inputState.y += addition; break;
        case sf::Keyboard::S: _inputState.y -= addition; break;
        case sf::Keyboard::A: _inputState.x -= addition; break;
        case sf::Keyboard::D: _inputState.x += addition; break;
    }
}

void KeyboardMovementController::applyInput(double delta) const
{
    auto lockedMovement = movement.lock();
    if (!lockedMovement) {
        return;
    }

    lockedMovement->setInput(_inputState.cast<double>());
}

void MouseLookController::processInput(const sf::Event& event)
{
}

void MouseLookController::applyInput(double delta) const
{
}
