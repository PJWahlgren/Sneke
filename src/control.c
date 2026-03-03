#include "control.h"
#include "control_linker.h"
#include "raylib.h"

#include <stdint.h>
#include <stdio.h>

#define GAME_UP KEY_W
#define GAME_LEFT KEY_A
#define GAME_DOWN KEY_S
#define GAME_RIGHT KEY_D
#define GAME_CLOSE KEY_ESCAPE

char has_event_happened(uint8_t *events, GameEvent event) {
  uint8_t tmp = 1 << event;
  uint8_t events_cpy = *events;
  events_cpy &= tmp;
  events_cpy >>= event;
  return (char)events_cpy;
}
uint8_t has_any_event_happened(PollEvent *events) {
  uint8_t tmp = 0b11111111;
  return events->HELD & tmp || events->LIFT & tmp || events->PRESSED & tmp;
}
void key_event(PollEvent *events, GameEvent event, int key) {
  if (has_any_event_happened(events)) {
    return;
  }
  uint8_t tmp = 1 << event;
  if (IsKeyPressed(key)) {
    events->PRESSED |= tmp;
  }
  if (IsKeyDown(key)) {
    events->HELD |= tmp;
  }
  if (IsKeyReleased(key)) {
    events->PRESSED &= ~tmp;
    events->HELD &= ~tmp;
    events->LIFT |= tmp;
  }
}

PollEvent get_event() {
  PollEvent new_event = {.PRESSED = 0, .HELD = 0, .LIFT = 0};
  key_event(&new_event, NORTH, GAME_UP);
  key_event(&new_event, WEST, GAME_LEFT);
  key_event(&new_event, SOUTH, GAME_DOWN);
  key_event(&new_event, EAST, GAME_RIGHT);
  key_event(&new_event, CLOSE_GAME, GAME_CLOSE);
  key_event(&new_event, TEST_KEY, KEY_SPACE);
  return new_event;
}
