#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void show_hist(string name, Mat src);
void hist_compare(Mat src1, Mat src2);

int main(int argc, char** argv)
{
    Mat src = imread("f:/images/Crystal.jpg");
    if (src.empty())
    {
        printf("Could not find the image!\n");
        return -1;
    }

    namedWindow("input", WINDOW_AUTOSIZE);
    imshow("input", src);
    
    show_hist("result", src);

    // 直方图均衡化
    Mat gray, dst;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, dst);
    imshow("gray", gray);
    imshow("equalizeHist", dst);

    Mat src1 = imread("f:/images/ela_modified.jpg");
    Mat src2 = imread("f:/images/ela_original.jpg");
    hist_compare(src1, src2);

    waitKey(0);
    destroyAllWindows();
}

void show_hist(string name, Mat src) {
    vector<Mat> mv;
    split(src, mv);

    // 计算直方图
    int histSize = 256;
    float range[] = { 0, 255 };
    const float* histRanges = { range };
    Mat b_hist, g_hist, r_hist;
    calcHist(&mv[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
    calcHist(&mv[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
    calcHist(&mv[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);

    Mat result = Mat::zeros(Size(600, 400), CV_8UC3);
    int margin = 50;
    int maxValue = result.rows - 2 * margin;
    // 归一化
    normalize(b_hist, b_hist, 0, maxValue, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, maxValue, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, maxValue, NORM_MINMAX, -1, Mat());

    float step = 500.0 / 256.0;
    // 绘制直方图
    for (int i = 0; i < 255; i++) {
        float bh1 = b_hist.at<float>(i, 0);
        float gh1 = g_hist.at<float>(i, 0);
        float rh1 = r_hist.at<float>(i, 0);

        float bh2 = b_hist.at<float>(i + 1, 0);
        float gh2 = g_hist.at<float>(i + 1, 0);
        float rh2 = r_hist.at<float>(i + 1, 0);

        line(result,
            Point(step * i + margin, maxValue + 50 - bh1),
            Point(step * (i + 1) + margin, maxValue + 50 - bh2),
            Scalar(255, 0, 0), 1, 8, 0);
        line(result,
            Point(step * i + margin, maxValue + 50 - gh1),
            Point(step * (i + 1) + margin, maxValue + 50 - gh2),
            Scalar(0, 255, 0), 1, 8, 0);
        line(result,
            Point(step * i + margin, maxValue + 50 - rh1),
            Point(step * (i + 1) + margin, maxValue + 50 - rh2),
            Scalar(0, 0, 255), 1, 8, 0);
    }

    imshow(name, result);
}

void hist_compare(Mat src1, Mat src2) {
    int histSize[] = { 256, 256, 256 };
    int channels[] = { 0, 1, 2 };
    Mat hist1, hist2;
    float c1[] = { 0, 255 };
    float c2[] = { 0, 255 };
    float c3[] = { 0, 255 };
    const float* histRanges[] = { c1, c2, c3 };
    calcHist(&src1, 1, channels, Mat(), hist1, 3, histSize, histRanges, true, false);
    calcHist(&src2, 1, channels, Mat(), hist2, 3, histSize, histRanges, true, false);

    // 归一化
    normalize(hist1, hist1, 0, 1.0, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, 1.0, NORM_MINMAX, -1, Mat());

    // 比较 - 巴氏距离
    double h12_bhattacharyya = compareHist(hist1, hist2, HISTCMP_BHATTACHARYYA);
    double h11_bhattacharyya = compareHist(hist1, hist1, HISTCMP_BHATTACHARYYA);

    // 比较 - 相关性比较
    double h12_correl = compareHist(hist1, hist2, HISTCMP_CORREL);
    double h11_correl = compareHist(hist1, hist1, HISTCMP_CORREL);

    printf("巴氏距离: h12 = %.2f\th11 = %.2f\n", h12_bhattacharyya, h11_bhattacharyya);
    printf("相关性: h12 = %.2f\th11 = %.2f\n", h12_correl, h11_correl);
}