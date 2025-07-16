#pragma once

#include <optional>
#include <raylib.h>

struct Force {
  Vector3 direction;
  std::optional<float> duration;
  float factor;
  float accelerationTime = 0;

  float time = 0;
  bool isActive = false;

  void update();
  Vector3 force_to_apply() const;
};

class pCube {
private:
  Vector3 pos{0, 100, 0};
  Vector3 velocity{0, 0, 0};
  float initSpeed = 20;
  float dashSpeed = 50;
  float speed = initSpeed;

  Force fMainMovement;
  Force fGravity;
  Force fJump;
  Force fDash;

  void deplacement_key(Force &force, float &speed, float duration,
                       bool needMoving);

public:
  void init_p();
  void draw_me() const;
  void check_interaction();
  void check_collisions();

  void update_velocity(float &dT);

  void reset_velocity() { velocity = {0, 0, 0}; }
  void apply_velocity() {
    pos.x += velocity.x;
    pos.y += velocity.y;
    pos.z += velocity.z;
  }

  Vector3 get_pos() { return pos; };
};