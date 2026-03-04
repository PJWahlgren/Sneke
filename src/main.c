#include "control.h"
#include "control_linker.h"
#include "sneke.h"
#include "view.h"
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#define POLL_RATE 400

Board board;
Snok snake;
BoardView view;
PollEvent event;
uint8_t is_running = 1;

void *call_game(void *arg) {
  while (is_running) {
    if (!has_any_event_happened(&event)) {
      move_snake(&board, &snake, snake.dir);
      usleep(POLL_RATE * 1000);
      continue;
    }
    if (has_event_happened(&event.HELD, NORTH)) {
      move_snake(&board, &snake, NORTH);
    }
    if (has_event_happened(&event.HELD, WEST)) {
      move_snake(&board, &snake, WEST);
    }
    if (has_event_happened(&event.HELD, SOUTH)) {
      move_snake(&board, &snake, SOUTH);
    }
    if (has_event_happened(&event.HELD, EAST)) {
      move_snake(&board, &snake, EAST);
    }
    usleep(POLL_RATE * 1000);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int height = 10;
  int width = 12;
  int random_seed = time(NULL);

  board = init_board(height, width, 2, random_seed);
  snake = init_snake(&board);
  GameInfo info = {.length = &snake.length, .game_state = &board.game_state};

  init_view(&view, &board, 1200, 1000);
  print_values(&view);
  init_board_window(&view);

  pthread_t thread;
  pthread_create(&thread, NULL, call_game, NULL);

  while (is_running) {
    event = get_event();
    if (has_event_happened(&event.PRESSED, CLOSE_GAME)) {
      is_running = 0;
    }
    if (has_event_happened(&event.PRESSED, RESTART)) {
      random_seed = time(NULL);
      board = init_board(height, width, 2, random_seed);
      snake = init_snake(&board);
    }
    draw_game(&view, &info);
  }

  close_view_window();

  return 0;
}
