#include "components.hpp"

sf::Transform Position::transform() const
{
    sf::Transform transform;
    transform.translate(
        static_cast<float>(location.x), static_cast<float>(location.y));
    transform.rotate(static_cast<float>(angle));
    return transform;
}

void Movement::updatePosition(Position& position, double delta)
{
    velocity.decreaseBy(deceleration * delta);
    position.location += velocity * delta;
}