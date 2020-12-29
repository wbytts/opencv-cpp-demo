#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src = imread("f:/images/lena.jpg");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    imshow("input", src);

    // 读入制作好的lut.png
    Mat color = imread("D:/images/lut.png");
    Mat lut = Mat::zeros(256, 1, CV_8UC3);
    for (int i = 0; i < 256; i++) {
        lut.at<Vec3b>(i, 0) = color.at<Vec3b>(10, i);
    }
    imshow("color", color);
    Mat dst;
    LUT(src, lut, dst);
    imshow("lut-demo-dst", dst);

    // 使用 applyColorMap
    applyColorMap(src, dst, COLORMAP_AUTUMN);
    imshow("color-map", dst);

    waitKey(0);
    destroyAllWindows();
}