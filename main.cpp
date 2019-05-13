#include <iostream>
#include "PolitoceanConstants.h"
#include <Publisher.h>
#include <Subscriber.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <PwmMotor.h>
#include <Controller.h>

using namespace std;
using namespace cv;
using namespace Politocean;
using namespace Politocean::Constants;
using namespace Politocean::Constants::MicroRov;

bool action,vel;

void set_vel(const std::string& velocity){
  return;
}

void set_action(const std::string& action){
  return;
}

int main(){
  RPi::Controller ctrl1;
  RPi::Controller ctrl2;
  RPi::PwmMotor motor1(&ctrl1,0,1,1,1);
  RPi::PwmMotor motor2(&ctrl2,0,2,2,2);
  Publisher camera_publisher(Constants::Hmi::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
  Subscriber MotorSubscriber(Constants::Rov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
  MotorSubscriber.subscribeTo(Constants::Topics::MICROROV_COMMANDS, &set_action);
  MotorSubscriber.subscribeTo(Constants::Topics::MICROROV_VELOCITY, &set_vel);
  MotorSubscriber.connect();
  camera_publisher.connect();
  vector <uchar> encoded;
  VideoCapture cap(0);
  if(!cap.isOpened()){
    camera_publisher.publish(Constants::Topics::ERRORS, "Camera error");
    return -1;
  }   
  while(MotorSubscriber.is_connected()){
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
    //
  }
}


