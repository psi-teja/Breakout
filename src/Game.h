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

public :
    Game();
    void run();


};

#endif // !GAME_H