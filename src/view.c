#include "view.h"
#include "raylib.h"

struct BoardView {
  Board *board;
  int view_width;
  int view_height;
  int square_width;
  int square_height;
  Color col1;
  Color col2;
};

void init_view(BoardView *view, Board *board, int width, int height) {
  view->board = board;
  view->view_width = width;
  view->view_height = height;
  view->square_width = width / board->width;
  view->square_height = height / board->height;
  view->col1 = BLUE;
  view->col2 = GRAY;
}

void init_board_window(BoardView *view) {
  InitWindow(view->view_width, view->view_height, TITLE);
}

void draw_board(BoardView *view) {
  int w = view->view_width;
  int h = view->view_height;
  int sw = view->square_width;
  int sh = view->square_height;
  bool alternate = true;
  for (int row = 0; row < view->board->height; row++) {
    for (int col = 0; col < view->board->width; col++) {
      Color current_color = alternate ? view->col1 : view->col2;
      alternate = !alternate;
      DrawRectangle(row * h * sh, col * sw, sw, sh, current_color);
    }
  }
}
void draw_game(BoardView *view) {
  BeginDrawing();
  ClearBackground(BLACK);
  draw_board(view);
  EndDrawing();
}
