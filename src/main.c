#include "control.h"
#include "control_linker.h"
#include "sneke.h"
#include "view.h"

int main(int argc, char *argv[]) {
  int height = 10;
  int width = 12;

  Board board = init_board(height, width, 2, 1337);
  Snok snake = init_snake(&board);
  BoardView view;
  PollEvent event;

  init_view(&view, &board, 1200, 1000);
  print_values(&view);
  init_board_window(&view);

  while (1) {
    event = get_event();
    if (has_event_happened(&event.PRESSED, CLOSE_GAME)) {
      break;
    }
    if (has_event_happened(&event.PRESSED, NORTH)) {
      move_snake(&board, &snake, NORTH);
    }
    if (has_event_happened(&event.PRESSED, WEST)) {
      move_snake(&board, &snake, WEST);
    }
    if (has_event_happened(&event.PRESSED, SOUTH)) {
      move_snake(&board, &snake, SOUTH);
    }
    if (has_event_happened(&event.PRESSED, EAST)) {
      move_snake(&board, &snake, EAST);
    }
    if (has_event_happened(&event.PRESSED, TEST_KEY)) {
      snek_expansion(&board, &snake);
    }
    draw_game(&view);
  }

  close_view_window();

  return 0;
}
