//
// Created by Stefan Annell on 2021-12-30.
//

#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
  sphere()
    : center({}), radius(0) {
  }
  sphere(point3 center, float radius, std::shared_ptr<material> material)
    : center(center), radius(radius), material(material) {
  }

  bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
public:
  point3 center;
  float radius;
  std::shared_ptr<material> material;
};
