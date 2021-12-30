#include "color.h"
#include <iostream>

int main() {
  // Image

  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

  for (int j = image_height - 1; j >= 0; j--) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      float r = float(i) / (image_width - 1);
      float g = float(j) / (image_height - 1);
      float b = 0.25;

      write_color(std::cout, {r, g, b});
    }
  }
  std::cerr << std::endl << "Done!" << std::endl;

  return 0;
}
