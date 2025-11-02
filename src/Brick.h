#ifndef BRICK_H
#define BRICK_H

class Brick {

private:
    float x, y;
    float width, height;
    bool isDestroyed;
public:

    Brick(float startX, float startY, float brickWidth, float brickHeight);
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    bool destroyed() const;
    void destroy();
};

#endif // !BRICK_H