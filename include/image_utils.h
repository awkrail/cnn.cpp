#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>
#include <stdint.h>
#include <opencv2/opencv.hpp>

bool image_load(const char * filename, cv::Mat & image);

bool image_preprocess(cv::Mat & image);


#endif
