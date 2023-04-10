#pragma once

#include "stb_image_write.h"
#include "vec3f.h"

#include <vector>

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  constexpr Color() noexcept : red(), green(), blue() {}

  constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept
      : red(r), green(g), blue(b) {}

  constexpr Color(float r, float g, float b) noexcept
      : red(static_cast<uint8_t>(r * 255.0f)),
        green(static_cast<uint8_t>(g * 255.0f)),
        blue(static_cast<uint8_t>(b * 255.0f)) {}

  constexpr Color(Vec3f rgb) noexcept : Color(rgb.x, rgb.y, rgb.z) {}
};

class Image {
public:
  Image(uint32_t width, uint32_t height)
      : _width(width), _height(height), _image(size_t(width) * height) {}

  Color *operator[](size_t row) noexcept {
    return _image.data() + row * _width;
  }

  const Color *operator[](size_t row) const noexcept {
    return _image.data() + row * _width;
  }

  uint32_t width() const noexcept { return _width; }
  uint32_t height() const noexcept { return _height; }

  void save(const char *path) const noexcept {
    stbi_write_jpg(path, int(_width), int(_height), 3, _image.data(), 100);
  }

private:
  uint32_t _width;
  uint32_t _height;
  std::vector<Color> _image;
};
