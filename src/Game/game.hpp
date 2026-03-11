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
  float gravity = -1.f;

  float restitution = 100.f;
  float friction = 0.5f;

  int nbrBoules = 30;
  float spacing = 1.f;

  // Flag Dimensions
  float widthFlag = 10.0f;
  float heightFlag = 5.0f;
  int nbrSegmentsFlag = 30;

  void initLineBoule();
  void initFlag();

public:
  void init();
  void update();

  void draw();

  void end() { render.end(); }

  //   -------
};