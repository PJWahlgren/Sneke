#ifndef VIEW_H
#define VIEW_H

#include "sneke.h"
#define TITLE "sneke"

typedef struct BoardView BoardView;
void init_view(BoardView *view, Board *board, int width, int height);
void init_board_window(BoardView *view);
void draw_game(BoardView *view);
#endif
