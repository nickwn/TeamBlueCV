#include <algorithm>
#include <opencv2/opencv.hpp>
#include "GUIManager.hpp"

void GUIManager::createWindow(const std::string& winName)
{
  cv::namedWindow(winName);
}

void GUIManager::show(const std::string& winName, const cv::Mat& img)
{
  if(std::find(windows.begin(), windows.end(), winName) == windows.end())
  {
    windows.push_back(winName);
    cv::namedWindow(winName);
  }

  cv::imshow(winName, img);
}

void GUIManager::addSlider(const std::string& winName, const std::string& sliderName, int max, int* val)
{
  cv::createTrackbar(sliderName, winName, val, max);
}

int getSliderPos(const std::string& winName, const std::string& sliderName)
{
  return cv::getTrackbarPos(sliderName, winName);
}
