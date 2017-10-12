#pragma once

#include "screen.hpp"
#include "actors.hpp"
#include "game_state.hpp"
#include "controllers.hpp"

#include <SFML/Window.hpp>

#include <vector>

class Gameplay : public GameState {
public:
    Gameplay();

    void processInputEvent(const sf::Event& event) override;
    void update(double delta) override;
    void render(Screen& screen) const override;

private:
    Camera _camera;
    std::shared_ptr<Drone> _drone;
    std::vector<std::unique_ptr<Actor>> _actors;

    std::vector<std::unique_ptr<Controller>> _controllers;
};