//
// Created by Stefan Annell on 2021-12-30.
//

#include "sphere.h"
bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) {
  vec3 oc = r.origin() - center;
  float a = r.direction().length_squared();
  float half_b = dot(oc, r.direction());
  float c = oc.length_squared() - radius * radius;
  float discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return false;
  }
  float sqrtd = sqrt(discriminant);

  float root = (-half_b - sqrtd) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || root > t_max) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - center) / radius;
  return true;
}
