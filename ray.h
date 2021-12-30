//
// Created by Stefan Annell on 2021-12-30.
//

#pragma once

#include "vec3.h"

class ray {
public:
  ray()
    : ray({}, {}) {
  }

  ray(const point3& origin, const vec3& direction)
    : origin(origin), direction(direction) {

  }

  point3 origin() const { return origin; }

  vec3 direction() const { return direction; }

  point3 at(float t) {
    return origin + t * direction;
  }

public:
  point3 origin;
  vec3 direction;
};
