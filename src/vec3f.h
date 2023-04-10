#pragma once

#include <cmath>

struct Vec3f {
  float x;
  float y;
  float z;

  constexpr Vec3f() noexcept : x(), y(), z() {}

  explicit constexpr Vec3f(float value) noexcept
      : x(value), y(value), z(value) {}

  constexpr Vec3f(float x, float y, float z) noexcept : x(x), y(y), z(z) {}

  float length2() const noexcept { return x * x + y * y + z * z; }
  float length() const noexcept { return sqrt(length2()); }

  Vec3f normalize() const noexcept {
    const float len = length();
    if (len == 0)
      return *this;

    const float invLen = 1.0f / len;
    return {x * invLen, y * invLen, z * invLen};
  }
};

constexpr float dot(Vec3f lhs, Vec3f rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

constexpr Vec3f cross(Vec3f lhs, Vec3f rhs) noexcept {
  return {
      lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.x * rhs.y - lhs.y * rhs.x,
  };
}

constexpr Vec3f abs(Vec3f vec) noexcept {
  return {
      vec.x < 0 ? -vec.x : vec.x,
      vec.y < 0 ? -vec.y : vec.y,
      vec.z < 0 ? -vec.z : vec.z,
  };
}

constexpr Vec3f max(Vec3f a, Vec3f b) noexcept {
  return {
      a.x < b.x ? b.x : a.x,
      a.y < b.y ? b.y : a.y,
      a.z < b.z ? b.z : a.z,
  };
}

constexpr Vec3f min(Vec3f a, Vec3f b) noexcept {
  return {
      a.x < b.x ? a.x : b.x,
      a.y < b.y ? a.y : b.y,
      a.z < b.z ? a.z : b.z,
  };
}

constexpr Vec3f clamp(Vec3f value, Vec3f floor, Vec3f ceil) noexcept {
  return min(ceil, max(value, floor));
}

inline Vec3f sqrt(Vec3f vec) noexcept {
  return {sqrt(vec.x), sqrt(vec.y), sqrt(vec.z)};
}

constexpr Vec3f operator+(Vec3f vec) noexcept { return vec; }

constexpr Vec3f operator-(Vec3f vec) noexcept {
  return {-vec.x, -vec.y, -vec.z};
}

constexpr Vec3f operator+=(Vec3f &lhs, Vec3f rhs) noexcept {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

constexpr Vec3f operator+=(Vec3f &lhs, float rhs) noexcept {
  lhs.x += rhs;
  lhs.y += rhs;
  lhs.z += rhs;
  return lhs;
}

constexpr Vec3f operator-=(Vec3f &lhs, Vec3f rhs) noexcept {
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
  return lhs;
}

constexpr Vec3f operator-=(Vec3f &lhs, float rhs) noexcept {
  lhs.x -= rhs;
  lhs.y -= rhs;
  lhs.z -= rhs;
  return lhs;
}

constexpr Vec3f operator*=(Vec3f &lhs, Vec3f rhs) noexcept {
  lhs.x *= rhs.x;
  lhs.y *= rhs.y;
  lhs.z *= rhs.z;
  return lhs;
}

constexpr Vec3f operator*=(Vec3f &lhs, float rhs) noexcept {
  lhs.x *= rhs;
  lhs.y *= rhs;
  lhs.z *= rhs;
  return lhs;
}

constexpr Vec3f operator/=(Vec3f &lhs, Vec3f rhs) noexcept {
  lhs.x /= rhs.x;
  lhs.y /= rhs.y;
  lhs.z /= rhs.z;
  return lhs;
}

constexpr Vec3f operator/=(Vec3f &lhs, float rhs) noexcept {
  lhs.x /= rhs;
  lhs.y /= rhs;
  lhs.z /= rhs;
  return lhs;
}

constexpr Vec3f operator+(Vec3f lhs, Vec3f rhs) noexcept {
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

constexpr Vec3f operator+(Vec3f lhs, float rhs) noexcept {
  return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

constexpr Vec3f operator+(float lhs, Vec3f rhs) noexcept {
  return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z};
}

constexpr Vec3f operator-(Vec3f lhs, Vec3f rhs) noexcept {
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

constexpr Vec3f operator-(Vec3f lhs, float rhs) noexcept {
  return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
}

constexpr Vec3f operator*(Vec3f lhs, Vec3f rhs) noexcept {
  return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

constexpr Vec3f operator*(Vec3f lhs, float rhs) noexcept {
  return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

constexpr Vec3f operator*(float lhs, Vec3f rhs) noexcept {
  return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

constexpr Vec3f operator/(Vec3f lhs, Vec3f rhs) noexcept {
  return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

constexpr Vec3f operator/(Vec3f lhs, float rhs) noexcept {
  return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

constexpr bool operator==(Vec3f lhs, Vec3f rhs) noexcept {
  return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

constexpr bool operator!=(Vec3f lhs, Vec3f rhs) noexcept {
  return !(lhs == rhs);
}

inline Vec3f reflect(Vec3f v, Vec3f n) noexcept {
  return v - 2 * dot(v, n) * n;
}

inline Vec3f refract(Vec3f in, Vec3f normal, float refracIndex) noexcept {
  float cosTheta = std::min(dot(-in, normal), 1.0f);
  Vec3f prep = refracIndex * (in + cosTheta * normal);
  Vec3f parallel = -sqrt(fabs(1.0f - prep.length2())) * normal;
  return prep + parallel;
}
