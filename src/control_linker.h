#ifndef CONTROL_LINKER_H
#define CONTROL_LINKER_H

#include <stdint.h>
typedef enum : uint8_t {
  NORTH = 0,
  WEST = 1,
  SOUTH = 2,
  EAST = 3,
  START = 4, // No movement until the player has moved
  CLOSE_GAME = 5,
  RESTART = 6
} GameEvent;
#endif
