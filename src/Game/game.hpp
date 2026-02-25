#pragma once
#include "Game/Control/control.hpp"
#include "Render/render.hpp"
#include <raylib.h>

struct Parameter {

  KeyBinding movementKey;
};

class Game {
private:
  Render render;

  Parameter parameter;

  // Control
  KeyBinding keyBinding;
  float speed = 20.0f;

public:
  void init();
  void update();

  void draw();

  //   -------
};