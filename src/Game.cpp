#include "Game.h"
#include <iostream>
#include "raylib.h"
#include <cmath> // For std::abs in collision detection

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

    paddle.reset(ScreenWidth / 2.0f - paddle.getWidth() / 2.0f, ScreenHeight - 50.0f);
    ball.reset(ScreenWidth / 2.0f, ScreenHeight / 1.2f);

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
    // Use raylib's built-in circle-rectangle collision check for accuracy
    Rectangle paddleRect = {paddle.getX(), paddle.getY(), paddle.getWidth(), paddle.getHeight()};
    Vector2 ballCenter = {ball.getX(), ball.getY()};

    // --- Paddle Collision ---
    if (CheckCollisionCircleRec(ballCenter, ball.getRadius(), paddleRect))
    {
        // Move ball out of paddle to prevent sticking
        // We assume the ball is coming from above
        ball.setY(paddle.getY() - ball.getRadius());

        // Calculate hit position on paddle (-1 for left edge, 0 for center, 1 for right edge)
        float hitX = (ball.getX() - (paddle.getX() + paddle.getWidth() / 2.0f));
        float influence = hitX / (paddle.getWidth() / 2.0f);

        // Adjust ball's horizontal speed based on where it hit the paddle
        // This adds "spin" or control over the ball's direction
        ball.setSpeedX(influence * 5.0f); // The '5.0f' is a sensitivity factor you can tune

        // Reverse vertical direction
        ball.reverseY();
    }

    // --- Wall Collisions ---
    // Top wall
    if (ball.getY() - ball.getRadius() <= 0)
    {
        ball.reverseY();
    }
    // Bottom wall - Game Over
    else if (ball.getY() + ball.getRadius() >= GetScreenHeight())
    {
        currentState = GAME_OVER;
    }

    // Left and right walls
    if (ball.getX() - ball.getRadius() <= 0 || ball.getX() + ball.getRadius() >= GetScreenWidth())
    {
        ball.reverseX();
    }

    // --- Brick Collisions ---
    for (auto &brick : bricks)
    {
        if (!brick.destroyed())
        {
            Rectangle brickRect = {brick.getX(), brick.getY(), brick.getWidth(), brick.getHeight()};
            if (CheckCollisionCircleRec(ballCenter, ball.getRadius(), brickRect))
            {
                brick.destroy();

                // Improved bounce logic: Determine if the collision is more horizontal or vertical.
                // We calculate the overlap on each axis and bounce on the axis with the smallest overlap.
                float overlapX = (ball.getRadius() + brick.getWidth() / 2.0f) - std::abs(ball.getX() - (brick.getX() + brick.getWidth() / 2.0f));
                float overlapY = (ball.getRadius() + brick.getHeight() / 2.0f) - std::abs(ball.getY() - (brick.getY() + brick.getHeight() / 2.0f));

                if (overlapX < overlapY)
                {
                    ball.reverseX();
                }
                else
                {
                    ball.reverseY();
                }
                break; // Only handle one brick collision per update
            }
        }
    }
}

void Game::reset()
{
    paddle.reset(ScreenWidth / 2.0f - paddle.getWidth() / 2.0f, ScreenHeight - 50.0f);
    ball.reset(ScreenWidth / 2.0f, ScreenHeight / 1.2f);
    currentState = PLAYING;
}