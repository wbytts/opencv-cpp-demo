#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

    Mat src = imread("f:/temp/images/lena.jpg", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }


    namedWindow("002-demo", WINDOW_AUTOSIZE);
    imshow("002-demo", src);

    // 获取图像的宽度
    int width = src.cols;
    // 获取图像的高度
    int height = src.rows;
    // 获取图像的通道数
    int dim = src.channels();
    int depth = src.depth();
    int type = src.type();

    if (type == CV_8UC1)
    {
        printf("type：CV_8UC1\n");
    }

    /*
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (dim == 3) {
                Vec3b pixel = src.at<Vec3b>(row, col);
                int blue = pixel[0];
                int green = pixel[1];
                int red = pixel[2];
                src.at<Vec3b>(row, col)[0] = 255 - blue;
                src.at<Vec3b>(row, col)[1] = 255 - green;
                src.at<Vec3b>(row, col)[2] = 255 - red;
            }
            if (dim == 1) {
                int pv = src.at<uchar>(row, col);
                src.at<uchar>(row, col) = (255 - pv);
            }
        }
    }
    imshow("fan", src);
    */

    // 指针方式遍历，并拷贝图像
    Mat result = Mat::zeros(src.size(), src.type());
    for (int row = 0; row < height; row++) {
        uchar* curr_row = src.ptr<uchar>(row);
        uchar* result_row = result.ptr<uchar>(row);
        for (int col = 0; col < width; col++) {
            if (dim == 3) {
                int blue = *curr_row++;
                int green = *curr_row++;
                int red = *curr_row++;

                *result_row++ = blue;
                *result_row++ = green;
                *result_row++ = red;
            }
            if (dim == 1) {
                int pv = *curr_row++;
                *result_row++ = pv;
            }
        }
    }
    imshow("src", src);


    // 这里打印出来depth和type有时候为0，并不代表深度为0，而是代表一个枚举类型的值
    printf("width: %d, height: %d, dim: %d, depth: %d, type: %d\n", width, height, dim, depth, type);

    // 创建mat对象
    Mat t1 = Mat(256, 256, CV_8UC3);
    // Scalar(...) 是一个标量，表示一个颜色值
    // 灰度图像是一个通道的，一个参数就可以
    t1 = Scalar(0, 0, 255);
    imshow("t1", t1);

    // 方法2
    Mat t2 = Mat(Size(512, 512), CV_8UC3);
    t2 = Scalar(255, 0, 255);
    imshow("t2", t2);

    // 创建时指定大小
    Mat t3 = Mat::zeros(Size(256, 256), CV_8UC3);
    imshow("t3", t3);

    // 从现有的图像create
    // 只是对象引用的赋值，本质上还是一张图像
    // 如果对原图像进行修改，t4也会被修改
    Mat t4 = src; 
    // 克隆，是一个新的对象
    // 对原图进行修改，t5并不改变
    Mat t5 = src.clone();
    imshow("t5", t5);

    // 拷贝
    Mat t6;
    src.copyTo(t6);
    imshow("t6", t6);

    // 创建一个和现有图像大小、类型一样的空白图像
    Mat t7 = Mat::zeros(src.size(), src.type());
   
    waitKey(0);
    destroyAllWindows();

    return 0;
}