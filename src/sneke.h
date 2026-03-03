#ifndef SNEKE_H
#define SNEKE_H
#define MAX_BOARD_SIZE 32 * 32

#include "control_linker.h"
#include <stdint.h>

typedef enum Entity { EMPTY, HEAD, BODY, FRUIT } Entity;
typedef GameEvent Direction;

typedef struct Position {
  int x, y;
} Position;

typedef struct Board {
  Entity entities[MAX_BOARD_SIZE];
  int height;
  int width;
  int fruit_amount;
  unsigned int random_seed;
} Board;

typedef struct Snok {
  Position pos;
  int length;
  Direction dir;
  Direction body[MAX_BOARD_SIZE - 1];
} Snok;

Snok init_snake(Board *board);
Board init_board(int height, int width, int fruit_amount,
                 unsigned int random_seed);
void move_snake(Board *board, Snok *snake, Direction dir);
void snek_expansion(Board *board, Snok *snake);

void modify_at(Board *board, Entity e, int x, int y);

Entity get_entity_at(Board *board, int x, int y);

void print_board(Board *board);

#endif
