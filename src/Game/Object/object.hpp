#pragma once

#include "../Physique/moteurPhy.hpp"
#include <raylib.h>

namespace Object {

class Sphere {
private:
  // Physical properties
  MP::pMat physics;

  // Rendering properties
  float radius;
  Color color;

public:
  Sphere() : physics(), radius(1.0f), color{255, 0, 0, 100} {};
  Sphere(Vector3 position, Vector3 velocity, float mass, float radius,
         Color color)
      : physics(position, velocity, mass), radius(radius), color(color) {}

  MP::pMat *getPhysics() { return &physics; }

  void draw() const { DrawSphere(physics.getPosition(), radius, color); }
};

} // namespace Object