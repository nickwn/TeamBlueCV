#include "Target.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

Target::Target(std::vector<cv::Point> c):contour(c)
{

}

cv::Point Target::getTopPoint()
{
  int max = 0;
  int ref = 0;
  for(int i = 0; i <contour.size(); i++)
  {
    if (contour[i].y > max)
    {
      ref = i;
      max = contour[i].y;
    }
  }
  return contour[ref];
}

cv::Point Target::getBottomPoint()
{
  int min = 10000;
  int ref = 0;
  for(int i = 0; i <contour.size(); i++)
  {
    if (contour[i].y < min)
    {
      ref = i;
      min = contour[i].y;
    }
  }
  return contour[ref];
}

cv::Point Target::getLeftPoint()
{
  int min = 10000;
  int ref = 0;
  for(int i = 0; i <contour.size(); i++)
  {
    if (contour[i].x < min)
    {
      ref = i;
      min = contour[i].x;
    }
  }
  return contour[ref];
}

cv::Point Target::getRightPoint()
{
  int max = 0;
  int ref = 0;
  for(int i = 0; i <contour.size(); i++)
  {
    if (contour[i].x > max)
    {
      ref = i;
      max = contour[i].x;
    }
  }
  return contour[ref];
}

double Target::getHeight()
{
  return abs(getTopPoint().y - getBottomPoint().y);
}

double Target::getWidth()
{
  return abs(getRightPoint().x - getLeftPoint().x);
}

cv::Point Target::getCenter()
{

  double totalX=0, totalY=0;
  int i;
  for(i = 0; i < contour.size(); i++)
  {
      totalX += contour[i].x;
  }

  return cv::Point(totalX /= i, totalY /= i);

}

std::vector<cv::Point> Target::getContour()
{
  return contour;
}
