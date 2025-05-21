#include "image_utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

struct image_u8 * image_u8_init() {
  return new image_u8();
}

struct image_f32 * image_f32_init() {
  return new image_f32();
}

void image_u8_free(struct image_u8 * img) {
  if (img)
    delete img;
}

void image_f32_free(struct image_f32 * img) {
  if (img)
    delete img;
}

bool image_load_from_file(const char * fname, image_u8 * img) {
  int nx, ny, nc;
  auto * data = stbi_load(fname, &nx, &ny, &nc, 3);
  if (!data) {
    fprintf(stderr, "%s: Error: Failed to load image: %s\n", __func__, fname);
    return false;
  }
  
  img->nx = nx;
  img->ny = ny;
  img->buf.resize(3 * nx * ny);
  memcpy(img->buf.data(), data, img->buf.size());

  stbi_image_free(data);
  return true;
}

void bilinear_resize(const image_u8 * src, image_u8 * dst,
                     const int target_width, const int target_height) {
  dst->nx = target_width;
  dst->ny = target_height;
  dst->buf.resize(3 * target_width, target_height);

  float x_ratio = static_cast<float>(src->nx - 1) / target_width;
  float y_ratio = static_cast<float>(src->ny - 1) / target_height;

  for (int y = 0; y < target_height; y++) {
    for (int x = 0; x < target_width; x++) {
      float px = x_ratio * x;
      float py = y_ratio * y;
      int x_floor = static_cast<int>(px);
      int y_floor = static_cast<int>(py);
      float x_lerp = px - x_floor;
      float y_lerp = py - y_floor;
      
      for (int c = 0; c < 3; c++) {
        /**
        float top = lerp(
          static_cast<float>(src->buf[3 * (y_floor * src->nx + x_floor) + c]),
          static_cast<float>(src->buf[3 * (y_floor * src->nx + (x_floor + 1)) + c]),
          x_lerp
        );
        float bottom = 
        **/
      }


    }
  }
}

bool image_preprocess(const image_u8 * img0, image_f32 * img1,
                      const int target_width, const int target_height) {
  /* resize an input image to width x height  */
  image_u8 * dst = image_u8_init();
  bilinear_resize(img0, dst, target_width, target_height);

  /* normalize an image */
  // const float mean[] = {};
  // const float std[] = {};
  return true;
}
