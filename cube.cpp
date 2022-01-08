//
// Created by Stefan Annell on 2022-01-02.
//

#include "cube.h"
#include "rtweekend.h"

bool cube::hit(const ray &ray, float ray_t_min, float ray_t_max, hit_record &rec) const {
  // leftBottom is the corner of AABB with minimal coordinates - left bottom, rightTop is maximal corner
  float t1 = (leftBottom.e[0] - ray.orig.e[0]) / ray.dir.e[0];
  float t2 = (rightTop.e[0]   - ray.orig.e[0]) / ray.dir.e[0];
  float t3 = (leftBottom.e[1] - ray.orig.e[1]) / ray.dir.e[1];
  float t4 = (rightTop.e[1]   - ray.orig.e[1]) / ray.dir.e[1];
  float t5 = (leftBottom.e[2] - ray.orig.e[2]) / ray.dir.e[2];
  float t6 = (rightTop.e[2]   - ray.orig.e[2]) / ray.dir.e[2];

  float t_min = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
  float t_max = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

  // if t_max < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
  // if t_min > t_max, ray doesn't intersect AABB
  if (t_max < 0 || t_min > t_max) {
    return false;
  }

  // intersection is behind some other object or outside of range
  if (t_min < ray_t_min || t_min > ray_t_max) {
    return false;
  }

  rec.t = t_min;
  rec.p = ray.at(rec.t);
  rec.material = material;
  rec.set_face_normal(ray, normalAt(rec.p));
  return true;
}

void cube::setCorners(const point3 &center, float side) {
  vec3 shift(side, side, side);
  leftBottom = center - shift;
  rightTop = center + shift;
}

vec3 cube::normalAt(const point3 &point) const {
  vec3 normal;
  point3 localPoint = point - center;
  float min = std::numeric_limits<float>::max();
  float distance = std::abs(side - std::abs(localPoint.x()));
  if (distance < min) {
    min = distance;
    normal = vec3(1, 0, 0);
  }
  distance = std::abs(side - std::abs(localPoint.y()));
  if (distance < min) {
    min = distance;
    normal = vec3(0, 1, 0);
  }
  distance = std::abs(side - std::abs(localPoint.z()));
  if (distance < min) {
    min = distance;
    normal = vec3(0, 0, 1);
  }
  return normal;
}
