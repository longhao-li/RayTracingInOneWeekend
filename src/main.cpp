#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "camera.h"
#include "dielectric.h"
#include "hittable_list.h"
#include "image.h"
#include "lambertian.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"

#include <cassert>
#include <format>
#include <iostream>
#include <numbers>
#include <random>

static constexpr const uint32_t WIDTH = 800;
static constexpr const uint32_t HEIGHT = 450;

static float randomFloat() noexcept {
  static std::mt19937 rand(std::random_device{}());
  static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  return dist(rand);
}

static Vec3f randomSample(Vec3f normal) noexcept {
  static std::mt19937 rand(std::random_device{}());
  static std::normal_distribution<float> dist(0.0f, 1.0f);

  for (;;) {
    Vec3f vec(dist(rand), dist(rand), dist(rand));
    if (vec.length2() >= 1.0f)
      continue;

    if (dot(vec, normal) > 0)
      return vec;
    else if (dot(vec, normal) < 0)
      return -vec;
  }
}

Vec3f rayColor(const Ray &r, const Hittable &world, int32_t depth) noexcept {
  if (depth <= 0)
    return {};

  HitRecord record;
  if (world.hit(r, 0.0001f, std::numeric_limits<float>::infinity(), record)) {
    Vec3f attenuation;
    Ray outRay;

    if (record.material->scatter(r, record, attenuation, outRay))
      return attenuation * rayColor(outRay, world, depth - 1);
    else
      return {};
  }

  // Background color.
  Vec3f dir = r.direction().normalize();
  float t = 0.5f * (dir.y + 1.0f);
  return (1.0f - t) * Vec3f(1.0f, 1.0f, 1.0f) + t * Vec3f(0.5f, 0.7f, 1.0f);
}

int main() {
  stbi_flip_vertically_on_write(1);

  Image image(WIDTH, HEIGHT);
  constexpr int32_t samplesPerPixel = 32;
  constexpr int32_t maxDepth = 16;

  // World
  auto groundMaterial = std::make_shared<Lambertian>(Vec3f(0.8f, 0.8f, 0.0f));
  auto centerMaterial = std::make_shared<Lambertian>(Vec3f(0.1f, 0.2f, 0.5f));
  auto leftMaterial = std::make_shared<Dielectric>(1.5f);
  auto rightMaterial = std::make_shared<Metal>(Vec3f(0.8f, 0.6f, 0.2f), 0.0f);

  HittableList world;
  world.add<Sphere>(Vec3f(0, 0, 0.0f), 0.5f, centerMaterial);
  world.add<Sphere>(Vec3f(0, -100.5f, 0.0f), 100.0f, groundMaterial);
  world.add<Sphere>(Vec3f(-1.0f, 0.0f, 0.0f), 0.5f, leftMaterial);
  world.add<Sphere>(Vec3f(1.0f, 0.0f, 0.0f), 0.5f, rightMaterial);

  // Camera
  constexpr const Vec3f lookFrom = Vec3f(-2.0f, 2.0f, -2.0f);
  constexpr const Vec3f lookAt = Vec3f(0, 0, 0.0f);
  constexpr const Vec3f cameraUp = Vec3f(0, 1.0f, 0);
  constexpr const float fovY = std::numbers::pi_v<float> * 0.2f;
  constexpr const float aspectRatio = 16.0f / 9.0f;
  constexpr const float aperture = 0.5f;
  const float distToFocus = (lookAt - lookFrom).length();

  Camera cam(lookFrom, lookAt, cameraUp, fovY, aspectRatio, aperture,
             distToFocus);

  // Render
  for (int32_t j = HEIGHT - 1; j >= 0; --j) {
    std::cout << std::format("\rScanlines remaining: {} ", j) << std::flush;
    for (int32_t i = 0; i < WIDTH; ++i) {
      Vec3f color;
      for (int32_t s = 0; s < samplesPerPixel; ++s) {
        float u = (static_cast<float>(i) + randomFloat()) / (WIDTH - 1);
        float v = (static_cast<float>(j) + randomFloat()) / (HEIGHT - 1);
        Ray r = cam.generateRay(u, v);
        color += rayColor(r, world, maxDepth);
      }

      color *= (1.0f / static_cast<float>(samplesPerPixel));
      color = sqrt(color);

      image[j][i] = color;
    }
  }

  image.save("image.jpg");
  return 0;
}
