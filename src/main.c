#include "sneke.h"
#include "view.h"

int main(int argc, char *argv[]) {
  int height = 8;
  int width = 8;
  Board board = init_board(height, width);
  BoardView *view;
  init_view(view, &board, 800, 800);
  init_board_window(view);
  while (1) {
    draw_game(view);
  }
  return 0;
}
