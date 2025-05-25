#include "image_utils.h"
#include <iostream>

int main(int argc, char * argv[]) {
  /* load image */
  const char * image_filename = "images/paper.png";
  cv::Mat image;
  if (!image_load(image_filename, image)) {
    fprintf(stderr, "%s: Failed to image_load. Abort.\n", __func__);
    return 1;
  }

  /* image preprocessing */
  if (!image_preprocess(image)) {
    fprintf(stderr, "%s: Failed to image_preprocess, Abort.\n", __func__);
    return 1;
  }

  return 0;
}
