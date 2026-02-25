#include "render.hpp"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void Render::draw3D(Object::Sphere &sphere) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  BeginMode3D(currentCamera);

  // Space visualization
  DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{.0f, 10.0f, .0f}, BLUE);
  DrawGrid(100, 10.0f);

  // Object visualization
  sphere.draw();

  EndMode3D();

  DrawFPS(10, 10);
  EndDrawing();
}

void Render::init() {
  // Camera setup
  currentCamera = {};
  currentCamera.position = Vector3{10.0f, 10.0f, 10.0f};
  currentCamera.target = Vector3{0.0f, 0.0f, 0.0f};
  currentCamera.up = Vector3{0.0f, 1.0f, 0.0f};
  currentCamera.fovy = 45.0f;
  currentCamera.projection = CAMERA_PERSPECTIVE;
}