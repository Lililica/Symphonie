#pragma once

#include "../Physique/moteurPhy.hpp"
#include <raylib.h>

class Object {
private:
  Color color;

public:
  virtual ~Object() = default;
  virtual void draw() const = 0;
};

class Sphere : public Object {
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

  void draw() const override {
    DrawSphere(physics.getPosition(), radius, color);
  }
};

class Ressort : public Object {
private:
  MP::pLink link;

  //   Rendering properties
  Color color;

public:
  Ressort(Color color, float stiffness, float damping)
      : link(stiffness, damping), color(color) {}

  MP::pLink *getLink() { return &link; };

  void draw() const override {
    DrawLine3D(link.get_pos_m1(), link.get_pos_m2(), color);
  }
};
