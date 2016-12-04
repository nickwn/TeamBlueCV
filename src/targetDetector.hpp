#ifndef TARGET_DETECTOR_H
#define TARGET_DETECTOR_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class targetDetector{
  public:
    targetDetector();
    Target processImage(Mat image);
  };

  #endif
