#include "image_utils.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
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

  }
  
  


  return 0;
}
