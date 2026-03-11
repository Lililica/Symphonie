#pragma once
#include "../utils.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <raylib.h>

namespace MP {
class pMat {
private:
  Vector3 position;
  Vector3 velocity;
  Vector3 force{};
  float mass;

public:
  pMat() : position{0, 0, 0}, velocity{0, 0, 0}, force{0, 0, 0}, mass(1.0f) {}
  pMat(Vector3 pos, Vector3 vel, float m)
      : position(pos), velocity(vel), mass(m) {}

  Vector3 getPosition() const { return position; }
  Vector3 getVelocity() const { return velocity; }
  float getMass() const { return mass; }

  //   Force application
  void addForce(const Vector3 &f) { force = force + f; }

  void update_leapfrog(float h) {
    // Update velocity and position using simple Euler integration
    Vector3 acceleration =
        Vector3{force.x / mass, force.y / mass, force.z / mass};
    velocity = velocity + Vector3{acceleration.x * h, acceleration.y * h,
                                  acceleration.z * h};
    position =
        position + Vector3{velocity.x * h, velocity.y * h, velocity.z * h};
    force = Vector3{0, 0, 0}; // Reset force after update

    // Set limit plane (ground)
    if (position.y < 0) {
      position.y = 0;
      velocity.y = 0;
    }
  }
};
class pLink {
private:
  pMat *mass1 = nullptr;
  pMat *mass2 = nullptr;

  Vector3 fHook = {};
  Vector3 fFriction = {};

  // Ressort paramater
  float k = 0.5;
  float z = 0.05f;

  float l0 = 0.;

public:
  pLink() = default;
  pLink(float stiffness, float damping) : k(stiffness), z(damping) {}

  Vector3 get_pos_m1() const { return mass1->getPosition(); }
  Vector3 get_pos_m2() const { return mass2->getPosition(); }

  void set_stiffness(float stiffness) { k = stiffness; }
  void set_damping(float damping) { z = damping; }

  void connect_masses(pMat *m1, pMat *m2) {
    mass1 = m1;
    mass2 = m2;

    l0 = norme_V3(mass2->getPosition() - mass1->getPosition());
  }

  void compute_forces() {
    if (mass1 == nullptr || mass2 == nullptr) {
      std::cerr << "Error pLink forces compute : Some masses aren't assign"
                << std::endl;
      return;
    }

    // Hooke's law: F = -k * (1 - l0 / d) * (M2 - M1)
    Vector3 M1M2 = mass2->getPosition() - mass1->getPosition();
    float dM1M2 = norme_V3(M1M2);
    dM1M2 = (dM1M2 == 0) ? 0.0001f : dM1M2; // Avoid division by zero
    fHook = (k) * (1 - l0 / dM1M2) * M1M2;

    // frein cinetique : F = -c * (V2 - V1)
    Vector3 V1V2 = mass2->getVelocity() - mass1->getVelocity();
    fFriction = -(z)*V1V2;
  }

  void send_forces() {
    mass1->addForce(fHook - fFriction);
    mass2->addForce(-fHook + fFriction);
  };
};
}; // namespace MP