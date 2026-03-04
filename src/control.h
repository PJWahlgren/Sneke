#ifndef CONTROL_H
#define CONTROL_H

#include "control_linker.h"
#include <stdint.h>

typedef struct {
  uint8_t PRESSED;
  uint8_t HELD;
  uint8_t LIFT;
  int check_poll;
} PollEvent;

char has_event_happened(uint8_t *events, GameEvent event);

uint8_t has_any_event_happened(PollEvent *events);
PollEvent get_event();
#endif
