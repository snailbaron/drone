#pragma once

#include "vector.hpp"
#include "components.hpp"

#include <SFML/Window.hpp>

#include <memory>

class Controller {
public:
    virtual void processInput(const sf::Event& event) = 0;
    virtual void applyInput(double delta) const = 0;
};

class KeyboardMovementController : public Controller {
public:
    KeyboardMovementController(std::weak_ptr<Movement> movement)
        : movement(movement)
    { }

    void processInput(const sf::Event& event);
    void applyInput(double delta) const;

private:
    std::weak_ptr<Movement> movement;
    Vector<int> _inputState;
};

class MouseLookController : public Controller {
public:
    void processInput(const sf::Event& event) override;
    void applyInput(double delta) const override;
};