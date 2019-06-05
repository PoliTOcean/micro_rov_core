#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

    VideoCapture cap(0);

    const double fps = cap.get(CAP_PROP_FPS);
    const int width  = cap.get(CAP_PROP_FRAME_WIDTH);
    const int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    const int fourcc = cap.get(CAP_PROP_FOURCC );

    VideoWriter out("raspivid -t 0 -cd MJPEG -w 1280 -h 720 -fps 20 -b 4000000 -o - | gst-launch-1.0 fdsrc ! \"image/jpeg,framerate=20/1\" ! jpegparse ! rtpjpegpay ! udpsink host=10.0.0.1 port=5000",fourcc, fps, cv::Size(width,height), true);

    if (!out.isOpened() || !cap.isOpened())
    {
        cout << "VideoWriter or VideoCapture not opened" << endl;
        exit(-1);
    }

    Mat frame;

    while(true) {

        cap.read(frame);

        if(frame.empty())
            break;

        out.write(frame);

    }

    return 0;
}