#ifndef TARGET_DETECTOR_HPP
#define TARGET_DETECTOR_HPP

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include "Target.hpp"

class TargetDetector
{
  public:
     std::unique_ptr<Target> processImage(const cv::Mat& img, int count, int hueMin = 0, int hueMax = 102, int valMin = 227, int valMax = 225);
  private:
    void split(const cv::Mat& img, std::vector<cv::Mat>& split);
    void thresh(const cv::Mat& in, cv::Mat& out, int low, int high);
    void findContours(const cv::Mat& img, std::vector<std::vector<cv::Point> >& contours);
    void filterContours(const std::vector<std::vector<cv::Point> >& unfiltered, std::vector<cv::Point>& filtered, int cornerCount);
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
};

  #endif
