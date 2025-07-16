#pragma once

#include "Game/player.hpp"
#include <raylib.h>
#include <vector>

struct dataForDrawing {
  pCube *p;
};

class Render {
private:
  Camera3D currentCamera;
  Vector3 lookPosition = Vector3{20.0f, 20.0f, 20.0f};

public:
  void init_default_camera() {
    currentCamera.position = lookPosition; // currentCamera position
    currentCamera.target =
        Vector3{0.0f, 0.0f, 0.0f}; // currentCamera looking at point
    currentCamera.up = Vector3{
        0.0f, 1.0f, 0.0f}; // currentCamera up vector (rotation towards target)
    currentCamera.fovy = 45.0f; // currentCamera field-of-view Y
    currentCamera.projection = CAMERA_PERSPECTIVE; // Camera mode type
  }

  void follow_player(Vector3 v) {
    currentCamera.target = v;
    currentCamera.position.x = v.x + lookPosition.x;
    currentCamera.position.y = v.y + lookPosition.y;
    currentCamera.position.z = v.z + lookPosition.z;
  }

  void draw3D(const dataForDrawing &data);
};