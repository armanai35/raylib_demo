#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define MAX_SPEED_X 300
#define JUMP_SPEED 600
#define GRAVITY 1700

#define LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Game");
  SetTargetFPS(60);

  float ground = 3.0 * HEIGHT / 4;

  Vector2 position = {100, ground};

  float w = 60;

  Vector2 speed = Vector2Zero();
  Vector2 gravity = {0, GRAVITY};

  Texture2D idles[4];
  int spriteIndex = 0;

  for (int i = 0; i < LENGTH(idles); ++i) {
    char path[50];
    sprintf(path, "assets/sprites/player-idle-%d.png", i + 1);
    idles[i] = LoadTexture(path);
  }

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    speed = Vector2Add(speed, Vector2Scale(gravity, dt));

    position = Vector2Add(position, Vector2Scale(speed, dt));

    if (position.y > ground) {
      position.y = ground;
      speed.y = 0;
    }

    if (position.x < 0) {
      position.x = 0;
    } else if (position.x + w > WIDTH)
      position.x = WIDTH - w;

    if (IsKeyDown(KEY_RIGHT)) {
      speed.x = MAX_SPEED_X;
    } else if (IsKeyDown(KEY_LEFT)) {
      speed.x = -MAX_SPEED_X;
    } else {
      speed.x = 0;
    }

    if (IsKeyPressed(KEY_SPACE) && position.y == ground) {
      speed.y = -JUMP_SPEED;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    Rectangle groundRect = {0, ground, WIDTH, HEIGHT - ground};

    DrawTexturePro(idles[spriteIndex],
                   (Rectangle){0, 0, idles[0].width, idles[0].height},
                   (Rectangle){position.x, position.y - 96, 96, 96},
                   Vector2Zero(), 0, WHITE);

    DrawRectangleRec(groundRect, GetColor(0x014B43FF));
    DrawRectangleLinesEx(groundRect, 3, BLACK);

    EndDrawing();

    spriteIndex = (int)(GetTime() / 0.1) % LENGTH(idles);
  }

  for (int i = 0; i < LENGTH(idles); ++i) {
    UnloadTexture(idles[i]);
  }

  CloseWindow();

  return 0;
}
