#pragma once

#include <type_traits>

template <class Container, class... Objects>
void copyToPtrContainer(Container& container, Objects&&... objects) {}

template <class Container, class First, class... Others>
void copyToPtrContainer(Container& container, First&& first, Others&&... others)
{
    container.push_back(std::make_unique<First>(std::forward<First>(first)));
    copyToPtrContainer(container, std::forward<Others>(others)...);
}


