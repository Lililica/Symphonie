
#include "control.hpp"
#include "Game/Render/render.hpp"
#include <raylib.h>

float Control::mouse_movement_TETA(float &sensibility) {
  Vector2 mousePos = GetMousePosition();
  float delta = GetFrameTime();

  float distanceX = mousePos.x - (screenWidth / 2.);
  // float distanceY = mousePos.y;

  return delta * sensibility * distanceX;
}

float Control::mouse_movement_PHI(float &sensibility) {
  Vector2 mousePos = GetMousePosition();
  float delta = GetFrameTime();

  float distanceY = mousePos.y - (screenHeight / 2.);
  // float distanceY = mousePos.y;

  SetMousePosition(screenWidth / 2, screenHeight / 2);

  return delta * sensibility * distanceY;
}

void Control::deplacement_key(Force &force, float &inSpeed, float duration,
                              bool needDefaultMoving, KeyBinding &key,
                              float &angleOrigin) {
  if (IsKeyDown(key.moveRight) && IsKeyDown(key.moveForward)) {
    force = {};
    force.direction = {inSpeed * cos((5 * PI / 4) + angleOrigin), 0,
                       inSpeed * sin((5 * PI / 4) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveRight) && IsKeyDown(key.moveBackward)) {
    force = {};
    force.direction = {inSpeed * cos((7 * PI / 4) + angleOrigin), 0,
                       inSpeed * sin((7 * PI / 4) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveLeft) && IsKeyDown(key.moveBackward)) {
    force = {};
    force.direction = {inSpeed * cos((PI / 4) + angleOrigin), 0,
                       inSpeed * sin((PI / 4) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveLeft) && IsKeyDown(key.moveForward)) {
    force = {};
    force.direction = {inSpeed * cos((3 * PI / 4) + angleOrigin), 0,
                       inSpeed * sin((3 * PI / 4) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveBackward)) {
    force = {};
    force.direction = {inSpeed * cos((0) + angleOrigin), 0,
                       inSpeed * sin((0) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveForward)) {
    force = {};
    force.direction = {inSpeed * cos((PI) + angleOrigin), 0,
                       inSpeed * sin((PI) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(key.moveLeft)) {

    force = {};
    force.direction = {inSpeed * cos((PI / 2) + angleOrigin), 0,
                       inSpeed * sin((PI / 2) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;
  }

  else if (IsKeyDown(key.moveRight)) {
    force = {};
    force.direction = {inSpeed * cos((3 * PI / 2) + angleOrigin), 0,
                       inSpeed * sin((3 * PI / 2) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;
  }

  else if (needDefaultMoving) {
    force = {};
    force.direction = {inSpeed * cos((PI) + angleOrigin), 0,
                       inSpeed * sin((PI) + angleOrigin)};
    force.duration = duration;
    force.isActive = true;
  }
}