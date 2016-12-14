#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>

#include "GUIManager.hpp"
#include "NetworkController.hpp"
#include "CmdLineInterface.hpp"
#include "TargetProcessor.hpp"
#include "TargetDetector.hpp"
#include "Target.hpp"

#define EPSILON 5 // Minimum error value
#define CAM_ANGLE 45 // angle of camera on robot

void test(TargetType targetType);
void run();
std::string buildStr();

// Alignment Cross values
double alignCrossDist; // distance in inches towards the alignment cross
double alignCrossAz; //azimuth for the alognment cross;

// High goal values
double highGoalDist; // distance in inches towards high goal
double highGoalAz; // azimuth towards high goal
double highGoalAlt; // altitude towards high gloal

// Parking Cross values
double parkCrossDist; // distance towards parking cross in inches
double parkCrossAz; // azimuth towards parking cross in degrees

// Cameras and stuff
TargetDetector targetDetector; // general-purpose TargetDetector
TargetProcessor targetProcessor(480, 320, 240);
VideoCapture backCam; // The back cam. It's main purpose is to find the distance and azimuth for the alignment cross and parking cross. Angled straight ahead
VideoCapture sideCam; // The side cam. It's main purpose is to find the distance and azimuth of the high goal and parking cross.

GUIManager gui;

int main(int argc, char* argv[])
{
  CmdLineInterface cli(argc, argv);

  backCam = VideoCapture(0); //
  if(!backCam.isOpened())
  {  // check if we succeeded
    std::cerr << "failed to open back cam" << std::endl;
    return -1;
  }

  if(cli.getIsTest())
  {
    test(cli.getTargetType());
  }
  else
  {
    sideCam = VideoCapture(1);
    if(!sideCam.isOpened())
    {  // check if we succeeded
      std::cerr << "failed to open side cam" << std::endl;
      return -1;
    }
    run();
  }

  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;

}

void test(TargetType targetType)
{
  cv::Mat backImg;
  std::unique_ptr<Target> target;
  int points = (targetType==TargetType::Cross) ? 12 : 8;
  int tgtWidth = (targetType==TargetType::Cross) ? 20.32 : 50;
  double distance = 0, azimuth = 0, altitude = 0;

  while(waitKey(10) < 0)
  {
    backCam >> backImg;
    target = targetDetector.processImage(backImg, points);
    if(target != nullptr)
    {
      targetProcessor.loadTarget(*target, tgtWidth);
      distance = targetProcessor.calcDistance();
      azimuth = targetProcessor.calcAzimuth();
      altitude = targetProcessor.calcAltitude();

      //drawContours(backImg, &contour, 0, Scalar(255, 0, 0), 4);
      gui.show("img", backImg);
      std::cout << "Target found!" << std::endl
                << "\tDistance: " << distance << std::endl
                << "\tAzimuth: " << azimuth << std::endl
                << "\tAltitude: " << azimuth << std::endl;
    }
    else
    {
      std::cout << "No target found" << std::endl;
    }
  }
}

void run()
{
  /* ---------- Initial Alignment with alignment cross ---------- */
  cv::Mat backImg;
  cv::Mat sideImg;
  std::unique_ptr<Target> alignCross;
  std::unique_ptr<Target> highGoal;
  std::unique_ptr<Target> parkCross;
  while(alignCrossAz > EPSILON)
  { // while the horizontal azimuth of first camera is greater than error constant
    sideCam >> sideImg;
    alignCross = targetDetector.processImage(sideImg, 12); // make the image of horizontal detection a target
    if(alignCross != nullptr)
    {
      targetProcessor.loadTarget(*alignCross, 20.32);
      alignCrossAz = targetProcessor.calcAzimuth(); //TODO send to sc
    }
  }

  /* ---------- Look for both crosses and goal after turning 90 degrees ---------- */
  bool foundParkLoc;
  while (highGoalAz > EPSILON) // loop until we are aligned with the high goal
  {
    // look for alignment cross
    backCam >> backImg;
    alignCross = targetDetector.processImage(backImg, 12);
    if(alignCross != nullptr)
    {
      targetProcessor.loadTarget(*alignCross, 20.32);
      alignCrossDist = targetProcessor.calcDistance();
      alignCrossAz = targetProcessor.calcAzimuth();
    }

    // look for high goal
    sideCam >> sideImg;
    highGoal = targetDetector.processImage(sideImg, 8);
    if(highGoal != nullptr)
    {
      targetProcessor.loadTarget(*highGoal, 50);
      highGoalDist = targetProcessor.calcDistance();
      highGoalAz = targetProcessor.calcAzimuth();
      highGoalAlt = targetProcessor.calcAltitude();
    }

    // look for the parking cross if we haven't already found it to save time
    if(!foundParkLoc)
    {
      sideCam >> sideImg; // update the image again because it took a while to find the high goal
      parkCross = targetDetector.processImage(sideImg, 8);
      if(parkCross != nullptr)
      {
        targetProcessor.loadTarget(*parkCross, 20.32);
        parkCrossDist = targetProcessor.calcDistance();
        parkCrossAz = targetProcessor.calcAzimuth();
      }

      if(parkCrossAz < EPSILON)
        foundParkLoc = true;
    }
  }

  /* ---------- Look for parking cross to align robot with it and drive into it ---------- */
  while (parkCrossDist > 20)
  {
    backCam >> backImg;
    parkCross = targetDetector.processImage(backImg, 12);
    if(parkCross != nullptr)
    {
      targetProcessor.loadTarget(*parkCross, 50);
      parkCrossDist = targetProcessor.calcDistance();
      parkCrossAz = targetProcessor.calcAzimuth();
    }
  }
}
