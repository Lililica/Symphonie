#include "render.hpp"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
#define GLSL_VERSION 330

void Render::draw3D(std::vector<std::unique_ptr<Object>> &objects,
                    float &restitution, [[maybe_unused]] float &friction,
                    float &gravity) {

  // Set Light position and view position
  Vector3 viewPos = currentCamera.position;
  SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &viewPos,
                 SHADER_UNIFORM_VEC3);
  UpdateLightValues(shader, light);

  BeginDrawing();

  ClearBackground(RAYWHITE);

  BeginMode3D(currentCamera);

  // Space visualization
  DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{.0f, 10.0f, .0f}, BLUE);
  DrawGrid(100, 10.0f);
  DrawPlane(Vector3{0.0f, 0.0f, 0.0f}, Vector2{100.0f, 100.0f},
            Fade(DARKGREEN, 0.20f));

  // Object visualization
  BeginShaderMode(shader);
  for (int i = 0; i < 50 * 50; i++) {
    objects[i]->draw();
  }
  // DrawCube(Vector3{1.0f, 10.0f, 0.0f}, 1.0f, 1.0f, 1.0f, GRAY);
  EndShaderMode();

  // if (light.enabled)
  //   DrawSphereEx(light.position, 0.5f, 8, 8, light.color);
  // else
  //   DrawSphereWires(light.position, 0.5f, 8, 8, ColorAlpha(light.color,
  //   0.3f));
  EndMode3D();

  // UI
  if (GuiButton(Rectangle{230, 10, 120, 30}, "#191#Show GUI"))
    uiDisplayed = !uiDisplayed;

  if (uiDisplayed) {
    // Draw Box that contains the sliders
    DrawRectangle(5, 5, 220, 300, Fade(LIGHTGRAY, 0.5f));
    DrawRectangleLines(5, 5, 220, 300, GRAY);

    // GUI Sliders

    DrawText("Restitution", 10, 30, 20, DARKGRAY);
    GuiSliderBar(Rectangle{10, 60, 200, 20}, nullptr, nullptr, &restitution,
                 0.0f, 200.0f);

    // DrawText("Friction", 10, 100, 20, DARKGRAY);
    // GuiSliderBar(Rectangle{10, 130, 200, 20}, nullptr, nullptr, &friction,
    // 0.0f,
    //              1.0f);
    // friction = restitution / 10.0f;

    DrawText("Gravity", 10, 170, 20, DARKGRAY);
    GuiSliderBar(Rectangle{10, 200, 200, 20}, nullptr, nullptr, &gravity,
                 -20.0f, 20.0f);
  }
  DrawFPS(10, 10);
  EndDrawing();
}

void Render::init() {

  SetTargetFPS(2000.0f);

  // Camera setup
  currentCamera = {};
  currentCamera.position = Vector3{0.0f, 10.0f, 80.0f};
  currentCamera.target =
      Vector3{currentCamera.position.x, currentCamera.position.y + 2.0f,
              currentCamera.position.z - 10};
  currentCamera.up = Vector3{0.0f, 1.0f, 0.0f};
  currentCamera.fovy = 45.0f;
  currentCamera.projection = CAMERA_PERSPECTIVE;

  // Load basic lighting shader
  shader = LoadShader(
      TextFormat("../../src/Game/Render/shaders/lighting.vs", GLSL_VERSION),
      TextFormat("../../src/Game/Render/shaders/lighting.fs", GLSL_VERSION));
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  ambientLoc = GetShaderLocation(shader, "ambient");
  float ambientValue[4] = {0.18f, 0.2f, 0.24f, 1.0f};
  SetShaderValue(shader, ambientLoc, ambientValue, SHADER_UNIFORM_VEC4);

  light =
      CreateLight(LIGHT_POINT, Vector3{0.0f, 10.0f, 0.0f},
                  Vector3{0.0f, 0.0f, 0.0f}, Color{255, 245, 235, 255}, shader);
}