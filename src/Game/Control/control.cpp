#include "control.hpp"

void Control::update_camera(Camera3D &camera, const KeyBinding &keyBinding,
                            float speed, float deltaTime) {
  // Camera movement
  if (IsKeyDown(keyBinding.moveForward)) {
    camera.position.z -= speed * deltaTime;
    camera.target.z -= speed * deltaTime;
  }
  if (IsKeyDown(keyBinding.moveBackward)) {
    camera.position.z += speed * deltaTime;
    camera.target.z += speed * deltaTime;
  }
  if (IsKeyDown(keyBinding.moveRight)) {
    camera.position.x += speed * deltaTime;
    camera.target.x += speed * deltaTime;
  }
  if (IsKeyDown(keyBinding.moveLeft)) {
    camera.position.x -= speed * deltaTime;
    camera.target.x -= speed * deltaTime;
  }

  // Camera rotation
  if (IsKeyDown(KEY_RIGHT)) {
    camera.target.x += speed * deltaTime / 3.;
  }
  if (IsKeyDown(KEY_LEFT))
    camera.target.x -= speed * deltaTime / 3.;
  if (IsKeyDown(KEY_UP))
    camera.target.y += speed * deltaTime / 3.;
  if (IsKeyDown(KEY_DOWN))
    camera.target.y -= speed * deltaTime / 3.;
}