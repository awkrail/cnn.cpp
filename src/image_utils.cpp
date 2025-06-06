#include "image_utils.h"

static cv::Mat crop_margin(const cv::Mat & image) {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  double min_val;
  double max_val;
  cv::minMaxLoc(gray, &min_val, &max_val, nullptr, nullptr);
  if (min_val == max_val) return image;

  cv::Mat normalized = (gray - min_val) / (max_val - min_val) * 255;
  cv::Mat binarized;
  cv::threshold(normalized, binarized, 200, 255, cv::THRESH_BINARY_INV);

  cv::Mat coords;
  cv::findNonZero(binarized, coords);
  cv::Rect rect = cv::boundingRect(coords);
  
  return cv::Mat(image, rect);
}

static cv::Mat padding_image(const cv::Mat & image) {
  /* resized an image while keeping the aspect ratio */
  // https://github.com/facebookresearch/nougat/blob/5a92920d342fb6acf05fc9b594ccb4053dbe8e7a/nougat/model.py#L172
  constexpr int input_size[] = { 672, 896 }; // width, height
  constexpr int min_size = std::min(input_size[0], input_size[1]);
  const int width = image.cols;
  const int height = image.rows;

  int resized_width;
  int resized_height;
  if (width < height) {
    resized_width = min_size;
    resized_height = static_cast<int>((static_cast<float>(height) / width) * min_size);
  } else {
    resized_height = min_size;
    resized_width = static_cast<int>((static_cast<float>(width) / height) * min_size);
  }

  cv::Mat resized_image;
  cv::resize(image, resized_image, cv::Size(resized_width, resized_height), 0, 0, cv::INTER_LINEAR);
  
  /* create canvas and put an image on it */
  const int delta_width = (input_size[0] - resized_image.cols) / 2;
  const int delta_height = (input_size[1] - resized_image.rows) / 2;
  cv::Mat canvas(input_size[1], input_size[0], image.type(), cv::Scalar(0, 0, 0));
  resized_image.copyTo(canvas(cv::Rect(delta_width, delta_height, resized_image.cols, resized_image.rows)));
  return canvas;
}

static cv::Mat normalize(const cv::Mat & image) {
  cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
  cv::Mat normalized;
  image.convertTo(normalized, CV_32FC3, 1.0 / 255);

  std::vector<cv::Mat> channels(3);
  cv::split(normalized, channels);

  const std::vector<float> mean = {0.485, 0.456, 0.406};
  const std::vector<float> stds = {0.229, 0.224, 0.225};

  for (int c = 0; c < 3; c++)
    channels[c] = (channels[c] - mean[c]) / stds[c];

  cv::merge(channels, normalized);
  return normalized;
}

bool image_load(const char * filename, cv::Mat & image) {
  image = cv::imread(filename);
  if (image.empty()) {
    fprintf(stderr, "%s: Unable to load image.\n", __func__);
    return false;
  }
  return true;
}

bool image_preprocess(cv::Mat & image, std::vector<float> & chw) {
  image = crop_margin(image);
  if (image.rows == 0 || image.cols == 0) {
    fprintf(stderr, "%s: The rows or cols of extracted image is 0. image.rows = %d, image.cols = %d.\n", __func__, image.rows, image.cols);
    return false;
  }
  image = padding_image(image);
  image = normalize(image);
  
  /* TODO: loop unrolling */
  for (int c = 0; c < 3; c++) {
    for (int i = 0; i < image.rows; i++) {
      for (int j = 0; j < image.cols; j++) {
        chw.push_back(image.at<cv::Vec3f>(i, j)[c]);
      }
    }
  }

  return true;
}
