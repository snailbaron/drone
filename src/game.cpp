#include "game.hpp"
#include "gameplay.hpp"

Game::Game()
{
    _state = std::make_unique<Gameplay>();
}

void Game::processInput()
{
    for (auto event = _screen.pollEvent(); event; event = _screen.pollEvent()) {
        if (event->type == sf::Event::Closed) {
            _finished = true;
            break;
        }
        _state->processInputEvent(*event);
    }
}

void Game::update(double delta)
{
    _state->update(delta);
}

void Game::render()
{
    _state->render(_screen);
}