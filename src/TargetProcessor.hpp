#ifndef TARGET_PROCESSOR_HPP
#define TARGET_PROCESSOR_HPP

#include <opencv2/opencv.hpp>
#include "Target.hpp"
using namespace cv;

class TargetProcessor
{
public:
  TargetProcessor(double focalLength, int imgWidth, int imgHeight);
  void loadTarget(const Target& target, double tgtWidth);
  double calcDistance();
  double calcAzimuth();
  double calcAltitude();

private:
  double targetWith;
  double objectWidth;
  Point targetCenter;
  double focalLength;
  double horizCenter;
  double vertCenter;
};

#endif
