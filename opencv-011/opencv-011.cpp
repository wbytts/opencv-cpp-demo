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

    /*
    参数：
        src,dst
        ksize：卷积核大小
        sigmaX：
        sigmaY：默认(0,0)
        borderType：默认 4
    当Size为0，0的时候，sigma参数才会起作用，
    sigmaX与sigmaY一般是一样的
    */
    Mat dst;
    GaussianBlur(src, dst, Size(5,5), 0);
    imshow("dst", dst);

    // 盒子模糊
    Mat box_dst;
    boxFilter(src, box_dst, -1, Size(5,5), Point(-1, -1), true, BORDER_DEFAULT);
    imshow("boxFilter demo", box_dst);

    waitKey(0);
    destroyAllWindows();

    return 0;
}