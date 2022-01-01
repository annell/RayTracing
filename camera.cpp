//
// Created by Stefan Annell on 2022-01-01.
//

#include "camera.h"
camera::camera(
    point3 lookfrom,
    point3 lookat,
    vec3 vup,
    float vfov,
    float aspect_ratio) {
  float theta = degrees_to_radians(vfov);
  float h = tan(theta/2);
  float viewport_height = 2.0 * h;
  float viewport_width = aspect_ratio * viewport_height;

  vec3 w = unit_vector(lookfrom - lookat);
  vec3 u = unit_vector(cross(vup, w));
  vec3 v = cross(w, u);

  origin = lookfrom;
  horizontal = viewport_width * u;
  vertical = viewport_height * v;
  lower_left_corner = origin - horizontal/2 - vertical/2 - w;
}
ray camera::get_ray(float s, float t) const {
  return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}

