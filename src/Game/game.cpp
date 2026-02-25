#include "game.hpp"
#include "Control/control.hpp"
#include <iostream>
#include <raylib.h>

void Game::init() {
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  render.init();
}

void Game::update() {
  float delta = GetFrameTime();
  std::cout << "delta : " << delta << std::endl;

  // Update section
  auto camera = render.getCamera();
  Control::update_camera(*camera, keyBinding, speed, delta);
  render.setCamera(*camera);

  // -----
  if (IsKeyReleased(KEY_P))
    ToggleFullscreen();
}

void Game::draw() {
  // Draw section
  render.draw3D();
}
