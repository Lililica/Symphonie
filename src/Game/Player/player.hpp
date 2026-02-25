#pragma once

#include "Game/Control/control.hpp"
#include "Game/Player/force.hpp"

#include <raylib.h>

class pCube {
private:
  Vector3 pos{0, 100, 0};
  Vector3 velocity{0, 0, 0};
  float viewDirection = 0;
  float initSpeed = 20;
  float dashSpeed = 50;
  float speed = initSpeed;

  Vector3 myHitBox = {1., 3., 1.};

  Force fMainMovement;
  Force fGravity;
  Force fJump;
  Force fDash;

public:
  void init_p();
  void draw_me() const;
  void check_interaction(KeyBinding &key);
  void check_collisions(BoundingBox &box1);

  void update_velocity(float &dT);
  void reset_velocity() { velocity = {0, 0, 0}; }
  void apply_velocity() {
    pos.x += velocity.x;
    pos.y += velocity.y;
    pos.z += velocity.z;
  }

  void set_viewDirection_Teta(float &teta) { viewDirection = {teta}; }

  Vector3 get_pos() { return pos; };
};
