#ifndef TARGET_HPP
#define TARGET_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

enum class TargetType
{
  Cross, Rect
};

class Target
{
public:
  Target(std::vector<cv::Point> c);
  Target() = default;
  double getHeight();
  double getWidth();
  void printPoints();
  cv::Point getCenter();
  std::vector<cv::Point> getContour();

private:
  std::vector<cv::Point> contour;
  cv::Point getTopPoint();
  cv::Point getBottomPoint();
  cv::Point getLeftPoint();
  cv::Point getRightPoint();
};

#endif
