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

    threshold(gray, binary, 127, 255, THRESH_BINARY);
    imshow("binary", binary);

    threshold(gray, binary, 127, 255, THRESH_BINARY_INV);
    imshow("binary invert", binary);

    threshold(gray, binary, 127, 255, THRESH_TRUNC);
    imshow("binary trunc", binary);
    
    threshold(gray, binary, 127, 255, THRESH_TOZERO);
    imshow("binary to zero", binary);

    threshold(gray, binary, 127, 255, THRESH_TOZERO_INV);
    imshow("binary to zero invert", binary);


    waitKey(0);
    destroyAllWindows();

    return 0;
}
