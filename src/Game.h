#ifndef GAME_H
#define GAME_H

#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>


class Game
{
private:
    Paddle paddle;
    Ball ball;
    std::vector<Brick> bricks;
    enum GameState {
        PLAYING,
        GAME_OVER
    };
    GameState currentState;
    void reset();

public :
    Game();

    float ScreenWidth;
    float ScreenHeight;

    void run();
    void render();
    void update();
    void checkCollisions();
};

#endif // !GAME_H