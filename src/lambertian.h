#pragma once

#include "material.h"

#include <random>

class Lambertian : public Material {
public:
  Lambertian(Vec3f albedo) noexcept : _albedo(albedo) {}
  ~Lambertian() noexcept override = default;

  bool scatter(const Ray &rayIn, const HitRecord &hitRec, Vec3f &attenuation,
               Ray &scattered) const override;

private:
  static Vec3f sample(Vec3f normal) noexcept {
    static std::mt19937 rand(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (;;) {
      Vec3f vec(dist(rand), dist(rand), dist(rand));
      const float len2 = vec.length2();
      if (len2 >= 1.0f || len2 <= FLT_EPSILON)
        continue;

      if (dot(vec, normal) > 0)
        return vec;
      else if (dot(vec, normal) < 0)
        return -vec;
    }
  }

private:
  Vec3f _albedo;
};

inline bool Lambertian::scatter(const Ray &rayIn, const HitRecord &hitRec,
                                Vec3f &attenuation, Ray &scattered) const {
  Vec3f scatterDirection = sample(hitRec.normal);
  scattered = Ray(hitRec.point, scatterDirection);
  attenuation = _albedo;
  return true;
}
