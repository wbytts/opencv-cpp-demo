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

    Mat dst;
    Mat blur_image;
    GaussianBlur(src, blur_image, Size(5, 5), 0);
    Laplacian(src, dst, -1, 1, 1.0, 0, BORDER_DEFAULT);
    imshow("Laplacian", dst);
    Mat usm_image;
    addWeighted(blur_image, 1.0, dst, -1.0, 0, usm_image);
    imshow("usm filter", usm_image);
    

    waitKey(0);
    destroyAllWindows();

    return 0;
}