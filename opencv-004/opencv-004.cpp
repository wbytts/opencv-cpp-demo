#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src = imread("f:/images/apple.jpg");
    Mat src1 = imread("f:/images/WindowsLogo.jpg"); 
    Mat src2 = imread("f:/images/LinuxLogo.jpg");

    imshow("src", src);

    // 位操作
    // 图像取反
    Mat m1;
    bitwise_not(src, m1, Mat());
    imshow("bitwise_not", m1);

    Mat m2;
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    // 参照mask的像素值进行取反
    // mask如果全是0的话，则不取反
    bitwise_not(src, m2, mask);
    imshow("bitwise_not---mask", m2);

    Mat m3;
    Mat mask2 = Mat::zeros(src.size(), CV_8UC1);
    int w = src.cols / 2;
    int h = src.rows / 2;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            mask2.at<uchar>(row, col) = 255;
        }
    }
    imshow("mask2", mask2);
    bitwise_not(src, m3, mask2);
    imshow("m3 bitwise_not", m3);

    // 与操作
    Mat m4;
    bitwise_and(src1, src2, m4);
    imshow("m4 bitwise_and", m4);

    // 或操作
    Mat m5;
    bitwise_or(src1, src2, m5);
    imshow("m5 bitwise_or", m5);

    // 异或操作
    Mat m6;
    bitwise_xor(src1, src2, m6);
    imshow("m6 bitwise_xor", m6);

    // 参数 mask：取ROI区域
    // 位运算的最后一个参数都可以给出一个mask

    waitKey(0);
    destroyAllWindows();

    return 0;
}