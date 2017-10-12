#include "game.hpp"
#include "timer.hpp"
#include "config.hpp"

int main()
{
    Game game;

    FrameTimer timer(conf::GameFps);
    while (!game.finished()) {
        game.processInput();

        auto framesPassed = timer.framesPassed();
        if (framesPassed > 0) {
            for (int i = 0; i < framesPassed; i++) {
                game.update(timer.frameDuration());
            }

            game.render();
        }
    }
}