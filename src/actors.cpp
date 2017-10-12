#include "actors.hpp"
#include "gfx_utils.hpp"

#include <algorithm>
#include <iostream>

Camera::Camera()
{
    position = std::make_shared<Position>();
}

void Camera::update(double delta)
{
    static const auto AttractionForce = 10.0;
    static const auto MaxSpeed = 10.0;

    auto target = positionToFollow.lock();
    if (!target) {
        return;
    }

    auto vectorFromActor = position->location - target->location;
    auto distanceToActor = vectorFromActor.length();
    if (distanceToActor == 0) {
        return;
    }

    auto speed = std::min(MaxSpeed, AttractionForce * distanceToActor * distanceToActor);
    auto offset = speed * delta;
    auto newDistanceToActor = std::max(0.0, distanceToActor - offset);
    auto newVectorFromActor = vectorFromActor * newDistanceToActor / distanceToActor;
    position->location = target->location + newVectorFromActor;
}

Drone::Drone()
{
    position = std::make_shared<Position>();

    movement = std::make_shared<Movement>();
    movement->maxSpeed = 4.0;

    auto fullAccelerationTime = 0.3;
    auto fullDecelerationTime = 0.2;

    movement->acceleration = movement->maxSpeed / fullAccelerationTime;
    movement->deceleration = movement->maxSpeed / fullDecelerationTime;
}

void Drone::update(double delta)
{
    movement->updatePosition(*position, delta);
}

void Drone::render(Screen& screen, sf::Transform transform) const
{
    static const auto BodyRadius = 0.2f;
    static const auto HandWidth = 0.1f;
    static const auto Color = sf::Color::White;

    transform *= position->transform();

    sf::CircleShape circle;
    circle.setPointCount(16);
    circle.setRadius(BodyRadius);
    circle.setOrigin(BodyRadius, BodyRadius);
    circle.setFillColor(Color);
    screen.window().draw(circle, transform);

    sf::RectangleShape hand;
    hand.setSize({HandWidth, BodyRadius * 1.5f});
    hand.setOrigin(HandWidth / 2, 0);
    hand.setFillColor(Color);
    screen.window().draw(hand, transform);
}

void Obstacle::render(Screen& screen, sf::Transform transform) const
{
    sf::ConvexShape shape;
    shape.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        shape.setPoint(
            i,
            {static_cast<float>(points[i].x), static_cast<float>(points[i].y)});
    }
    shape.setFillColor(sf::Color::Magenta);

    transform *= position->transform();
    screen.window().draw(shape, transform);
}

void Enemy::update(double delta)
{
}

void Enemy::render(Screen& screen, sf::Transform transform) const
{
    static const auto BodyRadius = 0.2f;
    static const auto HandWidth = 0.1f;
    static const auto Color = sf::Color::Red;

    transform *= position->transform();

    sf::CircleShape circle;
    circle.setPointCount(16);
    circle.setRadius(BodyRadius);
    circle.setOrigin(BodyRadius, BodyRadius);
    circle.setFillColor(Color);
    screen.window().draw(circle, transform);

    sf::RectangleShape hand;
    hand.setSize({HandWidth, BodyRadius * 1.5f});
    hand.setOrigin(HandWidth / 2, BodyRadius * 1.5f);
    hand.setFillColor(Color);
    screen.window().draw(hand, transform);
}
