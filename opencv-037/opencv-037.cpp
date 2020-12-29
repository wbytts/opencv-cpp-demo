#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void harris_demo(Mat &image);
void shitomas_demo(Mat &image);

int main(int argc, char** argv)
{
    VideoCapture capture(0);
    //VideoCapture capture("rtsp://admin:123456@192.168.0.102:8554/live");
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

        //harris_demo(frame);
        shitomas_demo(frame);

        imshow("result", frame);
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

void harris_demo(Mat& image) {
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Mat dst;
    double k = 0.04;
    int blockSize = 2, ksize=3;
    cornerHarris(gray, dst, blockSize, ksize, k);
    Mat dst_norm = Mat::zeros(dst.size(), dst.type());
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, -1, Mat());
    convertScaleAbs(dst_norm, dst_norm);
    // draw corners
    RNG rng(12345);
    for (int row = 0; row < image.rows; row++) {
        for (int col = 0; col < image.cols; col++) {
            int rsp = dst_norm.at<uchar>(row, col);
            if (rsp > 150) {
                int b = rng.uniform(0, 255);
                int g = rng.uniform(0, 255);
                int r = rng.uniform(0, 255);
                circle(image, Point(col, row), 5, Scalar(b, g, r), 2, 8);
            }
        }
    }
}

void shitomas_demo(Mat& image) {
    Mat gray, dst;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    vector<Point2f> corners;
    double quality_level = 0.01;
    goodFeaturesToTrack(gray, corners, 200, quality_level, 3, Mat(), 3, false);
    RNG rng(12345);
    for (int i = 0; i < corners.size(); i++) {
        int b = rng.uniform(0, 255);
        int g = rng.uniform(0, 255);
        int r = rng.uniform(0, 255);
        circle(image, corners[i], 5, Scalar(b, g, r), 2, 8);
    }
}
