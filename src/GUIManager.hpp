#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class GUIManager
{
public:
  void createWindow(const std::string& winName);
  void show(const std::string& winName, const cv::Mat& img);
  void addSlider(const std::string& winName, const std::string& sliderName, int max = 255, int* val = nullptr);
private:
  std::vector<std::string> windows;
};

#endif
