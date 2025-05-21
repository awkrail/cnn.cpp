#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>
#include <stdint.h>

struct image_u8 {
  int nx;
  int ny;

  std::vector<uint8_t> buf;
};

struct image_f32 {
  int nx;
  int ny;

  std::vector<float> buf;
};

image_u8 * image_u8_init();

void image_u8_free(image_u8 * img);

image_f32 * image_f32_init();

void image_f32_free(image_f32 * img);

bool image_load_from_file(const char * fname, image_u8 * img);

void bilinear_resize(const image_u8 * src, image_u8 * dst,
                     const int target_width, const int target_height);

bool image_preprocess(const image_u8 * img0, image_f32 * img1, 
                      const int target_width, const int target_height);


#endif
