#include "color.h"
#include <iostream>
#include "ray.h"

bool hit_sphere(const point3& center, float radius, const ray& r) {
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  return discriminant > 0;
}

color ray_color(const ray& r) {
  if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
    return color(1, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);

  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  // Image
  const float aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  float viewport_height = 2.0;
  float viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

  // Renderer
  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;
  for (int j = image_height - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      float u = float(i) / (image_width - 1);
      float v = float(j) / (image_height - 1);

      ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::cerr << std::endl << "Done!" << std::endl;

  return 0;
}
