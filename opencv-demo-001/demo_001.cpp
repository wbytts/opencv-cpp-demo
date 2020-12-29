#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int demo001()
{
    // 图像内存对象，在C++中是以Mat对象形式保存的
    Mat img = imread("C:\\Users\\hp\\Desktop\\Emoticon\\q.jpg");

    // 读取灰度图像
    //Mat img = imread("C:\\Users\\hp\\Desktop\\Emoticon\\q.jpg", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    // 创建窗口，WINDOW_AUTOSIZE：表示大小和图像相等
    namedWindow("input", WINDOW_AUTOSIZE);

    // 在指定窗口上显示一张图像
    imshow("input", img);

    // 色彩空间转换
    Mat gray;
    // 转换为灰度图像
    // 参数1：要转换的图像，参数2：存储转换结果的，参数3：转换的选项
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 将图像写入文件
    // 这个图像如果保存出错了，是不会有提示的
    imwrite("f:\\temp\\test\\gray.png", gray);

    waitKey(0);

    // 销毁所有窗口
    destroyAllWindows();
}

int demo002()
{
    /*
        imread函数：用于读取图像

    */
    Mat img = imread("f:/temp/images/lena.jpg");
    /*
        imshow函数：用于图像的显示
    */

    /*
        imwrite函数：用于写入图像到文件
    */
}

int main(int argc, char** argv)
{

    int ret = demo001();

    return ret;
}