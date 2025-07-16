#pragma once
#include "player.hpp"
#include "render.hpp"
#include <raylib.h>

class Game {
private:
  Render render;
  pCube p1;

  dataForDrawing data;

public:
  void init();
  void update();

  void draw();

  //   -------
};