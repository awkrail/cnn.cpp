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

void padding_image(cv::Mat & image) {
  // https://github.com/facebookresearch/nougat/blob/5a92920d342fb6acf05fc9b594ccb4053dbe8e7a/nougat/model.py#L172
  const int max_size = 672;
  const int width = image.cols;
  const int height = image.rows;

  int resized_width;
  int resized_height;
  if (width > height) {
    resized_width = max_size;
    resized_height = static_cast<int>((static_cast<float>(height) / width) * resized_width);
  } else {
    resized_width = max_size;
    resized_height = static_cast<int>((static_cast<float>(width) / height) * resized_height);
  }
  cv::resize(image, image, cv::Size(resized_width, resized_height));


}

bool image_preprocess(cv::Mat & image) {
  crop_margin(image);
  if (image.rows == 0 || image.cols == 0) {
    fprintf("%s: The rows or cols of extracted image is 0. image.rows = %d, image.cols = %d.\n", __func__, image.rows, image.cols);
    return false;
  }
  padding_image(image);
  return true;
}

