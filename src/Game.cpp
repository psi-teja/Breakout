#include "Game.h"
#include <iostream>
#include "raylib.h"

void Game::run()
{
    // Main game loop implementation
    InitWindow(800, 600, "Breakout");

    while (!WindowShouldClose())
    {
        render();
        update();
    }

    CloseWindow();
}

Game::Game() : paddle(350.0f, 550.0f, 100.0f, 20.0f, 10.0f), ball(400.0f, 300.0f, 10.0f, 0, 1.0f), currentState(PLAYING)
{
    // Initialize other game components if necessary
}

void Game::render()
{
    // Rendering logic would go here
    BeginDrawing();
    ClearBackground(RAYWHITE); // Clear screen to a light gray
    if (currentState == PLAYING) {
        paddle.draw();
        ball.draw();
    } else if (currentState == GAME_OVER) {
        DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 40) / 2, GetScreenHeight() / 2 - 40, 40, RED);
        DrawText("Press 'R' to Restart", GetScreenWidth() / 2 - MeasureText("Press 'R' to Restart", 20) / 2, GetScreenHeight() / 2 + 10, 20, BLACK);
    }
    EndDrawing();
}

void Game::update()
{
    if (currentState == PLAYING) {
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
    } else if (currentState == GAME_OVER) {
        if (IsKeyPressed(KEY_R)) {
            reset();
        }
    }
}

void Game::checkCollisions()
{
    // Collision detection and handling logic would go here
    if (ball.getY() + ball.getRadius() >= paddle.getY() &&
        ball.getX() >= paddle.getX() &&
        ball.getX() <= paddle.getX() + paddle.getWidth())
    {
        ball.reverseY();
        ball.setSpeedX((ball.getX() - (paddle.getX() + paddle.getWidth() / 2)) * 0.1f);
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

    
}

void Game::reset() {
    paddle.reset(350.0f, 550.0f);
    ball.reset(400.0f, 300.0f);
    currentState = PLAYING;
}