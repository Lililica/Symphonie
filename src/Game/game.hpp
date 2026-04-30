#pragma once
#include "Game/Control/control.hpp"
#include "Game/Object/object.hpp"
#include "Game/Physique/collision.hpp"
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

  float sphereRadius = .5f;
  float gravity = -1.f;

  float restitution = 100.f;
  float friction = 0.5f;

  // Prolongation - thème 2 : point fixe géométrique de contact
  std::vector<MP::FixedPlaneContact> fixedContacts;

  int nbrBoules = 30;
  float spacing = 1.f;

  // Flag Dimensions
  float widthFlag = 7.0f;
  float heightFlag = 7.0f;
  int nbrSegmentsFlag = 50;

  void initLineBoule();
  void initFlag();
  void initContacts();

public:
  void init();
  void update();

  void draw();

  void end() { render.end(); }

  //   -------
};