#include "Paddle.h"
#include "raylib.h"

Paddle::Paddle(float startX, float startY, float paddleWidth, float paddleHeight, float paddleSpeed) {
    x = startX;
    y = startY;
    width = paddleWidth;
    height = paddleHeight;
    speed = paddleSpeed;
}

void Paddle::moveLeft() {
    x -= speed;
    if (x < 0) {
        x = 0; // Prevent moving out of bounds
    }
    if (x + width > GetScreenWidth()) {
        x = GetScreenWidth() - width; // Prevent moving out of bounds
    }
}

void Paddle::moveRight() {
    x += speed;
    if (x < 0) {
        x = 0; // Prevent moving out of bounds
    }
    if (x + width > GetScreenWidth()) {
        x = GetScreenWidth() - width; // Prevent moving out of bounds
    }
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

void Paddle::draw() const {
    // Drawing logic would go here, e.g., using a graphics library
    DrawRectangle(x, y, width, height, BLUE);
}

void Paddle::reset(float startX, float startY) {
    x = startX;
    y = startY;
}