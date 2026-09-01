#include "raylib.h"
#define WIDTH 800
#define HEIGHT 600
int main(void)
{
    bool gameover = false;
    InitWindow(WIDTH, HEIGHT, "Bouncing Ball");
    SetTargetFPS(60);
    InitAudioDevice();
    Sound hitSound = LoadSound("assets/audio/jump.wav");
    Vector2 ballPosition = {400, 300};
    Vector2 ballVelocity = {200, 150};
    float ballRadius = 20;
    float paddleWidth = 120;
    float paddleHeight = 20;
    Vector2 paddlePosition = {340, 540};
    float paddleSpeed = 500;
    int brickRow = 3;
    int brickCol = 9;
    float brickWidth = 80;
    float brickHeight = 25;
    float brickSpacing = 10;
    bool bricks[3][9];
restart:
    for (int row = 0; row < brickRow; row++)
    {
        for (int col = 0; col < brickCol; col++)
        {
            bricks[row][col] = true;
        }
    }
    int live = 3, score = 0;
    bool win = false;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (gameover && IsKeyPressed(KEY_R))
        {
            live = 3;
            gameover = false;
            ballPosition = (Vector2){400, 300};
            ballVelocity = (Vector2){200, 150};
            paddlePosition = (Vector2){340, 540};
            goto restart;
        }
        if (!gameover)
        {
            ballPosition.x += ballVelocity.x * dt;
            ballPosition.y += ballVelocity.y * dt;
            if ((ballPosition.x >= (WIDTH - ballRadius)) || (ballPosition.x <= ballRadius))
            {
                ballVelocity.x = -ballVelocity.x;
            }
            if (ballPosition.y <= ballRadius)
            {
                ballVelocity.y = -ballVelocity.y;
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                paddlePosition.x += paddleSpeed * dt;
            }
            if (IsKeyDown(KEY_LEFT))
            {
                paddlePosition.x -= paddleSpeed * dt;
            }
            if (paddlePosition.x < 0)
            {
                paddlePosition.x = 0;
            }
            if (paddlePosition.x > WIDTH - paddleWidth)
            {
                paddlePosition.x = WIDTH - paddleWidth;
            }
            if (ballPosition.y >= (HEIGHT - ballRadius))
            {
                live--;
                if (live > 0)
                {
                    ballPosition = (Vector2){400, 300};
                    ballVelocity = (Vector2){200, 150};
                }
                if (live <= 0)
                {
                    gameover = true;
                }
            }
            if (score == 27)
            {
                win = true;
                gameover = true;
            }
            Rectangle paddleRect = {
                paddlePosition.x,
                paddlePosition.y,
                paddleWidth,
                paddleHeight};
            if (CheckCollisionCircleRec(
                    ballPosition,
                    ballRadius,
                    paddleRect))
            {
                ballPosition.y = paddlePosition.y - ballRadius;
                PlaySound(hitSound);
                float hitPosition = (ballPosition.x - paddlePosition.x) / paddleWidth;
                if (hitPosition < .33)
                {
                    ballVelocity.y = -ballVelocity.y;
                    ballVelocity.x = -200;
                }
                else if (hitPosition > .66)
                {
                    ballVelocity.y = -ballVelocity.y;
                    ballVelocity.x = 200;
                }
                else
                {
                    ballVelocity.y = -ballVelocity.y;
                    ballVelocity.x = 0;
                }
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (int row = 0; row < brickRow; row++)
        {
            for (int col = 0; col < brickCol; col++)
            {
                if (bricks[row][col])
                {
                    int x = col * (brickWidth + brickSpacing);
                    int y = 80 + row * (brickHeight + brickSpacing);
                    Rectangle brickRect = {
                        col * (brickWidth + brickSpacing),
                        80 + row * (brickHeight + brickSpacing),
                        brickWidth,
                        brickHeight};
                    DrawRectangle(x, y, brickWidth, brickHeight, GREEN);
                    if (CheckCollisionCircleRec(
                            ballPosition,
                            ballRadius,
                            brickRect))
                    {
                        score += 1;
                        PlaySound(hitSound);
                        bricks[row][col] = false;
                        ballVelocity.y = -ballVelocity.y;
                    }
                }
            }
        }
        DrawCircleV(ballPosition, ballRadius, RED);
        DrawRectangle(paddlePosition.x, paddlePosition.y, paddleWidth, paddleHeight, BLUE);
        DrawText(TextFormat("Lives: %d", live), 20, 20, 30, WHITE);
        DrawText(TextFormat("Score: %d", score), 300, 20, 30, WHITE);
        if (gameover)
        {
            DrawText("GAME OVER", 275, 250, 50, RED);
            DrawText(TextFormat("Your Total Score: %d", score), 275, 300, 20, BLUE);
            DrawText("Press R to restart", 275, 320, 30, WHITE);
            if (win)
            {
                DrawText("YOU WIN🏆", 275, 200, 50, RED);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}