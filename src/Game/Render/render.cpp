#include "render.hpp"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void Render::draw3D(std::vector<std::unique_ptr<Object>> &objects,
                    float &restitution, float &friction, float &gravity) {
  BeginDrawing();

  SetTargetFPS(1000.0f);

  ClearBackground(RAYWHITE);

  BeginMode3D(currentCamera);

  // Space visualization
  DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{.0f, 10.0f, .0f}, BLUE);
  DrawGrid(100, 10.0f);

  // Object visualization
  for (auto &obj : objects) {
    obj->draw();
  }

  EndMode3D();

  // UI
  // GUI Sliders
  DrawText("Restitution", 10, 30, 20, DARKGRAY);
  GuiSliderBar(Rectangle{10, 60, 200, 20}, nullptr, nullptr, &restitution,
               -200.0f, 0.0f);

  DrawText("Friction", 10, 100, 20, DARKGRAY);
  GuiSliderBar(Rectangle{10, 130, 200, 20}, nullptr, nullptr, &friction, 0.0f,
               10.0f);

  DrawText("Gravity", 10, 170, 20, DARKGRAY);
  GuiSliderBar(Rectangle{10, 200, 200, 20}, nullptr, nullptr, &gravity, -20.0f,
               20.0f);

  DrawFPS(10, 10);
  EndDrawing();
}

void Render::init() {
  // Camera setup
  currentCamera = {};
  currentCamera.position = Vector3{0.0f, 10.0f, 80.0f};
  currentCamera.target =
      Vector3{currentCamera.position.x, currentCamera.position.y + 2.0f,
              currentCamera.position.z - 10};
  currentCamera.up = Vector3{0.0f, 1.0f, 0.0f};
  currentCamera.fovy = 45.0f;
  currentCamera.projection = CAMERA_PERSPECTIVE;
}