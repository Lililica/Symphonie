#include "game.hpp"
#include "Control/control.hpp"
#include <iostream>
#include <raylib.h>

void Game::init() {
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  render.init();

  // Object initialization
  sphere = Object::Sphere(Vector3{0, 30, 0}, Vector3{0, 0, 0}, 1.0f, 2.0f,
                          Color{255, 0, 0, 200});
}

void Game::update() {
  float delta = GetFrameTime();

  // Update section
  auto camera = render.getCamera();
  Control::update_camera(*camera, keyBinding, speed, delta);
  render.setCamera(*camera);

  // Object update
  MP::pMat *phys = sphere.getPhysics();
  phys->resetForce();
  phys->addForce(Vector3{0, -9.81f * phys->getMass(), 0}); // Gravity
  phys->update(delta);
  std::cout << "Position: (" << phys->getPosition().x << ", "
            << phys->getPosition().y << ", " << phys->getPosition().z << ")\n";

  // -----
  if (IsKeyReleased(KEY_P))
    ToggleFullscreen();
}

void Game::draw() {
  // Draw section
  render.draw3D(sphere);
}
