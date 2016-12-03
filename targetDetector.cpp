#include "targetDetector.hpp"

targetDetector::targetDetector(){

}

Target targetDetector::processImage(Mat image, int num){}

    TargetProcessing tP;

     cvtColor(image, img_hsv, CV_BGR2HSV);
     std::vector<cv::Mat> channels;
     split(img_hsv, channels);

     Mat hueOrig = channels.at(0).clone();
     Mat threshLower, threshUpper;
     Mat result;

     threshold(hueOrig, threshLower, 60, 255, CV_THRESH_BINARY);
     threshold(hueOrig, threshUpper, 180, 255, CV_THRESH_BINARY_INV);

     result = threshLower & threshUpper;
     //imshow("Flag", result);

     Mat edges;
     std::vector<std::vector<Point> > contours;

     Canny(result, edges, 100, 200, 3, false);

     //imshow("Cannied", edges);

     cv::findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

     std::vector<Point> output; // the vector of points of the approxPolyDP contour
     std::vector<Point> max; // the vector of points of the highest approxPolyDP output contour

    double maxY = 0; // highest Y variable checker
    double totalX=0, totalY=0; // total X and Y of all points of output added together
    int i=0, j=0 // iterator variables

     for(i; i<contours.size(); i++){
        approxPolyDP(contours[i], output, cv::arcLength(cv::Mat(contours.at(i)), true) * 0.02
        , bool closed);
        if(output.size()== num && num == 4){ // if trying to detect higher 4 sided target
          totalX += output.x;
          for(j; j<output.size(); j++){ // iterate through approxPolyDP output
            totalX += output[j].x; // add all X values of the output to later find average
            totalY += output[j].y; // add all Y values of the output to later find average
          }
          Point point(total X/= output.size(), totalY /= output.size()); // center point of output

        if(point.y>maxY){ // checking for highest output
            maxY = point.y; // comparing Y value of all output vectors
            max = output; // set max vector as the highest output thus far
          }
          }

          else if(output.size()==num && num ==12){ // if trying to detect lower parking zone 12 sided target (plus)
            return output; // return the output to set as the target
          }

        }

        return max; // if trying to find a 4 sided contour, return the highest one

     waitKey(0);

   }
}
