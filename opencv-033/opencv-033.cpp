#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Mat src = imread("f:/images/shuang001.jpg");
    imshow("src", src);
    Mat gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary", binary);

   
    Mat k = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
    // 顶帽操作，提取出细小的区域
    Mat tophat;
    morphologyEx(binary, tophat, MORPH_TOPHAT, k);
    imshow("tophat", tophat);

    // 黑帽操作
    Mat blackhat;
    morphologyEx(binary, blackhat, MORPH_BLACKHAT, k);
    imshow("blackhat", blackhat);

    Mat khit = getStructuringElement(MORPH_CROSS, Size(5, 5), Point(-1, -1));
    // 击不中
    Mat hitmiss;
    morphologyEx(binary, hitmiss, MORPH_HITMISS, k);
    imshow("hitmiss", hitmiss);

    waitKey(0);
    destroyAllWindows();

    return 0;
}


