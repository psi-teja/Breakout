#include "Brick.h"

Brick::Brick(float startX, float startY, float brickWidth, float brickHeight, Color color) {
    x = startX;
    y = startY;
    width = brickWidth;
    height = brickHeight;
    isDestroyed = false;
    brickColor = color;
}

float Brick::getX() const {
    return x;
}

float Brick::getY() const {
    return y;
}

float Brick::getWidth() const {
    return width;
}

float Brick::getHeight() const {
    return height;
}

bool Brick::destroyed() const {
    return isDestroyed;
}

void Brick::destroy() {
    isDestroyed = true;
}

Color Brick::getColor() {
    return brickColor;
}
