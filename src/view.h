#ifndef VIEW_H
#define VIEW_H

#include "sneke.h"
#include <stdalign.h>
#include <stddef.h>
#define TITLE "sneke"

typedef struct {
  char var[16];
  char var_initialized;
  char size_of_allocation;
  alignas(max_align_t) char _buf[128];
} BoardView;
void print_values(BoardView *view);
void init_view(BoardView *view, Board *board, int width, int height);
void init_board_window(BoardView *view);
void draw_game(BoardView *view);
void close_view_window();
#endif
