#ifndef BRICK_H
#define BRICK_H

#include <raylib.h>

class Brick {

private:
    float x, y;
    float width, height;
    bool isDestroyed;
    Color brickColor;

public:

    Brick(float startX, float startY, float brickWidth, float brickHeight, Color color);
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    bool destroyed() const;
    void destroy();
    Color getColor();
};

#endif // !BRICK_H