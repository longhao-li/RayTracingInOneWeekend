#pragma once

#include "ray.h"

#include <random>

class Camera {
public:
  Camera(Vec3f from, Vec3f lookAt, Vec3f up, float fovY, float aspectRatio,
         float aperture, float focusDistance) noexcept {
    float h = tanf(fovY / 2.0f);
    float height = 2.0f * h;
    float width = aspectRatio * height;

    _lookTo = (lookAt - from).normalize();
    _right = cross(up.normalize(), _lookTo);
    _up = cross(_lookTo, _right);

    _origin = from;
    _width = focusDistance * width * _right;
    _height = focusDistance * height * _up;
    _lowerLeft =
        _origin - _width * 0.5f - _height * 0.5f + focusDistance * _lookTo;
    _lensRadius = aperture / 2.0f;
  }

  Ray generateRay(float u, float v) const noexcept {
    Vec3f rd = _lensRadius * randomInUnitDisk();
    Vec3f offset = _right * rd.x + _up * rd.y;
    Vec3f target = _lowerLeft + u * _width + v * _height - offset;
    return Ray(_origin + offset, target - _origin);
  }

private:
  static float randomFloat() noexcept {
    static std::mt19937 rand(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return dist(rand);
  }

  static Vec3f randomInUnitDisk() noexcept {
    for (;;) {
      Vec3f p(randomFloat(), randomFloat(), 0.0f);
      if (p.length2() >= 0.5f)
        continue;

      return p;
    }
  }

private:
  Vec3f _origin;
  Vec3f _lowerLeft;
  Vec3f _width;
  Vec3f _height;
  Vec3f _lookTo;
  Vec3f _right;
  Vec3f _up;
  float _lensRadius;
};
