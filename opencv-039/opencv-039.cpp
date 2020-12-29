#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void process_frame(Mat& image);
void process_frame2(Mat& image);

auto pMOG2 = createBackgroundSubtractorMOG2(1000, 128, false);

int main(int argc, char** argv)
{
    //VideoCapture capture("f:/car.avi");
    //VideoCapture capture("rtsp://admin:123456@192.168.0.102:8554/live");
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }

    Mat frame;
    //namedWindow("result", WINDOW_NORMAL);

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);

        process_frame2(frame);

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

void process_frame(Mat& image) {
    Mat mask, bg_image;
    pMOG2->apply(image, mask);
    pMOG2->getBackgroundImage(bg_image);
    imshow("mask", mask);
    imshow("background", bg_image);
}

void process_frame2(Mat& image) {
    Mat mask, bg_image;
    pMOG2->apply(image, mask);
    // 形态学操作
    Mat se = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
    morphologyEx(mask, mask, MORPH_OPEN, se);
    imshow("mask", mask);
    // 轮廓发现
    vector<vector<Point>> contours;
    vector<Vec4i> hirearchy;
    findContours(mask, contours, hirearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    int index = -1;
    double max_area = 0;
    for (size_t t = 0; t < contours.size(); t++) {
        double area = contourArea(contours[t]);
        if (area < 150) {
            continue;
        }
        Rect box = boundingRect(contours[t]);
        //rectangle(image, box, Scalar(0, 0, 255), 2, 8);
    }
    imshow("result", image);
}