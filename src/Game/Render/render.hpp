#pragma once

#include "Game/Object/object.hpp"
#include "Game/Render/rlights.h"
#include <memory>
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;

class Render {
private:
  Camera3D currentCamera;
  Shader shader;

  int ambientLoc = -1;
  Light light;

  bool uiDisplayed = false;

public:
  void init();
  void draw3D(std::vector<std::unique_ptr<Object>> &objects, float &restitution,
              float &friction, float &gravity, float &simulationSpeed);
  void end() { UnloadShader(shader); };

  std::unique_ptr<Camera3D> getCamera() {
    return std::make_unique<Camera3D>(currentCamera);
  }
  void setCamera(const Camera3D &camera) { currentCamera = camera; }
};