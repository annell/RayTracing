//
// Created by Stefan Annell on 2022-01-02.
//

#pragma once

#include "hittable.h"

class cube : public hittable {
public:
  cube()
      : cube({}, 0, {}) {
  }
  cube(point3 center, float side, std::shared_ptr<material> material)
      : center(center), side(side), material(material) {
    setCorners(center, side);
  }

  bool hit(const ray&ray, float t_min, float t_max, hit_record& rec) const override;
private:
  void setCorners(const point3& center, float side);
  vec3 normalAt(const vec3& point) const;
public:
  point3 center;
  point3 leftBottom;
  point3 rightTop;
  float side;
  std::shared_ptr<material> material;
};
