#pragma once

#include "vector.hpp"

#include <SFML/Graphics.hpp>

template <class T>
sf::Vector2f gfxVector(const Vector<T>& vector)
{
    return {static_cast<float>(vector.x), static_cast<float>(vector.y)};
}