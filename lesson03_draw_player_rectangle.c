#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Game");
  SetTargetFPS(60);

  float ground = 3.0 * HEIGHT / 4;

  Vector2 position = {100, ground};

  float w = 60;
  float h = 60;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Rectangle groundRect = {0, ground, WIDTH, HEIGHT - ground};
    Rectangle player = {position.x, position.y - h, w, h};

    DrawRectangleRec(player, GetColor(0x9C2113FF));
    DrawRectangleLinesEx(player, 3, BLACK);

    DrawRectangleRec(groundRect, GetColor(0x014B43FF));
    DrawRectangleLinesEx(groundRect, 3, BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
