#include "game.hpp"
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;

void Game::init() {
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  ToggleFullscreen();

  render.init_default_camera();
  p1.init_p();
}

void Game::update() {
  float delta = GetFrameTime();

  p1.reset_velocity();
  p1.check_interaction();
  p1.check_collisions();

  p1.update_velocity(delta);

  p1.apply_velocity();

  //   Give the data to render
  data.p = &p1;

  render.follow_player(p1.get_pos());
}

void Game::draw() {
  // Draw section
  render.draw3D(data);
}
