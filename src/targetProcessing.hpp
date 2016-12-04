#ifndef TARGET_PROCESSING_H
#define TARGET_PROCESSING_H

#include <opencv2/opencv.hpp>
#include "target.hpp"
using namespace cv;

class targetProcessing
{
    public:

        targetProcessing();
        void loadTarget(Target* target);
        double Distance();
        double Azimuth();
        double Altitude();

    private:

        double targetWidth;
        double objectWidth;
        Point targetCenter;
        double focalLength;
        double horizCenter;
        double vertCenter;

};
#endif
