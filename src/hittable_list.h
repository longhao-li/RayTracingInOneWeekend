#pragma once

#include "hit.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  HittableList() noexcept = default;
  ~HittableList() noexcept override = default;

  void clear() noexcept { _objects.clear(); }

  template <typename T, typename... Args,
            class = std::enable_if_t<std::is_constructible_v<T, Args...> &&
                                     std::is_base_of_v<Hittable, T>>>
  T &add(Args &&...args) {
    return static_cast<T &>(*_objects.emplace_back(
        std::make_unique<T>(std::forward<Args>(args)...)));
  }

  Hittable &operator[](size_t index) noexcept { return *_objects[index]; }

  bool hit(const Ray &ray, float tMin, float tMax,
           HitRecord &record) const override;

private:
  std::vector<std::unique_ptr<Hittable>> _objects;
};

inline bool HittableList::hit(const Ray &ray, float tMin, float tMax,
                              HitRecord &record) const {
  HitRecord temp{};
  bool hitAny = false;
  float closest = tMax;
  for (const auto &obj : _objects) {
    if (obj->hit(ray, tMin, closest, temp)) {
      hitAny = true;
      closest = temp.t;
      record = temp;
    }
  }

  return hitAny;
}
