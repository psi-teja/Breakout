#include "Paddle.h"

Paddle::Paddle(float startX, float startY, float paddleWidth, float paddleHeight, float paddleSpeed) {
    x = startX;
    y = startY;
    width = paddleWidth;
    height = paddleHeight;
    speed = paddleSpeed;
}

void Paddle::moveLeft() {
    x -= speed;
}

void Paddle::moveRight() {
    x += speed;
}

float Paddle::getX() const {
    return x;
}

float Paddle::getY() const {
    return y;
}

float Paddle::getWidth() const {
    return width;
}

float Paddle::getHeight() const {
    return height;
}