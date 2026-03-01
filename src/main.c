#include "sneke.h"
#include "view.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int height = 8;
  int width = 8;
  Board board = init_board(height, width);
  BoardView view;

  // printf("total allocation: %d\n", view.size_of_allocation);
  // printf("width: %d\n", get_window_width(&view));
  init_view(&view, &board, 900, 800);
  print_values(&view);
  init_board_window(&view);
  while (1) {
    draw_game(&view);
  }
  return 0;
}
