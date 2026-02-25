#pragma once
#include "Game/Control/control.hpp"
#include "Player/player.hpp"
#include "Render/render.hpp"
#include <raylib.h>

struct Parameter {
  float MouseSensibility = 0.2;

  KeyBinding movementKey;
};

class Game {
private:
  Render render;

  // Player
  pCube p1;

  // Obstacle
  BoundingBox box1{{0, 0, 0}, {5, 2, 5}};

  Parameter parameter;

  dataForDrawing data;

public:
  void init();
  void update();

  void draw();

  //   -------
};