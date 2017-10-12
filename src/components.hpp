#pragma once

#include "vector.hpp"

#include <SFML/Graphics.hpp>

struct Position {
    Vector<double> location;
    double angle;

    sf::Transform transform() const;
};

struct Movement {
    double acceleration;
    double deceleration;
    double maxSpeed;
    Vector<double> velocity;

    void updatePosition(Position& position, double delta);
};