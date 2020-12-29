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

    Mat dst;
    Laplacian(src, dst, -1, 3, 1.0, 0, BORDER_DEFAULT);
    imshow("Laplacian", dst);

    // Èñ»¯
    Mat sh_op = (Mat_<int>(3, 3) <<  0, -1,  0, 
                                    -1,  5, -1, 
                                     0, -1,  0);
    Mat result;
    filter2D(src, result, CV_32F, sh_op, Point(-1, -1), 0, BORDER_DEFAULT);
    convertScaleAbs(result, result);
    imshow("sharpen filter", result);

    waitKey(0);
    destroyAllWindows();

    return 0;
}