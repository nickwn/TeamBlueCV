#include <algorithm>
#include <memory>
#include <opencv2/opencv.hpp>
#include "TargetDetector.hpp"
#include "Target.hpp"
#include "GUIManager.hpp"

std::unique_ptr<Target> TargetDetector::processImage(const cv::Mat& img, int count, int hueMin, int hueMax, int valMin, int valMax)
{
  std::vector<cv::Mat> hsvSplit;
  split(img, hsvSplit);
  cv::Mat hueThreshed;
  cv::Mat valThreshed;
  cv::Mat threshed;
  thresh(hsvSplit[0], hueThreshed, hueMin, hueMax);
  thresh(hsvSplit[1], valThreshed, valMin, valMax);
  threshed = hueThreshed & valThreshed;
  std::vector<std::vector<cv::Point> > contours;
  findContours(threshed, contours);
  std::vector<cv::Point> targetContour;
  filterContours(contours, targetContour, count);
  if (targetContour.empty())
  {
    return nullptr;
  }

  return std::make_unique<Target>(Target(targetContour));
}

void TargetDetector::split(const cv::Mat& img, std::vector<cv::Mat>& split)
{
  cv::Mat hsv;
  cv::cvtColor(img, hsv, CV_BGR2HSV);
  cv::split(hsv, split);
}

void TargetDetector::thresh(const cv::Mat& in, cv::Mat& out, int low, int high)
{
  cv::Mat threshLower, threshUpper;
  cv::threshold(in, threshLower, low, 255, CV_THRESH_BINARY);
  cv::threshold(in, threshUpper, high, 255, CV_THRESH_BINARY_INV);
  out = threshLower & threshUpper;
}

void TargetDetector::findContours(const cv::Mat& img, std::vector<std::vector<cv::Point> >& contours)
{
  cv::findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
}

void TargetDetector::filterContours(const std::vector<std::vector<cv::Point> >& unfiltered, std::vector<cv::Point>& filtered, int cornerCount)
{
  std::vector<cv::Point> approx;
  std::vector<std::vector<cv::Point> > targets;
  for (int i = 0; i < unfiltered.size(); i++)
  {
	cv::approxPolyDP(cv::Mat(unfiltered[i]), approx, cv::arcLength(cv::Mat(unfiltered[i]), true) * 0.02, true);

	if(approx.size() == 4)
	{
	  double maxCosine = 0;

	  for(int j = 2; j<= 4; j++)
	  {
	    double cosine = fabs(cos(angle(approx[j%4], approx[j-2], approx[j-1])));
		maxCosine = MAX(maxCosine, cosine);
	  }

	  if(maxCosine < 0.3)
		targets.push_back(approx);
	}
  }

  std::sort(targets.begin(), targets.end(), [](auto i, auto j) {return i[0].y < j[0].y; }); // sort in descending order, highest to lowest
  filtered = targets[0]; //return the hightest point
}

double TargetDetector::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    double bleh = atan(dy1/dx1)-atan(dy2/dx2);
    return bleh;
}
