#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void chuli(Mat);

int main(int argc, char** argv)
{
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }
    namedWindow("frame", WINDOW_AUTOSIZE);
    int fps = capture.get(CAP_PROP_FPS);
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
    int type = capture.get(CAP_PROP_FOURCC);
    printf("size: %d x %d, fps: %d, frames: %d \n", width, height, fps, num_of_frames);

    Mat frame, hsv, mask, result;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        // inRange
        imshow("hsv", hsv);
        inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
        bitwise_not(mask, mask);
        bitwise_and(frame, frame, result, mask);
        imshow("result", result);
        char c = waitKey(50);
        if (c == 27) {
            break;
        }
    }

    capture.release();

    waitKey(0);
    destroyAllWindows();

    return 0;
}


