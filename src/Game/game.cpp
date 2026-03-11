#include "game.hpp"
#include "Control/control.hpp"
#include "Game/Object/object.hpp"
#include <iostream>
#include <memory>
#include <raylib.h>

void Game::init() {
  SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x
                                     // (if available)
  InitWindow(screenWidth, screenHeight,
             "raylib [core] example - 3d camera mode");

  render.init();

  // Object initialization
  allObj.clear();

  // initLineBoule();
  initFlag();
}

void Game::initFlag() {

  float hauteur = 30.f;

  // Particles : indice 0 to nbrSegmentsFlag*nbrSegmentsFlag-1
  for (int i = 0; i < nbrSegmentsFlag; i++) {
    for (int j = 0; j < nbrSegmentsFlag; j++) {
      float x = -widthFlag / 2 + i * widthFlag / (nbrSegmentsFlag - 1);
      float y =
          heightFlag / 2 - j * heightFlag / (nbrSegmentsFlag - 1) + hauteur;
      allObj.emplace_back(std::make_unique<Sphere>(Vector3{x, y, 0},
                                                   Vector3{0, 0, 0}, 1.0f, 0.1f,
                                                   Color{255, 0, 100, 200}));
    }
  }
  int nbrParticles = allObj.size();
  std::cout << "Number of particles : " << nbrParticles << std::endl;

  allObj.emplace_back(std::make_unique<Sphere>(
      Vector3{-widthFlag / 2 - 1, heightFlag / 2 + hauteur, 0},
      Vector3{0, 0, 0}, 1.0f, 1.0f, Color{255, 0, 255, 100}));
  allObj.emplace_back(std::make_unique<Sphere>(
      Vector3{widthFlag / 2 + 1, heightFlag / 2 + hauteur, 0}, Vector3{0, 0, 0},
      1.0f, 1.0f, Color{255, 0, 255, 100}));

  // Ressorts :
  /*
  We want this structure :
  (0,0) -- (1,0) -- (2,0) -- ... -- (nbrSegmentsFlag-1,0)
    |        |        |              |
  (0,1) -- (1,1) -- (2,1) -- ... -- (nbrSegmentsFlag-1,1)
    |        |        |              |
   ...      ...      ...            ...
    |        |        |              |
  (0,nbrSegmentsFlag-1) -- ... -- (nbrSegmentsFlag-1,nbrSegmentsFlag-1)

  So we have (nbrSegmentsFlag-1)*nbrSegmentsFlag ressorts in horizontal and
  nbrSegmentsFlag*(nbrSegmentsFlag-1) ressorts in vertical, for a total of
  2*nbrSegmentsFlag*(nbrSegmentsFlag-1) ressorts.
  */

  for (int i = 0; i < nbrSegmentsFlag; i++) {
    for (int j = 0; j < nbrSegmentsFlag - 1; j++) {
      allObj.emplace_back(std::make_unique<Ressort>(Color{50, 0, 50, 150},
                                                    restitution, friction));
      Ressort &r = dynamic_cast<Ressort &>(*allObj.back());
      Sphere &s1 = dynamic_cast<Sphere &>(*allObj[i * nbrSegmentsFlag + j]);
      Sphere &s2 = dynamic_cast<Sphere &>(*allObj[i * nbrSegmentsFlag + j + 1]);
      r.getLink()->connect_masses(s1.getPhysics(), s2.getPhysics());

      allObj.emplace_back(std::make_unique<Ressort>(Color{50, 0, 50, 150},
                                                    restitution, friction));
      Ressort &r2 = dynamic_cast<Ressort &>(*allObj.back());
      Sphere &s3 = dynamic_cast<Sphere &>(*allObj[j * nbrSegmentsFlag + i]);
      Sphere &s4 =
          dynamic_cast<Sphere &>(*allObj[(j + 1) * nbrSegmentsFlag + i]);
      r2.getLink()->connect_masses(s3.getPhysics(), s4.getPhysics());
    }
  }

  allObj.emplace_back(
      std::make_unique<Ressort>(Color{50, 0, 50, 150}, restitution, friction));
  Ressort &r = dynamic_cast<Ressort &>(*allObj.back());
  Sphere &s1 = dynamic_cast<Sphere &>(*allObj[0]);
  Sphere &s2 =
      dynamic_cast<Sphere &>(*allObj[nbrSegmentsFlag * nbrSegmentsFlag]);
  r.getLink()->connect_masses(s1.getPhysics(), s2.getPhysics());

  allObj.emplace_back(
      std::make_unique<Ressort>(Color{50, 0, 50, 150}, restitution, friction));
  Ressort &r2 = dynamic_cast<Ressort &>(*allObj.back());
  Sphere &s3 = dynamic_cast<Sphere &>(
      *allObj[(nbrSegmentsFlag) * (nbrSegmentsFlag - 1)]);
  Sphere &s4 =
      dynamic_cast<Sphere &>(*allObj[nbrSegmentsFlag * nbrSegmentsFlag + 1]);
  r2.getLink()->connect_masses(s3.getPhysics(), s4.getPhysics());

  std::cout << "Number of ressorts : " << allObj.size() - nbrParticles
            << std::endl;
}

void Game::initLineBoule() {
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
    phys->update_leapfrog(simulationSpeed * delta);
  };

  auto fct_set_stiffness_damping_ressort = [&](int i, float stiffness,
                                               float damping) {
    Ressort &r = dynamic_cast<Ressort &>(*allObj[i]);
    r.getLink()->set_stiffness(stiffness);
    r.getLink()->set_damping(damping);
  };

#if 0
  for (int i = 0; i < nbrBoules; i++) {
    fct_add_gravity_sphere(i);
  }

  for (int i = nbrBoules + 2; i < 2 * nbrBoules + 3; i++) {
    fct_set_stiffness_damping_ressort(i, restitution, friction);
    fct_compute_send_forces_ressort(i);
  }

  for (int i = 0; i < nbrBoules; i++) {
    fct_update_sphere(i);
  }
#else
  for (int i = 0; i < nbrSegmentsFlag * nbrSegmentsFlag; i++) {
    fct_add_gravity_sphere(i);
  }

  for (int i = nbrSegmentsFlag * nbrSegmentsFlag + 2;
       i < 2 * (nbrSegmentsFlag * (nbrSegmentsFlag - 1)) + 2 +
               nbrSegmentsFlag * nbrSegmentsFlag + 2;
       i++) {
    fct_set_stiffness_damping_ressort(i, restitution, friction);
    fct_compute_send_forces_ressort(i);
  }

  for (int i = 0; i < nbrSegmentsFlag * nbrSegmentsFlag; i++) {
    fct_update_sphere(i);
  }

#endif

  // -----
  if (IsKeyReleased(KEY_P))
    ToggleFullscreen();
}

void Game::draw() {
  // Draw section
  render.draw3D(allObj, restitution, friction, gravity, simulationSpeed);
}
