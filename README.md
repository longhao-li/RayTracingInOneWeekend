# Ray Tracing In One Weekend

This is my implementation for *[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)*.

## Build

The code is written on Windows, so it is not guaranteed that it works well for macOS and Linux.

There is only one `main.cpp` file. You can compile it with any C++ compiler you like. C++20 standard is required because `std::format` and `std::numbers` is used.

The program will generate an `image.jpg` at working directory. Take care that the currently existing `image.jpg` will be overwritten if exists.

## Acknowledgement

- [stb](https://github.com/nothings/stb) - MIT License
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - CC0-1.0 License