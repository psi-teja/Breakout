#include "Game.h"
#include <iostream>
#include "raylib.h"

void Game::run()
{
    // Main game loop implementation
    InitWindow(ScreenWidth, ScreenHeight, "Breakout");
    while (!WindowShouldClose())
    {
        render();
        update();
    }
    CloseWindow();
}

Game::Game() : paddle(350.0f, 550.0f, 100.0f, 20.0f, 10.0f), ball(400.0f, 400.0f, 10.0f, 0, 1.0f), currentState(PLAYING)
{
    // Initialize other game components if necessary
    // Initialize bricks layout
    bricks.clear();
    const int rows = 15;
    const int cols = 10;
    const float spacing = 3.0f;

    ScreenWidth = 800;
    ScreenHeight = 600;

    const float brickWidth = (ScreenWidth - spacing * (cols - 1)) / cols;
    const float brickHeight = (ScreenHeight / 2 - spacing * (rows - 1)) / rows;

    std::cout << "Screen Width: " << GetScreenWidth() << ", Screen Height: " << GetScreenHeight() << std::endl;
    std::cout << "Brick Width: " << brickWidth << ", Brick Height: " << brickHeight << std::endl;

    // Optional per-row colors (requires Brick to support a color setter)
    Color rowColors[rows] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, MAROON, BROWN, GRAY, DARKGRAY, LIGHTGRAY, SKYBLUE, LIME, PINK, VIOLET};

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            float x = c * (brickWidth + spacing);
            float y = r * (brickHeight + spacing);
            bricks.emplace_back(x, y, brickWidth, brickHeight, rowColors[r]);
        }
    }
}

void Game::render()
{
    // Rendering logic would go here
    BeginDrawing();
    ClearBackground(RAYWHITE); // Clear screen to a light gray
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
    EndDrawing();
}

void Game::update()
{
    if (currentState == PLAYING)
    {
        // Game update logic would go here
        if (IsKeyDown(KEY_LEFT))
        {
            paddle.moveLeft();
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            paddle.moveRight();
        }

        checkCollisions();

        ball.move();
    }
    else if (currentState == GAME_OVER)
    {
        if (IsKeyPressed(KEY_R))
        {
            reset();
        }
    }
}

void Game::checkCollisions()
{

    const float collisionBuffer = 0.1f;

    // Collision detection and handling logic would go here
    if (ball.getY() + ball.getRadius() >= paddle.getY() &&
        ball.getX() >= paddle.getX() &&
        ball.getX() <= paddle.getX() + paddle.getWidth())
    {
        ball.reverseY();
        ball.setSpeedX(paddle.getX() - paddle.previousX);
    }

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
    else if (ball.getX() + ball.getRadius() >= GetScreenWidth())
    {
        ball.reverseX();
    }

    for (auto &brick : bricks)
    {
        if (!brick.destroyed())
        {
            if (ball.getX() + ball.getRadius() >= brick.getX() &&
                ball.getX() - ball.getRadius() <= brick.getX() + brick.getWidth() &&
                ball.getY() + ball.getRadius() >= brick.getY() &&
                ball.getY() - ball.getRadius() <= brick.getY() + brick.getHeight())
            {
                brick.destroy();
                if (ball.getY() < brick.getY() || ball.getY() > brick.getY() + brick.getHeight())
                    ball.reverseY();
                else
                    ball.reverseX();
                break; // Only handle one brick collision per update
            }
        }
    }
}

void Game::reset()
{
    paddle.reset(350.0f, 550.0f);
    ball.reset(400.0f, 300.0f);
    currentState = PLAYING;
}