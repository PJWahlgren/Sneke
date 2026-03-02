#include "sneke.h"
#include "control_linker.h"
#include <stdio.h>
#include <stdlib.h>

Board init_board(int height, int width) {
  Board board;
  board.height = height;
  board.width = width;
  if (height * width > MAX_BOARD_SIZE) {
    printf("Board size set to %d but max size is %d\n", height * width,
           MAX_BOARD_SIZE);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      board.entities[i * width + j] = EMPTY;
    }
  }
  return board;
}

Snok init_snake(Board *board, unsigned int random_seed) {
  srand(random_seed);
  int x = rand() % board->width;
  int y = rand() % board->height;
  modify_at(board, HEAD, x, y);
  Snok snake = {.pos = {.x = x, .y = y}, .length = 0, START};
  return snake;
}

Position direction_to_position(Direction dir) {
  switch (dir) {
  case NORTH:
    return (Position){.x = 0, .y = -1};
  case WEST:
    return (Position){.x = -1, .y = 0};
  case SOUTH:
    return (Position){.x = -0, .y = 1};
  case EAST:
    return (Position){.x = 1, .y = 0};
  default:
    printf("Inputed a none direction\n");
    exit(EXIT_FAILURE);
  }
}
void move_snake(Board *board, Snok *snake, Direction dir) {
  Position *old_pos = &snake->pos;
  Position relative_new_pos = direction_to_position(dir);
  Position new_pos = {.x = old_pos->x + relative_new_pos.x,
                      .y = old_pos->y + relative_new_pos.y};
  modify_at(board, EMPTY, old_pos->x, old_pos->y);
  modify_at(board, HEAD, new_pos.x, new_pos.y);
  snake->dir = dir;
  snake->pos = new_pos;
}

char is_out_of_bounds(Board *board, int *x, int *y) {
  return *x >= board->width || *x < 0 || *y >= board->height || *y < 0;
}

void modify_at(Board *board, Entity e, int x, int y) {
  if (is_out_of_bounds(board, &x, &y)) {
    printf("(%d,%d) is outside of bounds\n", x, y);
    return;
  }
  board->entities[y * board->width + x] = e;
}

Entity get_entity_at(Board *board, int x, int y) {
  if (is_out_of_bounds(board, &x, &y)) {
    printf("Indexing out of bounds\n");
    exit(EXIT_FAILURE);
  }
  return board->entities[y * board->width + x];
}
// TEsting documentation thingy lol what?
void print_entity(Entity *entity) {
  char c;
  switch (*entity) {
  case HEAD:
    c = 'H';
    break;
  case BODY:
    c = 'S';
    break;
  case FRUIT:
    c = 'F';
    break;
  case EMPTY:
    c = ' ';
    break;
  default:
    c = 'X';
    break;
  }
  printf("%c", c);
}
void print_board(Board *board) {
  for (int y = 0; y < board->height; y++) {
    for (int x = 0; x < board->width; x++) {
      print_entity(&board->entities[y * board->width + x]);
    }
    printf("\n");
  }
  for (int i = 0; i < board->width; i++) {
    printf("#");
  }
  printf("\n");
}
