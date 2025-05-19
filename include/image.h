#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <stdint.h>

struct image_u8 {
  int nx;
  int ny;

  std::vector<uint8_t> buf;
};

#endif
