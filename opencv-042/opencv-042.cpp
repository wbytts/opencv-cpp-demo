#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

int main(int argc, char** argv)
{
    //VideoCapture capture("f:/car.avi");
    //VideoCapture capture("f:/images/vtest.avi");
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }

    namedWindow("MeanShift Demo", WINDOW_AUTOSIZE);
    Mat frame, hsv, hue, mask, hist, backproj;
    
    capture.read(frame);
    Rect trackWindow;
    bool init = true;
    int hsize = 16;
    float hranges[] = { 0, 180 };
    const float* ranges = hranges;
    Rect selection = selectROI("MeanShift Demo", frame, true, false);


    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(26, 43, 46), Scalar(34, 255, 255), mask);
        int ch[] = { 0,0 };
        hue.create(hsv.size(), hsv.depth());
        mixChannels(&hsv, 1, &hsv, 1, ch, 1);
        if (init) {
            Mat roi(hue, selection), maskroi(mask, selection);
            calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &ranges);
            normalize(hist, hist, 0, 255, NORM_MINMAX);
            trackWindow = selection;
            init = false;
        }
        // ms
        calcBackProject(&hue, 1, 0, hist, backproj, &ranges);
        backproj &= mask;

        meanShift(backproj, trackWindow, TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 1));
        rectangle(frame, trackWindow, Scalar(0, 0, 255), 3, LINE_AA);

        // 自适应均值迁移
        RotatedRect rrt = CamShift(backproj, trackWindow, TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 1));
        ellipse(frame, rrt, Scalar(255, 0, 0), 2, 8);

        imshow("MeanShift Demo", frame);

        char c = waitKey(1);
        if (c == 27) {
            break;
        }
    }

    capture.release();

    waitKey(0);
    destroyAllWindows();

    return 0;
}
