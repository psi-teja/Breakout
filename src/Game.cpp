#include "Game.h"
#include <iostream>

void Game::run() {
    // Main game loop implementation
    std::cout << "Game is running with paddle at position (" 
              << paddle.getX() << ", " << paddle.getY() << ")\n";
}

Game::Game() : paddle(350.0f, 550.0f, 100.0f, 20.0f, 10.0f)
, ball(400.0f, 300.0f, 10.0f, 5.0f, -5.0f) {
    // Initialize other game components if necessary
}