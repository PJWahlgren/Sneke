#include "view.h"
#include "raylib.h"
#include "sneke.h"
#include <stdio.h>
#include <string.h>

Board *get_board(BoardView *view) {
  unsigned long temp = 0;
  int address = view->var[0];
  memcpy(&temp, &view->_buf[address], sizeof(Board *));
  return (Board *)temp;
}

int get_integer(BoardView *view, int addr) {
  int temp = 0;
  int a = view->var[addr];
  memcpy(&temp, &view->_buf[a], sizeof(int));
  return (int)temp;
}

Color get_color(BoardView *view, int addr) {
  Color temp;
  int a = view->var[addr];
  memcpy(&temp, &view->_buf[a], sizeof(Color));
  return temp;
}
int get_window_width(BoardView *view) { return get_integer(view, 1); }
int get_window_height(BoardView *view) { return get_integer(view, 2); }
int get_square_width(BoardView *view) { return get_integer(view, 3); }
int get_square_height(BoardView *view) { return get_integer(view, 4); }
Color get_col1(BoardView *view) { return get_color(view, 5); }
Color get_col2(BoardView *view) { return get_color(view, 6); }

void print_values(BoardView *view) {
  printf("1: %p\n", get_board(view));
  printf("2: %d\n", get_window_width(view));
  printf("3: %d\n", get_window_height(view));
  printf("4: %d\n", get_square_width(view));
  printf("5: %d\n", get_square_height(view));
}
// Copies values to a buffer, addr and i should be initialized
// before and is updated inside the function.
void copy_to_buffer(BoardView *view, int *addr, const void *restrict src,
                    int *i, int size_of_type) {
  memcpy(&view->_buf[*i], src, size_of_type);
  view->var[*addr] = *i;
  (*addr)++;
  *i += size_of_type;
}
void init_view(BoardView *view, Board *board, int width, int height) {
  int i = 0;
  int addr = 0;
  unsigned long temp = (unsigned long)board;
  copy_to_buffer(view, &addr, &temp, &i, sizeof(Board *));
  copy_to_buffer(view, &addr, &width, &i, sizeof(width));
  copy_to_buffer(view, &addr, &height, &i, sizeof(height));
  int square_width = width / board->width;
  int square_height = height / board->height;
  copy_to_buffer(view, &addr, &square_width, &i, sizeof(square_width));
  copy_to_buffer(view, &addr, &square_height, &i, sizeof(square_height));
  copy_to_buffer(view, &addr, &DARKGREEN, &i, sizeof(Color));
  copy_to_buffer(view, &addr, &LIME, &i, sizeof(Color));
  view->var_initialized = (char)addr;
  view->size_of_allocation = (char)i;
}

void init_board_window(BoardView *view) {
  int width = get_window_width(view);
  int height = get_window_height(view);

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(width, height, TITLE);
}

void draw_apple(int x, int y, int sw, int sh) {
  int off_set_x = 0;
  int off_set_y = 0;
  if (sw > 10) {
    off_set_x = 10;
  }
  if (sh > 10) {
    off_set_y = 10;
  }
  DrawRectangle(x * sw + off_set_x, y * sh + off_set_y, sw - 2 * off_set_x,
                sh - 2 * off_set_y, RED);
}

void draw_board(BoardView *view) {
  // int w = get_window_width(view);
  // int h = get_window_height(view);
  int sw = get_square_width(view);
  int sh = get_square_height(view);
  Board *board = get_board(view);
  bool alternate = true;
  for (int y = 0; y < board->height; y++) {
    for (int x = 0; x < board->width; x++) {
      Color current_color = BLACK;
      Entity e = get_entity_at(board, x, y);
      switch (e) {
      case HEAD:
        current_color = WHITE;
        DrawRectangle(x * sw, y * sh, sw, sh, current_color);
        // printf("HEAD at (%d,%d)\n", x, y);
        break;
      case BODY:
        current_color = GRAY;
        DrawRectangle(x * sw, y * sh, sw, sh, current_color);
        break;
      case FRUIT:
        current_color = alternate ? get_col1(view) : get_col2(view);
        DrawRectangle(x * sw, y * sh, sw, sh, current_color);
        draw_apple(x, y, sw, sh);
        break;
      default:
        current_color = alternate ? get_col1(view) : get_col2(view);
        DrawRectangle(x * sw, y * sh, sw, sh, current_color);
      }
      alternate = !alternate;
    }
    if (!(board->width % 2)) {
      alternate = !alternate;
    }
  }
}
void draw_gui(BoardView *view, GameInfo *info) {
  int w = get_window_width(view);
  int h = get_window_height(view);
  char length[6 + 4];
  sprintf(length, "length: %d", *info->length);
  DrawText(length, 100, 100, 48, WHITE);
  if (*info->game_state == GAME_OVER) {
    Color game_over_red = {255, 0, 0, 100};
    DrawRectangle(0, 0, w, h, game_over_red);
    char *game_over_text = "Press r to restart";
    int text_length = MeasureText(game_over_text, 48);
    DrawText(game_over_text, w / 2 - text_length / 2, h / 2, 48, WHITE);
  }
}
void draw_game(BoardView *view, GameInfo *info) {
  BeginDrawing();
  ClearBackground(BLACK);
  draw_board(view);
  draw_gui(view, info);
  EndDrawing();
}
void close_view_window() { CloseWindow(); }
