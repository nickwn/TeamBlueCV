#include "targetProcessing.hpp"

TargetProcessing::TargetProcessing()
{
    objectWidth =
    focalLength =
    horizCenter =
    vertCenter =

}

void TargetProcessing::loadTarget(Target target){
  targetWidth = target.getWidth();
  targetCenter = target.getCenter();
}

double targetProcessing::Distance(){
  return objectWidth*focalLength/targetWidth;
}

double targetProcessing::Azimuth(){
  return atan((double) ((targetCenter().x - horizCenter)/focalLength)) * (180/M_PI);
}

double targetProcessing::Altitude(){
  return atan((double) ((targetCenter().y - vertCenter)/focalLength)) * (180/M_PI);
}
