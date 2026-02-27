#include "game.hpp"
#include "Control/control.hpp"
#include "Game/Object/object.hpp"
#include <memory>
#include <raylib.h>

void Game::init() {
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  SetTargetFPS(frameRate);

  render.init();

  // Object initialization
  allObj.clear();

  // Spheres objects : indice 0 to nbrBoules-1
  float startPointX = -(nbrBoules + 1) * spacing / 2.0f;
  for (int i = 0; i < nbrBoules; i++) {
    float x = startPointX + (i + 1) * spacing;
    allObj.emplace_back(
        std::make_unique<Sphere>(Vector3{x, 30, 0}, Vector3{0, 0, 0}, 1.0f,
                                 sphereRadius, Color{255, 0, 0, 200}));
  }

  // Spheres fixes : indice nbrBoules to nbrBoules+1
  allObj.emplace_back(std::make_unique<Sphere>(Vector3{startPointX, 30, 0},
                                               Vector3{0, 0, 0}, 1.0f, 1.0f,
                                               Color{255, 0, 255, 100}));
  allObj.emplace_back(std::make_unique<Sphere>(Vector3{-startPointX, 30, 0},
                                               Vector3{0, 0, 0}, 1.0f, 1.0f,
                                               Color{255, 0, 255, 100}));

  // Ressorts : indice nbrBoules+2 to nbrBoules+nbrBoules+1
  for (int i = 0; i < nbrBoules + 1; i++) {
    allObj.emplace_back(std::make_unique<Ressort>(Color{50, 0, 50, 150},
                                                  restitution, friction));
  }

  auto fct_link = [&](int i1, int i2, int iRessort) {
    Sphere &s1 = dynamic_cast<Sphere &>(*allObj[i1]);
    Sphere &s2 = dynamic_cast<Sphere &>(*allObj[i2]);
    Ressort &r = dynamic_cast<Ressort &>(*allObj[iRessort]);
    r.getLink()->connect_masses(s1.getPhysics(), s2.getPhysics());
  };

  int fixedIdx1 = nbrBoules;
  int fixedIdx2 = nbrBoules + 1;
  int ressortIdxStart = nbrBoules + 2;

  fct_link(fixedIdx1, 0, ressortIdxStart);
  for (int i = 0; i < nbrBoules - 1; i++) {
    fct_link(i, i + 1, ressortIdxStart + i + 1);
  }
  fct_link(nbrBoules - 1, fixedIdx2, ressortIdxStart + nbrBoules);
}

void Game::update() {
  float delta = GetFrameTime();

  // Update section
  auto camera = render.getCamera();
  Control::update_camera(*camera, keyBinding, speed, delta);
  render.setCamera(*camera);

  // Object update
  auto fct_reset_force_sphere = [&](int i) {
    Sphere &s = dynamic_cast<Sphere &>(*allObj[i]);
    MP::pMat *phys = s.getPhysics();
    phys->resetForce();
  };

  auto fct_add_gravity_sphere = [&](int i) {
    Sphere &s = dynamic_cast<Sphere &>(*allObj[i]);
    MP::pMat *phys = s.getPhysics();
    phys->addForce(Vector3{0, gravity * phys->getMass(), 0}); // Gravity
  };

  auto fct_compute_send_forces_ressort = [&](int i) {
    Ressort &r = dynamic_cast<Ressort &>(*allObj[i]);
    r.getLink()->compute_forces();
    r.getLink()->send_forces();
  };

  auto fct_update_sphere = [&](int i) {
    Sphere &s = dynamic_cast<Sphere &>(*allObj[i]);
    MP::pMat *phys = s.getPhysics();
    phys->update(delta);
  };

  auto fct_set_stiffness_damping_ressort = [&](int i, float stiffness,
                                               float damping) {
    Ressort &r = dynamic_cast<Ressort &>(*allObj[i]);
    r.getLink()->set_stiffness(stiffness);
    r.getLink()->set_damping(damping);
  };

  for (int i = 0; i < nbrBoules; i++) {
    fct_reset_force_sphere(i);
    fct_add_gravity_sphere(i);
  }

  for (int i = nbrBoules + 2; i < 2 * nbrBoules + 3; i++) {
    fct_set_stiffness_damping_ressort(i, restitution, friction);
    fct_compute_send_forces_ressort(i);
  }

  for (int i = 0; i < nbrBoules; i++) {
    fct_update_sphere(i);
  }

  // -----
  if (IsKeyReleased(KEY_P))
    ToggleFullscreen();
}

void Game::draw() {
  // Draw section
  render.draw3D(allObj, restitution, friction, gravity);
}
