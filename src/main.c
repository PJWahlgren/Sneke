#include "control.h"
#include "sneke.h"
#include "view.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int height = 8;
  int width = 8;

  Board board = init_board(height, width);
  BoardView view;
  PollEvent event;

  init_view(&view, &board, 900, 800);
  print_values(&view);
  init_board_window(&view);

  while (1) {
    event = get_event();
    if (has_event_happened(&event.PRESSED, CLOSE_GAME)) {
      break;
    }
    draw_game(&view);
    printf("%b\n", event.HELD);
  }

  close_view_window();

  return 0;
}
