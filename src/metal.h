#pragma once

#include "material.h"

class Metal : public Material {
public:
  Metal(Vec3f albedo, float fuzz) noexcept : _albedo(albedo), _fuzz(fuzz) {}
  ~Metal() noexcept override = default;

  bool scatter(const Ray &rayIn, const HitRecord &hitRec, Vec3f &attenuation,
               Ray &scattered) const override;

private:
  static Vec3f fuzzSample() noexcept {
    static std::mt19937 rand(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (;;) {
      Vec3f vec(dist(rand), dist(rand), dist(rand));
      const float len2 = vec.length2();
      if (len2 >= 1.0f || len2 <= FLT_EPSILON)
        continue;

      return vec;
    }
  }

private:
  Vec3f _albedo;
  float _fuzz;
};

inline bool Metal::scatter(const Ray &rayIn, const HitRecord &hitRec,
                           Vec3f &attenuation, Ray &scattered) const {
  Vec3f reflected = reflect(rayIn.direction().normalize(), hitRec.normal);
  scattered = Ray(hitRec.point, reflected + _fuzz * fuzzSample());
  attenuation = _albedo;
  return dot(scattered.direction(), hitRec.normal) > 0;
}
