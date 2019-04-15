#include <iostream>
#include "rovmqtt.h"
#include <Publisher.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(){
  
  Publisher camera_publisher(HOST_ROV,PUBLISHERID); 
  camera_publisher.connect();
  sleep(3);
  vector <uchar> encoded;
  VideoCapture cap(0);
  if(!cap.isOpened()){
    camera_publisher.publish(ERROR_TOPIC,CAMERA_ERROR);
    return -1;
  }   
  while(1){
    Mat frame, decoded_frame;
    cap >> frame;
    if(frame.size().width==0)continue;
    imencode(".jpg", frame, encoded);
    string str(encoded.begin(),encoded.end());
    camera_publisher.publish(CAMERA_TOPIC,str);
    sleep(.1);
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
}


