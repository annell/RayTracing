//
// Created by Stefan Annell on 2021-12-30.
//

#pragma once
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  float r = pixel_color.x();
  float g = pixel_color.y();
  float b = pixel_color.z();

  float scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;
  out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << std::endl;
}
