#include "player.hpp"
#include "../Control/control.hpp"
#include <raylib.h>

void pCube::init_p() {
  fGravity.direction = {0, -60, 0};
  fGravity.accelerationTime = 2;
}

void pCube::check_interaction(KeyBinding &key) {

  Control::deplacement_key(fMainMovement, speed, 0.5, false, key,
                           viewDirection);

  // Jump
  if (IsKeyDown(key.jump) && !fGravity.isActive) {
    fJump = {};
    fJump.direction = {0, 60, 0};
    fJump.duration = 1;
    fJump.isActive = true;
  }

  if (IsKeyDown(key.sprint)) {
    speed = initSpeed * 2;
  } else {
    speed = initSpeed;
  }

  if (IsKeyDown(key.dash) && !fDash.isActive) {
    Control::deplacement_key(fDash, dashSpeed, 2, true, key, viewDirection);
  }
}

void pCube::draw_me() const {
  Vector3 rPos = {pos.x, pos.y, pos.z};
  // DrawCube(rPos, myHitBox.x, myHitBox.y, myHitBox.z, RED);
  DrawCylinder(rPos, myHitBox.x, myHitBox.z, myHitBox.y, 10, RED);
  DrawCylinderWires(rPos, myHitBox.x, myHitBox.z, myHitBox.y, 10, BLACK);
  // DrawCubeWires(rPos, myHitBox.x, myHitBox.y, myHitBox.z, MAROON);
}

void pCube::check_collisions(BoundingBox &box1) {

  fGravity.isActive = pos.y > 0;
  if (pos.y < 0) {
    pos.y = 0;
  }

  BoundingBox playerBB = {{pos}, {myHitBox}};
  if (CheckCollisionBoxes(box1, playerBB))
    pos.y = box1.max.y;
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
