#pragma once

#include "Game/Object/object.hpp"
#include <memory>
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;

class Render {
private:
  Camera3D currentCamera;

public:
  void init();
  void draw3D(Object::Sphere &sphere);

  std::unique_ptr<Camera3D> getCamera() {
    return std::make_unique<Camera3D>(currentCamera);
  }
  void setCamera(const Camera3D &camera) { currentCamera = camera; }
};