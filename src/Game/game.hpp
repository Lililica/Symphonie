#pragma once
#include "Game/Control/control.hpp"
#include "Game/Object/object.hpp"
#include "Render/render.hpp"
#include <memory>
#include <raylib.h>

struct Parameter {

  KeyBinding movementKey;
};

class Game {
private:
  Render render;

  Parameter parameter;

  // Objects in the game
  std::vector<std::unique_ptr<Object>> allObj;

  // Control
  KeyBinding keyBinding;
  float speed = 20.0f;
  float frameRate = 120.0f;
  float simulationSpeed = 1.0f;

  float sphereRadius = .5f;
  float gravity = -9.81f;

  float restitution = -100.0f;
  float friction = 1.f;

  int nbrBoules = 100;
  float spacing = 2.f;

public:
  void init();
  void update();

  void draw();

  void end() { render.end(); }

  //   -------
};