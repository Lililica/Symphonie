#pragma once

#include "../Player/player.hpp"
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;

struct dataForDrawing {
  pCube *p;
  BoundingBox *box1;
  float tetaCam = PI / 4;
};

class Render {
private:
  Camera3D currentCamera;
  float projDistanceCamPlayer = 35.f;
  float angleView = PI / 4;
  float angleTopView = 1.3;
  Vector3 currentTarget = {};
  Vector3 lookPosition =
      Vector3{static_cast<float>(projDistanceCamPlayer * cos(angleView)),
              static_cast<float>(projDistanceCamPlayer *cos(angleTopView)),
              static_cast<float>(projDistanceCamPlayer *sin(angleView))};

public:
  float get_teta() const { return angleView; }

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
    currentTarget = v;
    lookPosition.x += v.x;
    lookPosition.y += v.y;
    lookPosition.z += v.z;
  }

  void draw3D(const dataForDrawing &data);

  void reset_lookPosition() { lookPosition = {}; };

  void add_to_TETA(float &angle) { angleView += angle; }
  void add_to_PHI(float &angle) {
    if (angleTopView - angle > 0.2 && angleTopView - angle < PI / 2.2)
      angleTopView -= angle;
  }

  void update_camera() {
    currentCamera.target = currentTarget;
    currentCamera.position.x =
        lookPosition.x + static_cast<float>(projDistanceCamPlayer *
                                            cos(angleView) * sin(angleTopView));
    currentCamera.position.y =
        lookPosition.y +
        static_cast<float>(projDistanceCamPlayer * cos(angleTopView));
    currentCamera.position.z =
        lookPosition.z + static_cast<float>(projDistanceCamPlayer *
                                            sin(angleView) * sin(angleTopView));
  };
};