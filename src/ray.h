#pragma once

#include "vec3f.h"

class Ray {
public:
  Ray() noexcept = default;
  Ray(Vec3f origin, Vec3f dir) noexcept
      : _origin(origin), _direction(dir.normalize()) {}

  Vec3f origin() const noexcept { return _origin; }
  Vec3f direction() const noexcept { return _direction; }
  Vec3f at(float t) const noexcept { return _origin + t * _direction; }

private:
  Vec3f _origin;
  Vec3f _direction;
};
