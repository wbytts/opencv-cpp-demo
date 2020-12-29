#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src1 = imread("f:/temp/images/WindowsLogo.jpg");
    Mat src2 = imread("f:/temp/images/LinuxLogo.jpg");
    //namedWindow("003-windowsSrc", WINDOW_AUTOSIZE);
    //namedWindow("003-linuxSrc", WINDOW_AUTOSIZE);
    //imshow("003-windowsSrc", src1);
    //imshow("003-linuxSrc", src2);

    /*
    Mat dst1;// **
    add(src1, src2, dst1);
    imshow("add", dst1);

    Mat dst2; // 减
    subtract(src1, src2, dst2);
    imshow("subtract", dst2);

    Mat dst3; // 乘
    multiply(src1, src2, dst3);
    imshow("multiply", dst3);

    Mat dst4; // 除
    divide(src1, src2, dst4);
    imshow("divide", dst4);
    */
    Mat src = imread("f:/temp/images/butterfly.jpg");
    imshow("butterfly.jpg", src);
    Mat black = Mat::zeros(src.size(), src.type());
    black = Scalar(40, 40, 40);
    Mat dst;
    // 加或减，改变图像的亮度
    //add(src, black, dst);
    subtract(src, black, dst);
    //imshow("dst", dst);

    Mat dst2;
    black = Scalar(127, 127, 127);
    // 让两个图像以不同的权重相加，然后加上一个常量的值
    // 权重可以给负数
    addWeighted(src, 1.2, black, 0.5, 0, dst2);
    imshow("dst2", dst2);

    Mat dst3;
    addWeighted(src1, 1, src2, 0.5, 0, dst3);
    imshow("src1+src2", dst3);

    

    waitKey(0);
    destroyAllWindows();

    return 0;
}