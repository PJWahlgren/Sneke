#include "control.h"
#include "raylib.h"

#include <stdint.h>
#include <stdio.h>

#define GAME_UP KEY_W
#define GAME_LEFT KEY_A
#define GAME_DOWN KEY_S
#define GAME_RIGHT KEY_D
#define GAME_CLOSE KEY_X

char has_event_happened(uint8_t *events, GameEvent event) {
  uint8_t tmp = 1 << event;
  uint8_t events_cpy = *events;
  events_cpy &= tmp;
  events_cpy >>= event;
  return (char)events_cpy;
}
void key_event(PollEvent *events, GameEvent event, int key) {
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
  PollEvent new_event;
  key_event(&new_event, UP, GAME_UP);
  key_event(&new_event, LEFT, GAME_LEFT);
  key_event(&new_event, DOWN, GAME_DOWN);
  key_event(&new_event, RIGHT, GAME_RIGHT);
  key_event(&new_event, CLOSE_GAME, GAME_CLOSE);
  return new_event;
}
