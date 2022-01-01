//
// Created by Stefan Annell on 2022-01-01.
//

#pragma once

#include "ray.h"

class camera {
public:
  camera(
      point3 lookfrom,
      point3 lookat,
      vec3 vup,
      float vfov,
      float aspect_ratio,
      float aperture,
      float focus_dist
      );

  ray get_ray(float u, float v) const;

private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  float lens_radius;
};
