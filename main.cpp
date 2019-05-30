#include <iostream>
#include <string>
#include "PolitoceanConstants.h"
#include "Publisher.h"
#include "Subscriber.h"
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "PwmMotor.h"
#include "Controller.h"

using namespace std;
using namespace cv;
using namespace Politocean;
using namespace Politocean::RPi;
using namespace Politocean::Constants;
using namespace Politocean::Constants::MicroRov;

Controller ctrl;
PwmMotor brushlessL(&ctrl,0,1,1,1); // int dirPin - PwmPin - minPwm - maxPwm
PwmMotor brushlessR(&ctrl,0,2,2,2); // Bisogna inserire i valori sopra;

void set_vel(const std::string& velocity){
  return;
}

void set_action(const std::string& action){
  if(action.compare("start")){
    brushlessL.startPwm();
    brushlessR.startPwm();
  }
  else if(action.compare("stop")){
    brushlessL.stopPwm();
    brushlessR.stopPwm();
  }
  return;
}

int main(){
  Publisher camera_publisher(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);

  Subscriber motorSubscriber(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
 //Listener listener;

  brushlessL.setup();
  brushlessR.setup();

  motorSubscriber.subscribeTo(Constants::Topics::MICROROV_COMMANDS, &set_action);
  motorSubscriber.subscribeTo(Constants::Topics::MICROROV_VELOCITY, &set_vel);

  motorSubscriber.connect();
  camera_publisher.connect();
  sleep(3);
  vector <uchar> encoded;
  VideoCapture cap(0);
  if(!cap.isOpened()){
    camera_publisher.publish(Constants::Topics::ERRORS,"Camera Error");
    return -1;
  }   
  while(motorSubscriber.is_connected()){
    if(camera_publisher.is_connected()){
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
}


