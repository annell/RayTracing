//
// Created by Stefan Annell on 2022-01-02.
//

#include "cube.h"
#include "rtweekend.h"

bool cube::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
  // r.dir is unit direction vector of ray
  vec3 dirfrac = r.dir;

  // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
  // r.org is origin of ray
  float t1 = (leftBottom.e[0] - r.orig.e[0]) / dirfrac.e[0];
  float t2 = (rightTop.e[0]   - r.orig.e[0]) / dirfrac.e[0];
  float t3 = (leftBottom.e[1] - r.orig.e[1]) / dirfrac.e[1];
  float t4 = (rightTop.e[1]   - r.orig.e[1]) / dirfrac.e[1];
  float t5 = (leftBottom.e[2] - r.orig.e[2]) / dirfrac.e[2];
  float t6 = (rightTop.e[2]   - r.orig.e[2]) / dirfrac.e[2];

  float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
  float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

  // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
  if (tmax < 0) {
    return false;
  }

  // if tmin > tmax, ray doesn't intersect AABB
  if (tmin > tmax) {
    return false;
  }

  if (tmin < t_min || tmin > t_max) {
    return false;
  }
  rec.t = tmin;

  rec.p = r.at(rec.t);
  rec.material = material;
  vec3 outward_normal = vec3(); // No idea about this one
  rec.set_face_normal(r, outward_normal);
  return true;
}

void cube::setCorners(const point3 &center, float side) {
  vec3 shift(side, side, side);
  leftBottom = center - shift;
  rightTop = center + shift;
}

