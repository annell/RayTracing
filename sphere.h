//
// Created by Stefan Annell on 2021-12-30.
//

#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
  sphere()
    : center({}), radius(0) {
  }
  sphere(point3 center, float radius)
    : center(center), radius(radius) {
  }

  bool hit(const ray& r, float t_min, float t_max, hit_record& rec) override;
public:
  point3 center;
  float radius;
};
