#include "game.hpp"
#include "Control/control.hpp"
#include <raylib.h>

void Game::init() {
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  render.init_default_camera();
  p1.init_p();
}

void Game::update() {
  float delta = GetFrameTime();

  p1.reset_velocity();
  p1.check_interaction(parameter.movementKey);
  p1.check_collisions(box1);

  p1.update_velocity(delta);

  p1.apply_velocity();

  //   Give the data to render
  data.p = &p1;
  data.tetaCam = render.get_teta();
  data.box1 = &box1;

  p1.set_viewDirection_Teta(data.tetaCam);

  // Camera Management
  render.reset_lookPosition();
  render.follow_player(p1.get_pos());
  float tetaMouse = Control::mouse_movement_TETA(parameter.MouseSensibility);
  render.add_to_TETA(tetaMouse);
  float phiMouse = Control::mouse_movement_PHI(parameter.MouseSensibility);
  render.add_to_PHI(phiMouse);
  render.update_camera();
  SetMousePosition(screenWidth / 2, screenHeight / 2);

  // -----
  if (IsKeyReleased(KEY_P))
    ToggleFullscreen();
}

void Game::draw() {
  // Draw section
  render.draw3D(data);
}
