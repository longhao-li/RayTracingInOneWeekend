#pragma once

#include "material.h"

#include <random>

class Dielectric : public Material {
public:
  Dielectric(float ir) noexcept : _ir(ir) {}
  ~Dielectric() noexcept override = default;

  bool scatter(const Ray &rayIn, const HitRecord &hitRec, Vec3f &attenuation,
               Ray &scattered) const override;

private:
  static float reflectance(float cosine, float refractIndex) noexcept {
    // Use Schlick's approximation for reflectance.
    float r0 = (1.0f - refractIndex) / (1.0f + refractIndex);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * powf(1.0f - cosine, 5.0f);
  }

  static float randomFloat() noexcept {
    static std::mt19937 rand(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rand);
  }

private:
  float _ir;
};

bool Dielectric::scatter(const Ray &rayIn, const HitRecord &hitRec,
                         Vec3f &attenuation, Ray &scattered) const {
  attenuation = Vec3f(1.0f);
  float refractionRatio = hitRec.frontFace ? (1.0f / _ir) : _ir;

  Vec3f direction = rayIn.direction().normalize();
  float cosTheta = fmin(dot(-direction, hitRec.normal), 1.0f);
  float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

  bool canRefract = refractionRatio * sinTheta <= 1.0f;
  Vec3f dir;

  if (!canRefract || reflectance(cosTheta, refractionRatio) > randomFloat())
    dir = reflect(direction, hitRec.normal);
  else
    dir = refract(direction, hitRec.normal, refractionRatio);

  scattered = Ray(hitRec.point, dir);
  return true;
}
