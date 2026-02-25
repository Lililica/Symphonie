#pragma once

#include <raylib.h>

struct KeyBinding {
  int moveForward = KEY_W;
  int moveBackward = KEY_S;
  int moveRight = KEY_D;
  int moveLeft = KEY_A;
  int cameraRotateRight = KEY_RIGHT;
  int cameraRotateLeft = KEY_LEFT;
  int cameraRotateUp = KEY_UP;
  int cameraRotateDown = KEY_DOWN;

  int jump = KEY_SPACE;
  int dash = KEY_Q;
  int sprint = KEY_LEFT_SHIFT;
};

namespace Control {
void update_camera(Camera3D &camera, const KeyBinding &keyBinding, float speed,
                   float deltaTime);

} // namespace Control