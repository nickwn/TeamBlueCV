#ifndef TARGET_H
#define TARGET_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

class Target{
public:
  Target(std::vector<Point> contour);
  double getHeight();
  double getWidth();
  void printPoints();
  Point getCenter();
private:
    Point getTopPoint();
    Point getBottomPoint();
    Point getLeftPoint();
    Point getRightPoint();
  };

  #endif
