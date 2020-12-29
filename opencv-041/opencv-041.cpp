#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

void draw_lines(Mat& frame, vector<Point2f> pts1, vector<Point2f> pts2);

int main(int argc, char** argv)
{
    VideoCapture capture("f:/car.avi");
    //VideoCapture capture("f:/images/vtest.avi");
    //VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }

    namedWindow("frame", WINDOW_AUTOSIZE);
    namedWindow("result", WINDOW_NORMAL);

    Mat frame, preFrame;
    Mat gray, preGray;

    capture.read(preFrame);
    cvtColor(preFrame, preGray, COLOR_BGR2GRAY);

    Mat hsv = Mat::zeros(preFrame.size(), preFrame.type());
    Mat mag = Mat::zeros(hsv.size(), CV_32FC1);
    Mat ang = Mat::zeros(hsv.size(), CV_32FC1);
    Mat xpts = Mat::zeros(hsv.size(), CV_32FC1);
    Mat ypts = Mat::zeros(hsv.size(), CV_32FC1);
    Mat_<Point2f> flow;
    vector<Mat> mv;
    split(hsv, mv);
    Mat bgr;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        calcOpticalFlowFarneback(preGray, gray, flow, 0.5, 3, 50, 3, 5, 1.2, 0);
        for (int row = 0; row < flow.rows; row++) {
            for (int col = 0; col < flow.cols; col++) {
                const Point2f& flow_xy = flow.at<Point2f>(row, col);
                xpts.at<float>(row, col) = flow_xy.x;
                ypts.at<float>(row, col) = flow_xy.y;
            }
        }
        cartToPolar(xpts, ypts, mag, ang);
        ang = ang * 180 / CV_PI / 2.0;
        normalize(mag, mag, 0, 255, NORM_MINMAX);
        convertScaleAbs(mag, mag);
        convertScaleAbs(ang, ang);
        mv[0] = ang;
        mv[1] = Scalar(255);
        mv[2] = mag;
        merge(mv, hsv);
        cvtColor(hsv, bgr, COLOR_HSV2BGR);
        imshow("frame", frame);
        imshow("result", bgr);

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

void draw_lines(Mat& frame, vector<Point2f> pts1, vector<Point2f> pts2) {
    vector<Scalar> lut;
    for (size_t t = 0; t < pts1.size(); t++) {
        int b = rng.uniform(0, 255);
        int g = rng.uniform(0, 255);
        int r = rng.uniform(0, 255);
        lut.push_back(Scalar(b, g, r));
    }
    for (size_t t = 0; t < pts1.size(); t++) {
        line(frame, pts1[t], pts2[t], lut[t], 1, 8, 0);
    }
}