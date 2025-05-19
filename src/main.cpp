#include "image_loader.h"

#include <iostream>

int main() {
  struct image_u8 * img = image_u8_init();
  const char * fname = "images/dog.jpg";
  image_load_from_file(fname, img);
  image_u8_free(img);
  return 0;
}
