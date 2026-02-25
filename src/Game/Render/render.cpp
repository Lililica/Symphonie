#include "render.hpp"
#include <raylib.h>

void Render::draw3D() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  BeginMode3D(currentCamera);

  DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{.0f, 10.0f, .0f}, BLUE);

  DrawGrid(100, 10.0f);

  EndMode3D();

  DrawFPS(10, 10);

  EndDrawing();
}

void Render::init() {
  // Nothing to initialize for now
  currentCamera = {};
  currentCamera.position = Vector3{10.0f, 10.0f, 10.0f};
  currentCamera.target = Vector3{0.0f, 0.0f, 0.0f};
  currentCamera.up = Vector3{0.0f, 1.0f, 0.0f};
  currentCamera.fovy = 45.0f;
  currentCamera.projection = CAMERA_PERSPECTIVE;
}