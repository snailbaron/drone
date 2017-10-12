#pragma once

#include "game_state.hpp"
#include "screen.hpp"

#include <memory>

class Game {
public:
    Game();

    void processInput();
    void update(double delta);
    void render();

    bool finished() const { return _finished; }

private:
    bool _finished = false;

    Screen _screen;
    std::unique_ptr<GameState> _state;
};