#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define WIDTH 800
#define HEIGHT 600
#define ROWS 6
#define COLS 19
#define radius 20
#define startX 30
#define startY 50
int main(void)
{
    srand(time(NULL));
    InitWindow(WIDTH, HEIGHT, "Bouncing Ball");
    SetTargetFPS(60);
    Texture2D background = LoadTexture("assets/sprites/begin.png");
    Texture2D gameBackground = LoadTexture("assets/sprites/game.png");
    int page = 1;
    Vector2 ballPosition[ROWS][COLS];
    int ballSerial[ROWS][COLS];
    Color ballColor[ROWS][COLS];
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            ballPosition[row][col].x = startX + col * 2 * radius;
            ballPosition[row][col].y = startY + row * sqrt(3) * radius;
            if (row % 2 == 1)
            {
                ballPosition[row][col].x += radius;
            }
            int color;
            do
            {
                color = rand() % 3;
            } while ((col >= 2 && color == ballSerial[row][col - 1] && color == ballSerial[row][col - 2]) || (row >= 4 && color == ballSerial[row - 2][col] && color == ballSerial[row - 4][col]) || (row >= 2 && col < COLS - 2 && color == ballSerial[row - 2][col + 1] && color == ballSerial[row - 1][col + 2]) || (row >= 2 && col >= 2 && color == ballSerial[row - 2][col - 1] && color == ballSerial[row - 1][col - 2]));
            ballSerial[row][col] = color;
            if (color == 0)
            {
                ballColor[row][col] = RED;
            }
            else if (color == 1)
            {
                ballColor[row][col] = BLUE;
            }
            else
            {
                ballColor[row][col] = GREEN;
            }
        }
    }
    while (!WindowShouldClose())
    {
        if (page == 1)
        {
            Rectangle startButton = {300, 350, 200, 70};
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startButton))
                {
                    page = 2;
                }
            }
        }
        else if (page == 2)
        {
            Rectangle startButton = {300, 400, 200, 70};
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startButton))
                {
                    page = 3;
                }
            }
        }
        BeginDrawing();
        if (page == 3)
        {
            Rectangle source = {0, 0, gameBackground.width, gameBackground.height};
            Rectangle dest = {0, 0, WIDTH, HEIGHT};
            DrawTexturePro(gameBackground, source, dest, (Vector2){0, 0}, 0, WHITE);
        }
        else
        {
            Rectangle source = {0, 0, background.width, background.height};
            Rectangle dest = {0, 0, WIDTH, HEIGHT};
            DrawTexturePro(background, source, dest, (Vector2){0, 0}, 0, WHITE);
        }
        if (page == 1)
        {
            DrawText("BOUNCING BALL", 210, 180, 50, RED);
            Rectangle startButton = {300, 350, 200, 70};
            DrawRectangleRec(startButton, BLUE);
            DrawText("START", 355, 370, 30, WHITE);
        }
        else if (page == 2)
        {
            DrawText("INSTRUCTION", 280, 100, 40, RED);
            DrawText("Match 3 or more balls of the same color", 150, 190, 25, BLACK);
            DrawText("to destroy them in Level 1 and Level 2.", 150, 225, 25, BLACK);
            DrawText("In Level 3, match 4 or more balls", 150, 260, 25, BLACK);
            DrawText("of the same color to destroy them.", 150, 295, 25, BLACK);
            DrawText("Clear all the balls to complete the level.", 150, 330, 25, BLACK);
            Rectangle startButton = {300, 400, 200, 70};
            DrawRectangleRec(startButton, BLUE);
            DrawText("START", 355, 420, 30, WHITE);
        }
        else if (page == 3)
        {
            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    DrawCircleV(ballPosition[row][col], radius, ballColor[row][col]);
                }
            }
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(gameBackground);
    CloseWindow();
    return 0;
}
