#include "raylib.h"
#include "raymath.h"

#define WIDTH 800
#define HEIGHT 600

#define MAX_SPEED_X 300

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Game");
  SetTargetFPS(60);

  float ground = 3.0 * HEIGHT / 4;

  Vector2 position = {100, ground};

  float w = 60;
  float h = 60;

  Vector2 speed = Vector2Zero();

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    position = Vector2Add(position, Vector2Scale(speed, dt));

    if (IsKeyDown(KEY_RIGHT)) {
      speed.x = MAX_SPEED_X;
    } else if (IsKeyDown(KEY_LEFT)) {
      speed.x = -MAX_SPEED_X;
    } else {
      speed.x = 0;
    }

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
