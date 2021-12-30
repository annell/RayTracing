#include <iostream>

int main() {
  // Image

  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

  for (int j = image_height - 1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      float r = float(i) / (image_width - 1);
      float g = float(j) / (image_height - 1);
      float b = 0.25;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
    }
  }

  return 0;
}
