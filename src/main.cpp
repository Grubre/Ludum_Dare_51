#include "Game.hpp"

int main() {
    Game game(engine::config::window_width, engine::config::window_height);
    game.start();
    return EXIT_SUCCESS;
}
