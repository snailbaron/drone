#include "screen.hpp"
#include "config.hpp"

Screen::Screen()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    _window.create(
        sf::VideoMode(conf::WindowWidth, conf::WindowHeight),
        conf::WindowTitle,
        sf::Style::Default,
        settings);
    _window.setKeyRepeatEnabled(false);
}

std::optional<sf::Event> Screen::pollEvent()
{
    sf::Event event;
    if (_window.pollEvent(event)) {
        return event;
    } else {
        return {};
    }
}

Vector<int> Screen::size() const
{
    auto gfxSize = _window.getSize();
    return {static_cast<int>(gfxSize.x), static_cast<int>(gfxSize.y)};
}

void Screen::clear()
{
    _window.clear(sf::Color::Black);
}

void Screen::present()
{
    _window.display();
}

void Screen::close()
{
    _window.close();
}