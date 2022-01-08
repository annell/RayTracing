//
// Created by Stefan Annell on 2021-12-31.
//

#pragma once
#include <cmath>
#include <limits>
#include <iostream>
#include <random>

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(float degrees) {
  return degrees * pi / 180.0;
}

inline float random_float() {
  static std::uniform_real_distribution<float> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_float(float min, float max) {
  return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

template <typename T>
inline bool equal(T a, T b) {
  return std::abs(a - b) < std::numeric_limits<T>::epsilon();
}

#include "ray.h"
#include "vec3.h"
