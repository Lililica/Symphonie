#include "player.hpp"
#include <iostream>
#include <raylib.h>

void pCube::init_p() {
  fGravity.direction = {0, -60, 0};
  fGravity.accelerationTime = 2;
}

void pCube::deplacement_key(Force &force, float &inSpeed, float duration,
                            bool needMoving) {
  if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP)) {
    force = {};
    force.direction = {inSpeed * cos(3 * PI / 2), 0, inSpeed * sin(3 * PI / 2)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN)) {
    force = {};
    force.direction = {inSpeed * cos(0 * PI / 2), 0, inSpeed * sin(0 * PI / 2)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN)) {
    force = {};
    force.direction = {inSpeed * cos(1 * PI / 2), 0, inSpeed * sin(1 * PI / 2)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP)) {
    force = {};
    force.direction = {inSpeed * cos(2 * PI / 2), 0, inSpeed * sin(2 * PI / 2)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_DOWN)) {
    force = {};
    force.direction = {inSpeed * cos(1 * PI / 4), 0, inSpeed * sin(1 * PI / 4)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_UP)) {
    force = {};
    force.direction = {inSpeed * cos(5 * PI / 4), 0, inSpeed * sin(5 * PI / 4)};
    force.duration = duration;
    force.isActive = true;

  }

  else if (IsKeyDown(KEY_LEFT)) {

    force = {};
    force.direction = {inSpeed * cos(3 * PI / 4), 0, inSpeed * sin(3 * PI / 4)};
    force.duration = duration;
    force.isActive = true;
  }

  else if (IsKeyDown(KEY_RIGHT)) {
    force = {};
    force.direction = {inSpeed * cos(7 * PI / 4), 0, inSpeed * sin(7 * PI / 4)};
    force.duration = duration;
    force.isActive = true;
  }

  else if (needMoving) {
    force = {};
    force.direction = {inSpeed * cos(5 * PI / 4), 0, inSpeed * sin(5 * PI / 4)};
    force.duration = duration;
    force.isActive = true;
  }
}

void pCube::check_interaction() {

  deplacement_key(fMainMovement, speed, 0.5, false);

  // Jump
  if (IsKeyDown(KEY_SPACE) && !fGravity.isActive) {
    fJump = {};
    fJump.direction = {0, 60, 0};
    fJump.duration = 1;
    fJump.isActive = true;
  }

  if (IsKeyDown(KEY_Q)) {
    speed = initSpeed * 2;
  } else {
    speed = initSpeed;
  }

  if (IsKeyDown(KEY_W) && !fDash.isActive) {
    deplacement_key(fDash, dashSpeed, 2, true);
  }
}

void pCube::draw_me() const {
  Vector3 rPos = {pos.x + 1.f, pos.y + 1.f, pos.z + 1.f};
  DrawCube(rPos, 2.0f, 2.0f, 2.0f, RED);
  DrawCubeWires(rPos, 2.0f, 2.0f, 2.0f, MAROON);
}

void pCube::check_collisions() {

  fGravity.isActive = pos.y > 0;
  if (pos.y < 0) {
    pos.y = 0;
  }
}

void pCube::update_velocity(float &dT) {

  if (fMainMovement.isActive) {
    fMainMovement.update();
    Vector3 temp = fMainMovement.force_to_apply();
    velocity.x += temp.x * dT;
    velocity.y += temp.y * dT;
    velocity.z += temp.z * dT;
  }

  fGravity.update();
  if (fGravity.isActive) {
    Vector3 temp = fGravity.force_to_apply();
    velocity.x += temp.x * dT;
    velocity.y += temp.y * dT;
    velocity.z += temp.z * dT;
  }

  fJump.update();
  if (fJump.isActive) {
    Vector3 temp = fJump.force_to_apply();
    velocity.x += temp.x * dT;
    velocity.y += temp.y * dT;
    velocity.z += temp.z * dT;
  }

  fDash.update();
  if (fGravity.isActive == false) {
    fGravity.time = 0;
  }
  if (fDash.isActive) {
    Vector3 temp = fDash.force_to_apply();
    velocity.x += temp.x * dT;
    velocity.y += temp.y * dT;
    velocity.z += temp.z * dT;
  }
}
