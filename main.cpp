#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "cube.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <future>

color ray_color(const ray& r, const hittable& world , int depth) {
  hit_record rec;
  if (depth <= 0) {
    return color(0, 0, 0);
  }
  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation(0, 0, 0);
    if (rec.material->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return attenuation;
  }

  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);

  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.1, 0.3, 0.6);
}

hittable_list random_scene() {
  hittable_list world;

  auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(std::make_shared<cube>(point3(0,-1000,0), 1000, ground_material));

  for (int a = -1; a < 11; a++) {
    for (int b = -1; b < 11; b++) {
      auto choose_mat = random_float();
      point3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<material> sphere_material;

        if (choose_mat < 0.7) {
          auto albedo = color::random() * color::random();
          sphere_material = std::make_shared<lambertian>(albedo);
          world.add(std::make_shared<cube>(center, 0.2, sphere_material));
        }
        else if (choose_mat < 0.8) {
          // emissive
          auto albedo = color::random() * color::random();
          sphere_material = std::make_shared<emissive>(albedo, random_float(0.5, 10));
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_float(0, 0.5);
          sphere_material = std::make_shared<metal>(albedo, fuzz);
          world.add(std::make_shared<cube>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<dielectric>(1.5);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<emissive>(color(1.0, 0.4, 0.4), 10);
  auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
  auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  auto material4 = std::make_shared<dielectric>(1.5);

  world.add(std::make_shared<cube>(point3(-4, 1, 0), 1.0, material1));
  world.add(std::make_shared<cube>(point3(0, 1, 0), 1.0, material3));
  world.add(std::make_shared<cube>(point3(4, 1, 0), 1.0, material3));

  return world;
}

int main() {
  // Image
  const float aspect_ratio = 3.0 / 2.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 5;

  // World
  hittable_list world = random_scene();

  // Camera
  point3 lookfrom(13,2,3);
  point3 lookat(0,0,0);
  vec3 vup(0,1,0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;

  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

  using std::chrono::high_resolution_clock;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  auto t1 = high_resolution_clock::now();

  auto pixelTask = [&] (int i, int j) {
    color pixel_color(0, 0, 0);
    for (int s = 0; s < samples_per_pixel; s++) {
      float u = (i + random_float()) / (image_width - 1);
      float v = (j + random_float()) / (image_height - 1);

      ray r = cam.get_ray(u, v);
      pixel_color += ray_color(r, world, max_depth);
    }
    return pixel_color;
  };
  // Renderer
  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;
  std::vector<std::future<color>> threads;
  for (int j = image_height - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      threads.emplace_back(std::async(std::launch::deferred, pixelTask, i, j));
    }
  }
  int i = 0;
  std::cerr << std::endl;
  for (auto& thread : threads) {
    std::cerr << "\rThreads synced: " << i++ << ' ' << std::flush;
    thread.wait();
    write_color(std::cout, thread.get(), samples_per_pixel);
  }

  auto t2 = high_resolution_clock::now();

  duration<double, std::milli> ms_double = t2 - t1;
  std::cerr << std::endl << "Done!" << std::endl;
  std::cerr << ms_double.count() << "ms\n";

  return 0;
}
