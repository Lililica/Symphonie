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