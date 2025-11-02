#include "Ball.h"

Ball::Ball(float startX, float startY, float ballRadius, float ballSpeedX, float ballSpeedY) {
    x = startX;
    y = startY;
    radius = ballRadius;
    speedX = ballSpeedX;
    speedY = ballSpeedY;
}

void Ball::move() {
    x += speedX;
    y += speedY;
}

float Ball::getX() const {
    return x;
}

float Ball::getY() const {
    return y;
}

float Ball::getRadius() const {
    return radius;
}