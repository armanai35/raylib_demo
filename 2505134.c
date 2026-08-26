#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "My Game");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("2505134 Game", 300, 280, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}