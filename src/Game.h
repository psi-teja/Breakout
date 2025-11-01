#ifndef GAME_H
#define GAME_H

#include "Paddle.h"

class Game
{
private:
    Paddle paddle;

public :
    Game();
    void run();

};

#endif // !GAME_H