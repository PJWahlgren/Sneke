#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

typedef enum : uint8_t {
  UP = 0,
  LEFT = 1,
  DOWN = 2,
  RIGHT = 3,
  CLOSE_GAME = 4,
} GameEvent;

typedef struct {
  uint8_t PRESSED;
  uint8_t HELD;
  uint8_t LIFT;
  int check_poll;
} PollEvent;

char has_event_happened(uint8_t *events, GameEvent event);

PollEvent get_event();
#endif
