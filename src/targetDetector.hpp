#ifndef TARGET_DETECTOR_HPP
#define TARGET_DETECTOR_HPP

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

class TargetDetector{
  public:
     std::unique_ptr<Target> processImage(Mat image);
  };

  #endif
