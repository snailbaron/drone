#pragma once

#include "vector.hpp"

#include <SFML/Graphics.hpp>

struct Position {
    sf::Transform transform() const;

    Vector<double> location;
    double angle;
};

class Movement {
public:
    void updatePosition(Position& position, double delta);

    double acceleration() const { return _acceleration; }
    void setAcceleration(double acceleration) { _acceleration = acceleration; }

    double deceleration() const { return _deceleration; }
    void setDeceleration(double deceleration) { _deceleration = deceleration; }

    double maxSpeed() const { return _maxSpeed; }
    void setMaxSpeed(double maxSpeed) { _maxSpeed = maxSpeed; }

    void setInput(const Vector<double>& input);

private:
    double _acceleration;
    double _deceleration;
    double _maxSpeed;
    Vector<double> _input;
    Vector<double> _velocity;
};