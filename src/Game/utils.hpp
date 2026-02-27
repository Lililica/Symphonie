#pragma once

#include <cmath>
#include <iostream>
#include <raylib.h>

inline Vector3 operator+(const Vector3 &a, const Vector3 &b) {
  return Vector3{a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b) {
  return Vector3{a.x - b.x, a.y - b.y, a.z - b.z};
}
inline Vector3 operator-(const Vector3 &a) { return Vector3{-a.x, -a.y, -a.z}; }

inline float norme_V3(const Vector3 &v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3 operator*(const float &a, const Vector3 &v) {
  return Vector3{a * v.x, a * v.y, a * v.z};
}

inline void print_V3(const Vector3 &v) {
  std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
  return;
}