#include <opencv2/opencv.hpp>
#include <iostream>

#include "targetProcessing.hpp"
#include "targetDetector.hpp"
#include "target.hpp"

#define EPSILON 5 // Minimum error value
#define CAM_ANGLE 45 // angle of camera on robot

using namespace cv;

int azimuth = 1000; // azimuth is the original checking angle used for PID with first camera
int azimuth_H; // azimuth_H is the horizontal angle to the higher target
int azimuth_L; // azimuth_L is the horizontal angle to the lower parking zone
int azimuth2; // azimuth2 is the azimuth of the second camera to the ending zone target
int altitude_H; // alitude_H is the altitude of the higher target
int altitude_L; // altitude_L is the altitude of the lower parking zone
int distance_H; // distance_H is the distance between second camera and ending zone parking target
                        //when the azimuth_H is 0
int distance_L; // distance_L is the distance between second camera and ending zone parking target
                        //when the azimuth_L is 0
int distance2; // distance2 is the distance of the second camera to the ending zone target

int main(int, char**){
  targetDetector tD(); // tD is target detector for the first camera
  targetProcessor tP(); // tP is target processor for the first camera
  targetDetector tD2(); // tD2 is target detector for the second camera
  targetProcessor tP2(); // tP2 is target processor for the second camera
  Target target; // target is generic target for the first camera
  Target target2; // target2 is generic target for the second(back) camera
  Target target_original; // target_original is the target for the intial horizontal target(plus sign)
                          // when checking with first camera
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened()){  // check if we succeeded
    return -1;
  }

  Mat frame;

  VideoCapture cap2(0); // open the 2nd default camera
  if(!cap2.isOpened()){  // check if we succeeded
    return -1;
  }

  Mat frame2;

  namedWindow("edges",1);
    while(azimuth > EPSILON){ // while the horizontal azimuth of first camera is greater than error constant
      cap >> frame; // get frame from first camera
      cap2 >> frame2; // get frame from second camera

      target_original = Target(tD.processImage(frame, 12)); // make the image of horizontal detection a target
      tP.loadTarget(target_original);
      azimuth = tp.Azimuth(); //TODO send to sc
    }

    bool scTrigger = true; // when to switch to second camera after 90 degree rotation
    while(scTrigger){ // while SC wants to use PID

      cap >> frame;
      cap2 >> frame2;

      target2 = Target(tD2.processImage(frame2, 12)); // make image of second camera (facing horizontally) into a target
      tP2.loadTarget(target2);
      azimuth2 = tp2.Azimuth(); //TODO send to sc in loop
      distance2 = tp2.Distance(); //TODO send to sc in loop
      // TODO Update SC Trigger from Network Tables (Once PID has
      // navigated close to the target, we will exit this loop.
    }

    while(true){

      cap >> frame;
      cap2 >> frame2;

      target = Target(tD.processImage(frame, 4)); // look for contours with 4 points to make a rectangular target (higher target)
      tP.loadTarget(target);
      azimuth_H = tp.Azimuth(); // the horizontal azimuth to higher target
      altitude_H = tp.Altitude() + CAM_ANGLE; // vertical altitude angle to higher target

      // TODO Check if altitude is greater than some constant to filter out medium goal
      // if(alitude_H > CONSTANT){ TODO find the CONSTANT by checking the camera
      //  //send aziimuth, distance and alitude to SC
      // }

      //distance = tp.Distance(); //send to sc


      if(azimuth_H < EPSILON){ // if the azimuth of higher target is less than error
        distance_H = tp2.Distance(); // If you identify the target
                                     // TODO send horizontal displacement to SC
        // TODO send azimuth_H and alitude_H to SC
      }

      target = Target(tD.processImage(frame, 12)); // look for contours with 4 points to make a plus target (parking zone)
      tP.loadTarget(target);
      azimuth_L = tp.Azimuth(); // the horizontal azimuth to lower parking zone
      altitude_L = CAM_ANGLE - tp.Altitude(); // the vertical altitude angle to lower parking zone

      //distance = tp.Distance(); //send to sc

      if(azimuth_L < EPSILON){ // if the azimuth of lower parking zone is less than error
        distance_L = tp2.Distance(); // If you identify the target
                                     // TODO send horizontal displacement to SC
        // TODO send azimuth_L and alitude_L to SC
      }
    }


  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;

}
