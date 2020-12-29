#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

int main(int argc, char** argv)
{
    // Mat src = imread("f:/images/qq/20200215213837.png");
    Mat src = imread("f:/images/qq/yezi.png");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    imshow("input", src);

    // 做一个高斯模糊，消除一些细微的东西
    GaussianBlur(src, src, Size(3, 3), 0);
    GaussianBlur(src, src, Size(3, 3), 0);

    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);

    // 二值化
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    //findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
    // 只绘制最外层的轮廓
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

    // 一个一个绘制
    for (size_t t = 0; t < contours.size(); t++) {
        // 绘制第t个轮廓
        drawContours(src, contours, t, Scalar(0, 0, 255), 2, 8);
    }

    // -1代表绘制所有
    //drawContours(src, contours, -1, Scalar(0, 0, 255), 2, 8);
    imshow("result", src);

    waitKey(0);
    destroyAllWindows();

    return 0;
}

