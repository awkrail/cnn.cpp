#include "image_utils.h"

bool image_load(const char * filename, cv::Mat & image) {
  image = cv::imread(filename);
  if (image.empty()) {
    fprintf(stderr, "%s: Unable to load image.\n", __func__);
    return false;
  }
  return true;
}

void crop_margin(cv::Mat & image) {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  double min_val;
  double max_val;
  cv::minMaxLoc(gray, &min_val, &max_val, nullptr, nullptr);
  if (min_val == max_val) return;

  cv::Mat normalized = (gray - min_val) / (max_val - min_val) * 255;
  cv::Mat binarized;
  cv::threshold(normalized, binarized, 200, 255, cv::THRESH_BINARY_INV);

  cv::Mat coords;
  cv::findNonZero(binarized, coords);
  cv::Rect rect = cv::boundingRect(coords);
  
  image = cv::Mat(image, rect);
}

bool image_preprocess(cv::Mat & image) {
  crop_margin(image);

  cv::imwrite("./cropped.png", image);


  return true;
}

