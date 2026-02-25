#pragma once

#include "../Player/force.hpp"
#include <raylib.h>

struct Box {
  Vector3 startPos{0, 0, 0};
  Vector3 endPos{5, 2, 5};
};

struct KeyBinding {
  int moveForward = KEY_W;
  int moveBackward = KEY_S;
  int moveRight = KEY_D;
  int moveLeft = KEY_A;

  int jump = KEY_SPACE;
  int dash = KEY_Q;
  int sprint = KEY_LEFT_SHIFT;
};

namespace Control {

void deplacement_key(Force &force, float &speed, float duration,
                     bool needDefaultMoving, KeyBinding &key,
                     float &angleOrigin);

float mouse_movement_TETA(float &sensibility);
float mouse_movement_PHI(float &sensibility);
} // namespace Control