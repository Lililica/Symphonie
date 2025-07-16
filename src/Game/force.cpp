#include "player.hpp"

#include <raylib.h>

void Force::update() {
  time += GetFrameTime();
  if (duration.has_value()) {
    if (time > duration)
      isActive = false;
  }
}

Vector3 Force::force_to_apply() const {
  Vector3 result;
  float timeFactor;
  if (time < accelerationTime) {
    timeFactor = time / accelerationTime;
  } else {
    if (duration.has_value()) {
      timeFactor = 1 - (time / duration.value());
      if (timeFactor < 0)
        timeFactor = 0;
    } else {
      timeFactor = 1.;
    }
  }

  result.x = timeFactor * direction.x;
  result.y = timeFactor * direction.y;
  result.z = timeFactor * direction.z;
  return result;
}