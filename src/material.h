#pragma once

#include "hit.h"
#include "ray.h"

#include <memory>

class Material : public std::enable_shared_from_this<Material> {
public:
  virtual ~Material() noexcept = default;
  virtual bool scatter(const Ray &rayIn, const HitRecord &hitRec,
                       Vec3f &attenuation, Ray &scattered) const = 0;
};
