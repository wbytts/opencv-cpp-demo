#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src = imread("f:/images/liu_tou.png");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    imshow("input", src);

    // 自定义滤波 - 均值卷积
    int k = 15;
    Mat mkernel = Mat::ones(k, k, CV_32F) / (float)(k * k);
    Mat dst;
    // 第三个参数，图像深度，-1表示和输入图像一样
    filter2D(src, dst, -1, mkernel, Point(-1, -1), 0, BORDER_DEFAULT);
    imshow("custom mean filter", dst);

    // 非均值滤波
    Mat robot = (Mat_<int>(2, 2) << 1, 0, 0, -1);
    Mat result;
    filter2D(src, result, CV_32F, robot, Point(-1,-1), 0, BORDER_DEFAULT);
    imshow("result", result);
    convertScaleAbs(result, result);
    imshow("convertScaleAbs result", result);

    waitKey(0);
    destroyAllWindows();

    return 0;
}