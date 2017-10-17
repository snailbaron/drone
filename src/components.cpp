#include "components.hpp"

sf::Transform Position::transform() const
{
    sf::Transform transform;
    transform.translate(
        static_cast<float>(location.x), static_cast<float>(location.y));
    transform.rotate(static_cast<float>(angle));
    return transform;
}

void Movement::setInput(const Vector<double>& input)
{
    _input = input;
    _input.normalize();
}

void Movement::updatePosition(Position& position, double delta)
{
    auto inputAcceleration = _acceleration + _deceleration;

    _velocity += _input * inputAcceleration * delta;
    _velocity.capLength(_maxSpeed);

    _velocity.decreaseBy(_deceleration * delta);
    position.location += _velocity * delta;
}