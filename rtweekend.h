//
// Created by Stefan Annell on 2021-12-31.
//

#pragma once
#include <cmath>
#include <limits>
#include <iostream>

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(float degrees) {
  return degrees * pi / 180.0;
}

#include "ray.h"
#include "vec3.h"
