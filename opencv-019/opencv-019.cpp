#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int t1 = 50;
Mat src;
void canny_demo(int, void*) {
    Mat edges, dst;
    Canny(src, edges, t1, t1 * 3, 3, false);
    bitwise_and(src, src, dst, edges);
    imshow("edges", dst);
}

int main(int argc, char** argv)
{
    src = imread("f:/images/shuang001.jpg");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    //namedWindow("edges", WINDOW_NORMAL);
    imshow("input", src);

    // Canny Demo
    createTrackbar("threshold value:", "input", &t1, 100, canny_demo);
    canny_demo(0, 0);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
