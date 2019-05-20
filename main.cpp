#include <iostream>
<<<<<<< Updated upstream
#include "rovmqtt.h"
#include <Publisher.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(){
  
  Publisher camera_publisher(HOST_ROV,PUBLISHERID); 
=======
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
PwmMotor motor1(&ctrl,0,1,1,1); // int dirPin - PwmPin - minPwm - maxPwm
PwmMotor motor2(&ctrl,0,2,2,2); // Bisogna inserire i valori sopra;

motor1.setup();
motor2.setup();

void set_vel(const std::string& velocity){
  return;
}

void set_action(const std::string& action){
  if(action.compare("start")){
    motor1.startPwm();
    motor2.startPwm();
  }
  else if(action.compare("stop")){
    motor1.stopPwm();
    motor2.stopPwm();
  }
  return;
}

int main(){
  Publisher camera_publisher(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
  Subscriber MotorSubscriber(Constants::MicroRov::IP_ADDRESS, Constants::MicroRov::MICRO_ROV_ID);
  MotorSubscriber.subscribeTo(Constants::Topics::MICROROV_COMMANDS, &set_action);
  MotorSubscriber.subscribeTo(Constants::Topics::MICROROV_VELOCITY, &set_vel);
  MotorSubscriber.connect();
>>>>>>> Stashed changes
  camera_publisher.connect();
  sleep(3);
  vector <uchar> encoded;
  VideoCapture cap(0);
  if(!cap.isOpened()){
    camera_publisher.publish(ERROR_TOPIC,CAMERA_ERROR);
    return -1;
  }   
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
  }
}


