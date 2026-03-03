#include "sneke.h"
#include "control_linker.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Position add_position(Position pos1, Position pos2) {
  return (Position){.x = pos1.x + pos2.x, .y = pos1.y + pos2.y};
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

Position get_random_board_pos(Board *board) {
  int x = rand() % board->width;
  int y = rand() % board->height;
  return (Position){.x = x, .y = y};
}

Entity get_entity_at(Board *board, int x, int y) {
  if (is_out_of_bounds(board, &x, &y)) {
    printf("Indexing out of bounds\n");
    exit(EXIT_FAILURE);
  }
  return board->entities[y * board->width + x];
}

uint8_t fruit_exists(Board *board, Position pos) {
  return get_entity_at(board, pos.x, pos.y) == FRUIT;
}

uint8_t snek_exists(Board *board, Position pos) {
  Entity e = get_entity_at(board, pos.x, pos.y);
  return e == HEAD || e == BODY;
}

void spawn_fruit(Board *board) {
  Position pos = get_random_board_pos(board);
  while (fruit_exists(board, pos) || snek_exists(board, pos)) {
    pos = get_random_board_pos(board);
  }
  modify_at(board, FRUIT, pos.x, pos.y);
}

Board init_board(int height, int width, int fruit_amount,
                 unsigned int random_seed) {
  Board board;
  board.height = height;
  board.width = width;
  board.fruit_amount = fruit_amount;
  srand(random_seed);
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
  for (int i = 0; i < fruit_amount; i++) {
    spawn_fruit(&board);
  }
  return board;
}

Snok init_snake(Board *board) {
  Position pos = get_random_board_pos(board);
  modify_at(board, HEAD, pos.x, pos.y);
  Snok snake = {.pos = pos, .length = 0, START};
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
// It goes in the opposite direction of
// direction to position
Position trace_the_snek(Direction dir) {
  switch (dir) {
  case NORTH:
    return direction_to_position(SOUTH);
  case WEST:
    return direction_to_position(EAST);
  case SOUTH:
    return direction_to_position(NORTH);
  case EAST:
    return direction_to_position(WEST);
  default:
    return direction_to_position(dir);
  }
}

void snek_expansion(Board *board, Snok *snake) {
  Direction *body = snake->body;
  int *length = &snake->length;
  Direction ahead_dir = *length ? body[*length - 1] : snake->dir;
  body[*length] = ahead_dir;
  (*length)++;
  printf("length: %d, dir: %d\n", *length, ahead_dir);
}
void move_snake(Board *board, Snok *snake, Direction dir) {
  Position pos = snake->pos;
  Position relative_new_pos = direction_to_position(dir);
  Position new_pos = add_position(pos, relative_new_pos);
  if (fruit_exists(board, new_pos)) {
    snek_expansion(board, snake);
    spawn_fruit(board);
  }
  // If the head can't move to the new pos it will
  // stop here.
  modify_at(board, HEAD, new_pos.x, new_pos.y);
  modify_at(board, EMPTY, pos.x, pos.y);
  snake->dir = dir;
  Direction copy = dir;
  snake->pos = new_pos;
  for (int i = 0; i < snake->length; i++) {
    copy = snake->body[i];
    snake->body[i] = dir;
    modify_at(board, BODY, pos.x, pos.y);
    pos = add_position(pos, trace_the_snek(copy));
    modify_at(board, EMPTY, pos.x, pos.y);
    dir = copy;
  }
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
