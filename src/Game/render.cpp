#include "render.hpp"

void Render::draw3D(const dataForDrawing &data) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  BeginMode3D(currentCamera);

  DrawLine3D(Vector3{0.0f, 0.0f, 0.0f}, Vector3{.0f, 10.0f, .0f}, BLUE);

  data.p->draw_me();

  DrawGrid(100, 10.0f);

  EndMode3D();

  DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

  DrawFPS(10, 10);

  EndDrawing();
}