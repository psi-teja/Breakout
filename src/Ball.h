#ifndef BALL_H
#define BALL_H

class Ball {
private:

    float x, y;
    float radius;
    float speedX, speedY;


public:

    Ball(float startX, float startY, float ballRadius, float ballSpeedX, float ballSpeedY);
    void move();
    float getX() const;
    float getY() const;
    float getRadius() const;
};  

#endif // !BALL_H