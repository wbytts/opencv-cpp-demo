#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void chuli(Mat );

int main(int argc, char** argv)
{
    //VideoCapture capture(0);
    VideoCapture capture("rtsp://admin:123456@192.168.0.102:8554/live");
    if (!capture.isOpened()) {
        printf("Could not open the camera...\n");
    }
    namedWindow("frame", WINDOW_AUTOSIZE);
    int fps = capture.get(CAP_PROP_FPS);
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
    int type = capture.get(CAP_PROP_FOURCC);
    printf("size: %d x %d, fps: %d, frames: %d \n", width, height, fps, num_of_frames);

    Mat frame;
    // 视频写入对象
    VideoWriter writer("f:/images/camera.mp4", type, fps, Size(width, height), true);

    while (true) {
        bool ret = capture.read(frame);
        if (!ret) break;
        imshow("frame", frame);
        // 视频写入
        writer.write(frame);
        char c = waitKey(50);
        if (c == 27) {
            break;
        }
    }

    // 释放
    capture.release();
    writer.release();

    waitKey(0);
    destroyAllWindows();

    return 0;
}


