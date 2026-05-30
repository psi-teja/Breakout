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
    void reset(float newX, float newY, float newSpeedX = 0.0f, float newSpeedY = 5.0f);
    void draw() const;
    void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
    void setY(float newY) { y = newY; }
};  

#endif // !BALL_H