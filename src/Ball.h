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
    void reverseX();
    void reverseY();
    void reset(float newX, float newY);
    void draw() const;
    void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
};  

#endif // !BALL_H