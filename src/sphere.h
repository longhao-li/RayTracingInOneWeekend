#pragma once

#include "hit.h"
#include "material.h"

#include <utility>

class Sphere : public Hittable {
public:
  Sphere(Vec3f center, float radius,
         std::shared_ptr<Material> material) noexcept
      : _center(center), _radius(radius), _material(std::move(material)) {}

  ~Sphere() noexcept override = default;

  bool hit(const Ray &ray, float tMin, float tMax,
           HitRecord &record) const override;

private:
  Vec3f _center;
  float _radius;
  std::shared_ptr<Material> _material;
};

inline bool Sphere::hit(const Ray &ray, float tMin, float tMax,
                        HitRecord &record) const {
  const Vec3f oc = ray.origin() - _center;
  const float a = ray.direction().length2();
  const float c = oc.length2() - _radius * _radius;
  const float bHalf = dot(oc, ray.direction());
  const float discriminant = bHalf * bHalf - a * c;

  if (discriminant < 0)
    return false;

  float root = (-bHalf - sqrt(discriminant)) / a;
  float root2 = (-bHalf + sqrt(discriminant)) / a;
  if (root > root2)
    std::swap(root, root2);

  if (root < tMin || root > tMax)
    root = root2;

  if (root < tMin || root > tMax)
    return false;

  record.t = root;
  record.point = ray.at(root);
  Vec3f normal = (record.point - _center).normalize();
  record.frontFace = (dot(normal, ray.direction()) < 0);
  record.normal = record.frontFace ? normal : -normal;
  record.material = _material.get();

  return true;
}
