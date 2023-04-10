#pragma once

#include "ray.h"
#include "vec3f.h"

class Material;

struct HitRecord {
  bool frontFace;
  float t;
  Material *material;
  Vec3f point;
  Vec3f normal;
};

class Hittable {
public:
  virtual ~Hittable() noexcept = default;
  virtual bool hit(const Ray &ray, float tMin, float tMax,
                   HitRecord &record) const = 0;
};
