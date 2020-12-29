#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

void draw_lines(Mat &frame, vector<Point2f> pts1, vector<Point2f> pts2);

int main(int argc, char** argv)
{
    //VideoCapture capture("f:/car.avi");
    //VideoCapture capture("f:/images/vtest.avi");
    //VideoCapture capture("rtsp://admin:123456@192.168.0.102:8554/live");
    //VideoCapture capture("f:/images/vtest.avi");
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }

    namedWindow("frame", WINDOW_AUTOSIZE);
    namedWindow("KLT-demo", WINDOW_NORMAL);

    Mat frame, gray;
    Mat old_frame, old_gray;
    capture.read(old_frame);
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    vector<Point2f> feature_pts;
    vector<Point2f> initPoints;
    double quality_level = 0.01;
    int minDistance = 10;
    goodFeaturesToTrack(old_gray, feature_pts, 100, quality_level, minDistance, Mat(), 3, false);
    vector<Point2f> pts[2];
    pts[0].insert(pts[0].end(), feature_pts.begin(), feature_pts.end());
    initPoints.insert(initPoints.end(), feature_pts.begin(), feature_pts.end());

    vector<uchar> status;
    vector<float> err;

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        // calcuate optical flow 计算光流
        // 停止条件，连续迭代10次，或者小于0.01
        TermCriteria criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 10, 0.01);
        calcOpticalFlowPyrLK(old_gray, gray, pts[0], pts[1], status, err, Size(31, 31), 3, criteria, 0);
        size_t i = 0, k = 0;
        for (i = 0; i < pts[1].size(); i++) {
            // 距离与状态检测
            double dist = abs(pts[0][i].x - pts[1][i].x) + abs(pts[0][i].y - pts[1][i].y);
            if (status[i] && dist > 2) {
                pts[0][k] = pts[0][i];
                initPoints[k] = initPoints[i];
                pts[1][k++] = pts[1][i];
                
                int b = rng.uniform(0, 255);
                int g = rng.uniform(0, 255);
                int r = rng.uniform(0, 255);
                circle(frame, pts[1][i], 2, Scalar(b, g, r), 2, 8);
                line(frame, pts[0][i], pts[1][i], Scalar(b, g, r), 2, 8, 0);
            }
        }

        // update key points
        pts[0].resize(k);
        pts[1].resize(k);
        initPoints.resize(k);

        // 绘制跟踪线
        draw_lines(frame, initPoints, pts[1]);

        // 绘制跟踪
        imshow("KLT-demo", frame);

        char c = waitKey(1);
        if (c == 27) {
            break;
        }

        // update to old
        std::swap(pts[1], pts[0]);
        swap(old_gray, gray);
        //swap(old_frame, frame);

        // re-init
        if (pts[0].size() < 40) {
            goodFeaturesToTrack(old_gray, feature_pts, 00, quality_level, minDistance, Mat(), 3, false);
            pts[0].insert(pts[0].end(), feature_pts.begin(), feature_pts.end());
            initPoints.insert(initPoints.end(), feature_pts.begin(), feature_pts.end());
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