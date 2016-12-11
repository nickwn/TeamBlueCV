#include "TargetProcessing.hpp"

TargetProcessor::TargetProcessor(double objWidth, double fl, int imgWidth, int imgHeight):
objectWidth(objWidth), focalLength(fl),
horizCenter(imgWidth/2), vertCenter(imgHeight/2)
{}

void TargetProcessor::loadTarget(const Target& target, double tgtWidth)
{
  targetWidth = target.getWidth();
  targetCenter = target.getCenter();
}

double targetProcessor::calcDistance()
{
  return objectWidth*focalLength/targetWidth;
}

double targetProcessor::calcAzimuth()
{
  return atan((double) ((targetCenter().x - horizCenter)/focalLength)) * (180/M_PI);
}

double targetProcessor::calcAltitude()
{
  return atan((double) ((targetCenter().y - vertCenter)/focalLength)) * (180/M_PI);
}
