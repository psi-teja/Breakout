#include "Game.h"
#include "raylib.h"
#include <cmath>
#include <algorithm>

void Game::run()
{
    InitWindow(ScreenWidth, ScreenHeight, "Breakout");
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        render();
        update();
    }
    CloseWindow();
}

Game::Game() : paddle(350.0f, 550.0f, 100.0f, 20.0f, 10.0f), ball(400.0f, 400.0f, 10.0f, 0, 3.0f), currentState(PLAYING)
{
    ScreenWidth = 800;
    ScreenHeight = 600;

    paddle.reset(ScreenWidth / 2.0f - paddle.getWidth() / 2.0f, ScreenHeight - 50.0f);
    ball.reset(ScreenWidth / 2.0f, ScreenHeight / 1.2f, 0.0f, 3.0f);

    initBricks();
}

void Game::initBricks()
{
    bricks.clear();
    const int rows = 15;
    const int cols = 10;
    const float spacing = 3.0f;

    // Account for (cols+1) gaps so bricks don't flush against the side walls
    const float brickWidth = (ScreenWidth - spacing * (cols + 1)) / cols;
    const float brickHeight = (ScreenHeight / 2.0f - spacing * (rows + 1)) / rows;

    Color rowColors[rows] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, MAROON, BROWN, GRAY, DARKGRAY, LIGHTGRAY, SKYBLUE, LIME, PINK, VIOLET};

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            float x = spacing + c * (brickWidth + spacing);
            float y = spacing + r * (brickHeight + spacing);
            bricks.emplace_back(x, y, brickWidth, brickHeight, rowColors[r]);
        }
    }
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (currentState == PLAYING)
    {
        paddle.draw();
        ball.draw();
        for (auto &brick : bricks)
        {
            if (!brick.destroyed())
            {
                DrawRectangle(brick.getX(), brick.getY(), brick.getWidth(), brick.getHeight(), brick.getColor());
            }
        }
    }
    else if (currentState == GAME_OVER)
    {
        DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 40) / 2, GetScreenHeight() / 2 - 40, 40, RED);
        DrawText("Press 'R' to Restart", GetScreenWidth() / 2 - MeasureText("Press 'R' to Restart", 20) / 2, GetScreenHeight() / 2 + 10, 20, BLACK);
    }
    else if (currentState == WIN)
    {
        DrawText("YOU WIN!", GetScreenWidth() / 2 - MeasureText("YOU WIN!", 40) / 2, GetScreenHeight() / 2 - 40, 40, GREEN);
        DrawText("Press 'R' to Play Again", GetScreenWidth() / 2 - MeasureText("Press 'R' to Play Again", 20) / 2, GetScreenHeight() / 2 + 10, 20, BLACK);
    }
    EndDrawing();
}

void Game::update()
{
    if (currentState == PLAYING)
    {
        if (IsKeyDown(KEY_LEFT))
            paddle.moveLeft();
        if (IsKeyDown(KEY_RIGHT))
            paddle.moveRight();

        checkCollisions();
        ball.move();
    }
    else if (currentState == GAME_OVER || currentState == WIN)
    {
        if (IsKeyPressed(KEY_R))
            reset();
    }
}

void Game::checkCollisions()
{
    Rectangle paddleRect = {paddle.getX(), paddle.getY(), paddle.getWidth(), paddle.getHeight()};

    // --- Paddle Collision ---
    if (CheckCollisionCircleRec({ball.getX(), ball.getY()}, ball.getRadius(), paddleRect))
    {
        ball.setY(paddle.getY() - ball.getRadius());

        float hitX = ball.getX() - (paddle.getX() + paddle.getWidth() / 2.0f);
        float influence = std::clamp(hitX / (paddle.getWidth() / 2.0f), -1.0f, 1.0f);
        ball.setSpeedX(influence * 5.0f);
        ball.reverseY();
    }

    // --- Wall Collisions ---
    if (ball.getY() - ball.getRadius() <= 0)
    {
        ball.reverseY();
    }
    else if (ball.getY() + ball.getRadius() >= GetScreenHeight())
    {
        currentState = GAME_OVER;
    }

    if (ball.getX() - ball.getRadius() <= 0 || ball.getX() + ball.getRadius() >= GetScreenWidth())
    {
        ball.reverseX();
    }

    // --- Brick Collisions ---
    // Snapshot position after all position corrections above
    Vector2 ballCenter = {ball.getX(), ball.getY()};
    bool anyRemaining = false;

    for (auto &brick : bricks)
    {
        if (!brick.destroyed())
        {
            anyRemaining = true;
            Rectangle brickRect = {brick.getX(), brick.getY(), brick.getWidth(), brick.getHeight()};
            if (CheckCollisionCircleRec(ballCenter, ball.getRadius(), brickRect))
            {
                brick.destroy();

                float overlapX = (ball.getRadius() + brick.getWidth() / 2.0f) - std::abs(ball.getX() - (brick.getX() + brick.getWidth() / 2.0f));
                float overlapY = (ball.getRadius() + brick.getHeight() / 2.0f) - std::abs(ball.getY() - (brick.getY() + brick.getHeight() / 2.0f));

                if (overlapX < overlapY)
                    ball.reverseX();
                else
                    ball.reverseY();

                // Check if this was the last brick
                anyRemaining = false;
                for (auto &b : bricks)
                    if (!b.destroyed()) { anyRemaining = true; break; }
                if (!anyRemaining)
                    currentState = WIN;

                break;
            }
        }
    }
}

void Game::reset()
{
    paddle.reset(ScreenWidth / 2.0f - paddle.getWidth() / 2.0f, ScreenHeight - 50.0f);
    ball.reset(ScreenWidth / 2.0f, ScreenHeight / 1.2f, 0.0f, 3.0f);
    initBricks();
    currentState = PLAYING;
}