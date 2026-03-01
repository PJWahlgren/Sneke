#ifndef SNEKE_H
#define SNEKE_H

#define MAX_BOARD_SIZE 32 * 32
typedef enum Entity { Empty, Head, Snake, Fruit } Entity;

typedef struct Board {
  int height;
  int width;
  Entity entities[MAX_BOARD_SIZE];
} Board;

Board init_board(int height, int width);

void modify_at(Board *board, Entity e, int x, int y);

Entity get_entity_at(Board *board, int x, int y);

void print_board(Board *board);

#endif
