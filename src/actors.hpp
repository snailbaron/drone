#pragma once

#include "vector.hpp"
#include "screen.hpp"
#include "components.hpp"
#include "tasks.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <iostream>

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

class MoveTo : public Task {
public:
    MoveTo(
            const Vector<double>* point,
            std::weak_ptr<Position> position,
            std::weak_ptr<Movement> movement)
        : _targetPoint(point)
        , _position(position)
        , _movement(movement)
    { }

    Status update(double) override
    {
        auto position = _position.lock();
        auto movement = _movement.lock();
        if (!position || !movement) {
            return Status::Failure;
        }

        auto vectorToTarget = *_targetPoint - position->location;
        std::cerr << vectorToTarget.length() << std::endl;

        if (vectorToTarget.length() < 0.1) {
            movement->setInput({0, 0});
            return Status::Success;
        }

        vectorToTarget.normalize();
        movement->setInput(vectorToTarget);

        return Status::Running;
    }

private:
    const Vector<double>* _targetPoint;
    std::weak_ptr<Position> _position;
    std::weak_ptr<Movement> _movement;
};

class Wait : public Task {
public:
    Wait(double seconds) : _total(seconds), _passed(0) {}

    void initialize() override
    {
        _passed = 0;
    }

    Status update(double delta) override
    {
        _passed += delta;
        if (_passed >= _total) {
            return Status::Success;
        } else {
            return Status::Running;
        }
    }

private:
    double _total;
    double _passed;
};

struct Enemy : Actor {
    Enemy();

    void update(double delta) override;
    void render(Screen& screen, sf::Transform transform) const override;

    std::shared_ptr<Position> position = std::make_shared<Position>();
    std::shared_ptr<Movement> movement = std::make_shared<Movement>();
    std::unique_ptr<Task> behavior;
};