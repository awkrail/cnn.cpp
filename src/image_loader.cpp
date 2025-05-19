#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

struct image_u8 * image_u8_init() {
  return new image_u8();
}

void image_u8_free(struct image_u8 * img) {
  if (img)
    delete img;
}

bool image_load_from_file(const char * fname, image_u8 * img) {
  int nx, ny, nc;
  auto * data = stbi_load(fname, &nx, &ny, &nc, 3);
  if (!data) {
    fprintf(stderr, "Error: Failed to load image: %s\n", fname);
    return false;
  }
  //build_img_from_pixels(data, nx, ny, img);
  stbi_image_free(data);
  return true;
}
