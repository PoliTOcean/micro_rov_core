#include <iostream>
#include "PolitoceanConstants.h"
#include <Publisher.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;
using namespace Politocean::Constants;

int main(){
  
  Publisher camera_publisher(MicroRov::HOST_ADDRESS, MicroRov::PUBLISHERID); 
  camera_publisher.connect();
  sleep(3);
  vector <uchar> encoded;
  VideoCapture cap(0);
  if(!cap.isOpened()){
    camera_publisher.publish(Topics::ERRORS, MicroRov::CAMERA_ERROR);
    return -1;
  }   
  while(1){
    Mat frame, decoded_frame;
    cap >> frame;
    if(frame.size().width==0)continue;
    imencode(".jpg", frame, encoded);
    string str(encoded.begin(),encoded.end());
    camera_publisher.publish(Topics::MICRO_ROV_CAMERA, str);
    sleep(.1);
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
}


