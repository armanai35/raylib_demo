#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Game");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
