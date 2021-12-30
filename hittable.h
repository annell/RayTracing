//
// Created by Stefan Annell on 2021-12-30.
//

#pragma once

#include "ray.h"

struct hit_record {
  point3 p;
  vec3 normal;
  float t;
};

class hittable {
public:
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) = 0;
};
