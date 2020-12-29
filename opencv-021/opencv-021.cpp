#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Mat src = imread("f:/images/shuang001.jpg");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    imshow("input", src);

    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);

    // 均值分割
    Scalar m = mean(gray);
    printf("means: %.2f\n", m[0]);
    threshold(gray, binary, m[0], 255, THRESH_BINARY);
    imshow("binary", binary);

    // 直方图
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("THRESH_OTSU", binary);

    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
    imshow("THRESH_TRIANGLE", binary);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
