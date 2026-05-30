#include "Ball.h"
#include "raylib.h"

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

void Ball::draw() const {
    // Drawing logic would go here, e.g., using a graphics library
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, BLACK);
}

void Ball::reset(float newX, float newY, float newSpeedX, float newSpeedY) {
    x = newX;
    y = newY;
    speedX = newSpeedX;
    speedY = newSpeedY;
}

void Ball::reverseX() {
    speedX = -speedX;
}

void Ball::reverseY() {
    speedY = -speedY;
}