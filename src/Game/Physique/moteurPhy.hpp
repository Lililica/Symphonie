#pragma once
#include "../utils.hpp"
#include <iostream>
#include <raylib.h>

namespace MP {
class pMat {
private:
  Vector3 position;
  Vector3 velocity;
  Vector3 force;
  float mass;

public:
  pMat() : position{0, 0, 0}, velocity{0, 0, 0}, force{0, 0, 0}, mass(1.0f) {}
  pMat(Vector3 pos, Vector3 vel, float m)
      : position(pos), velocity(vel), mass(m) {}

  void resetForce() { force = Vector3{0, 0, 0}; }
  Vector3 getPosition() const { return position; }
  float getMass() const { return mass; }

  //   Force application
  void addForce(const Vector3 &f) { force = force + f; }

  void update(float deltaTime) {
    // Update velocity and position using simple Euler integration
    Vector3 acceleration =
        Vector3{force.x / mass, force.y / mass, force.z / mass};
    std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y
              << ", " << acceleration.z << ")\n";
    velocity = velocity + Vector3{acceleration.x * deltaTime,
                                  acceleration.y * deltaTime,
                                  acceleration.z * deltaTime};
    std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ", "
              << velocity.z << ")\n";
    position =
        position + Vector3{velocity.x * deltaTime, velocity.y * deltaTime,
                           velocity.z * deltaTime};
    std::cout << "Updated Position: (" << position.x << ", " << position.y
              << ", " << position.z << ")\n";

    // Set limit plane (ground)
    if (position.y < 0) {
      position.y = 0;
      velocity.y = 0;
    }
  }
};

}; // namespace MP