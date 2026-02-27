#include "sneke.h"
#include <stdio.h>
#include <stdlib.h>

Board init_board(int height, int width) {
  Board board = {height, width};
  if (height * width > MAX_BOARD_SIZE) {
    printf("Board size set to %dbut max size is %d\n", height * width,
           MAX_BOARD_SIZE);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      board.board[i * width + j] = Empty;
    }
  }
  return board;
}

char is_out_of_bounds(Board *board, int *x, int *y) {
  return *x > board->width || *x < 0 || *y > board->height || *y < 0;
}

void modify_at(Board *board, Entity e, int x, int y) {
  if (is_out_of_bounds(board, &x, &y)) {
    printf("Placement is outside of bounds");
    return;
  }
  board->board[y * board->width + x] = e;
}
// TEsting documentation thingy lol what?
void print_entity(Entity *entity) {
  char c;
  switch (*entity) {
  case Head:
    c = 'H';
    break;
  case Snake:
    c = 'S';
    break;
  case Fruit:
    c = 'F';
    break;
  case Empty:
    c = ' ';
    break;
  default:
    c = 'X';
    break;
  }
  printf("%c", c);
}
void print_board(Board *board) {
  for (int row = 0; row < board->height; row++) {
    for (int col = 0; col < board->width; col++) {
      print_entity(&board->board[row * board->width + col]);
    }
    printf("\n");
  }
}
