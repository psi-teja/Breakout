#ifndef PADDLE_H
#define PADDLE_H

class Paddle {
private:
    float x, y;
    float width, height;
    float speed;
public:
    Paddle(float startX, float startY, float paddleWidth, float paddleHeight, float paddleSpeed);
    void moveLeft();
    void moveRight();
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
};

#endif // !PADDLE_H