//
// Created by Stefan Annell on 2022-01-01.
//

#pragma once

#include "ray.h"

class camera {
public:
  camera();

  ray get_ray(float u, float v) const;

private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};
