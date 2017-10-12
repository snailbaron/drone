#pragma once

#include "vector.hpp"
#include "screen.hpp"
#include "components.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class Actor {
public:
    virtual void update(double delta) {}
    virtual void render(Screen& screen, sf::Transform transform) const {}
};

struct Camera : Actor {
    Camera();

    void follow(std::weak_ptr<Position> actor) { positionToFollow = actor; }

    void update(double delta) override;

    std::shared_ptr<Position> position;
    std::weak_ptr<Position> positionToFollow;
};

struct Drone : Actor {
    Drone();

    void update(double delta) override;
    void render(Screen& screen, sf::Transform transform) const override;

    std::shared_ptr<Position> position;
    std::shared_ptr<Movement> movement;
};

struct Obstacle : Actor {
    void render(Screen& screen, sf::Transform transform) const override;

    std::shared_ptr<Position> position = std::make_shared<Position>();
    std::vector<Vector<double>> points;
};

struct Enemy : Actor {
    void update(double delta) override;
    void render(Screen& screen, sf::Transform transform) const override;

    std::shared_ptr<Position> position = std::make_shared<Position>();
    std::shared_ptr<Movement> movement = std::make_shared<Movement>();
};