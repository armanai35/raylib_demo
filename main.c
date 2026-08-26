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
  InitAudioDevice();
  SetTargetFPS(60);

  float ground = 3.0 * HEIGHT / 4;

  Vector2 position = {100, ground};

  float w = 60;
  bool flip = false;

  Vector2 speed = Vector2Zero();
  Vector2 gravity = {0, GRAVITY};

  Texture2D idles[4];
  Texture2D running[6];

  Texture2D *sprites = idles;
  int spriteIndex = 0;

  for (int i = 0; i < LENGTH(idles); ++i) {
    char path[50];
    sprintf(path, "assets/sprites/player-idle-%d.png", i + 1);
    idles[i] = LoadTexture(path);
  }

  for (int i = 0; i < LENGTH(running); ++i) {
    char path[50];
    sprintf(path, "assets/sprites/player-run-%d.png", i + 1);
    running[i] = LoadTexture(path);
  }

  Sound jumpSound = LoadSound("assets/audio/jump.wav");

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
      flip = false;
      sprites = running;
    } else if (IsKeyDown(KEY_LEFT)) {
      speed.x = -MAX_SPEED_X;
      flip = true;
      sprites = running;
    } else {
      speed.x = 0;
      sprites = idles;
    }

    if (IsKeyPressed(KEY_SPACE) && position.y == ground) {
      speed.y = -JUMP_SPEED;
      PlaySound(jumpSound);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    Rectangle groundRect = {0, ground, WIDTH, HEIGHT - ground};

    DrawTexturePro(sprites[spriteIndex],
                   (Rectangle){0, 0,
                               flip ? -sprites[0].width : sprites[0].width,
                               sprites[0].height},
                   (Rectangle){position.x, position.y - 96, 96, 96},
                   Vector2Zero(), 0, WHITE);

    DrawRectangleRec(groundRect, GetColor(0x014B43FF));
    DrawRectangleLinesEx(groundRect, 3, BLACK);

    EndDrawing();

    int spritesSize = 0;
    if (sprites == idles)
      spritesSize = LENGTH(idles);
    else if (sprites == running)
      spritesSize = LENGTH(running);

    spriteIndex = (int)(GetTime() / 0.1) % spritesSize;
  }

  for (int i = 0; i < LENGTH(idles); ++i) {
    UnloadTexture(idles[i]);
  }
  for (int i = 0; i < LENGTH(running); ++i) {
    UnloadTexture(running[i]);
  }

  UnloadSound(jumpSound);
  CloseAudioDevice();

  CloseWindow();

  return 0;
}
