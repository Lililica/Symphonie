#pragma once

#include "moteurPhy.hpp"
#include <algorithm>

namespace MP {

inline float dot_V3(const Vector3 &a, const Vector3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 normalize_V3(const Vector3 &v) {
  float n = norme_V3(v);
  if (n <= 0.000001f)
    return Vector3{0, 1, 0};
  return (1.0f / n) * v;
}

class FixedPlaneContact {
private:
  Vector3 point;
  Vector3 normal;
  float alpha;
  float beta;

  Vector3 react(const Vector3 &value) const {
    Vector3 nPart = dot_V3(value, normal) * normal;
    Vector3 tPart = value - nPart;
    float nLen = norme_V3(nPart);
    float tLen = norme_V3(tPart);

    // Thème 2 : dynamique inverse sur point fixe géométrique.
    // - composante normale : rebond
    // - composante tangentielle : glissement ou adhérence
    if (tLen <= 0.000001f || tLen < beta * nLen) {
      return -alpha * nPart;
    }

    return (-alpha * nPart) + (1.0f - beta * nLen / tLen) * tPart;
  }

public:
  FixedPlaneContact(Vector3 planePoint, Vector3 planeNormal,
                    float dissipation = 0.6f, float friction = 0.2f)
      : point(planePoint), normal(normalize_V3(planeNormal)),
        alpha(std::clamp(dissipation, 0.0f, 1.0f)),
        beta(std::clamp(friction, 0.0f, 1.0f)) {}

  bool resolve(pMat &mass, float dt) const {
    const float epsilon = 0.0001f;

    Vector3 p = mass.getPosition();
    Vector3 v = mass.getVelocity();
    Vector3 q = p + dt * v;

    float dP = dot_V3(p - point, normal);
    float dQ = dot_V3(q - point, normal);

    // Détection simple par segment [P,Q] comme dans le sujet.
    bool isCrossing = (dP > epsilon && dQ <= 0.0f);
    bool isPenetrating = (dP <= epsilon && dot_V3(v, normal) < 0.0f);
    if (!isCrossing && !isPenetrating)
      return false;

    Vector3 newVelocity = react(v);
    Vector3 newForce = react(mass.getForce());

    mass.setVelocity(newVelocity);
    mass.setForce(newForce);

    // Petite correction de position pour éviter l'enfoncement numérique.
    if (dP <= 0.0f) {
      mass.setPosition(p - dP * normal + epsilon * normal);
    }

    return true;
  }
};

} // namespace MP