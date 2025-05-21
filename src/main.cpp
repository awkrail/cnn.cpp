#include "image_utils.h"

#include <iostream>

int main(int argc, char * argv[]) {
  /* load image */
  image_u8 * img0 = image_u8_init();
  const char * fname = "images/dog.jpg";
  if (!image_load_from_file(fname, img0)) {
    fprintf(stderr, "%s: Unable to load image. Abort.\n", __func__);
    return 1;
  }

  /* preprocess */
  image_f32 * img1 = image_f32_init();
  const int target_width = 224;
  const int target_height = 224;

  if (!image_preprocess(img0, img1, target_width, target_height)) {
    fprintf(stderr, "%s: Unable to preproces image. Abort.\n", __func__);
    return 1;
  }


  

  image_u8_free(img0);
  image_f32_free(img1);
  return 0;
}
