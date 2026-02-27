#include "raylib.h"
#include "sneke.h"

int main(int argc, char *argv[]) {
  int height = 8;
  int width = 8;
  Board board = init_board(height, width);
  modify_at(&board, Head, 1, 0);
  print_board(&board);
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(1280, 800, "Sneke");
  print_board(&board);

  Rectangle r = {0, 0, 100, 100};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (IsKeyPressed(KEY_SPACE)) {
      r.x = ((int)r.x + 100) % 500;
    }
    DrawRectangleRec(r, WHITE);
    DrawText("Sneke", 200, 200, 20, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
