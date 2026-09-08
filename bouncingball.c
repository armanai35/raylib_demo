#include "raylib.h"
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 600
int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Bouncing Ball");
    SetTargetFPS(60);
    Texture2D background = LoadTexture("assets/sprites/begin.png");
    Texture2D gameBackground = LoadTexture("assets/sprites/game.png");
    int page = 1;
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
            DrawText("GAME STARTED!", 270, 250, 40, DARKGREEN);
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(gameBackground);
    CloseWindow();
    return 0;
}