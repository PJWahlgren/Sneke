#define MAX_BOARD_SIZE 16 * 16
typedef enum Entity { Empty, Head, Snake, Fruit } Entity;

typedef struct Board {
  int height;
  int width;
  Entity board[MAX_BOARD_SIZE];
} Board;

Board init_board(int height, int width);

void modify_at(Board *board, Entity e, int x, int y);

void print_board(Board *board);
