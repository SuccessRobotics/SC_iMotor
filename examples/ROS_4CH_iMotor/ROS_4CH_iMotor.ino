#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <Wire.h>
#include <SC_iMotor.h>

SC_iMotor sc01;

ros::NodeHandle nh;

geometry_msgs::Twist msg;
std_msgs::Float32 encL_msg;
std_msgs::Float32 encR_msg;

ros::Publisher EncL("Enc_L", &encL_msg);
ros::Publisher EncR("Enc_R", &encR_msg);

long newPositionL;
long newPositionR;
long oldPositionL  = 0;
long oldPositionR  = 0;

void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{

  double x = cmd_vel.linear.x;
  double z = cmd_vel.angular.z;

  double moveL = x + (z / 2);
  double moveR = x - (z / 2);


  if (moveL > 0.0) {
    sc01.motor(1, max(min(moveL * 100, 60), 15), 1);
  } else if (moveL < 0.0) {
    sc01.motor(1, max(min(moveL * 100, 60), 15), 0);
  } else {
    sc01.motor(1, 0, 0);
  }

  if (moveR > 0.0) {
    sc01.motor(2, max(min(moveR * 100, 60), 15), 0);
  } else if (moveR < 0.0) {
    sc01.motor(2, max(min(moveR * 100, 60), 15), 1);
  } else {
    sc01.motor(2, 0, 0);
  }

}

ros::Subscriber <geometry_msgs::Twist> Motor("/cmd_vel", roverCallBack);

void setup()
{
  Wire.onReceive(receiveEvent);

  nh.initNode();
  nh.subscribe(Motor);
  nh.advertise(EncL);
  nh.advertise(EncR);
}

void loop()
{
  newPositionL = sc01.Enc1_Read();
  newPositionR = sc01.Enc2_Read() * -1;

  if (newPositionL != oldPositionL) {
    oldPositionL = newPositionL;
    encL_msg.data = newPositionL;
  }
  if (newPositionR != oldPositionR) {
    oldPositionR = newPositionR;
    encR_msg.data = newPositionR;
  }
  if ((newPositionL > 1000000) || (newPositionR > 1000000) || (newPositionL < -1000000) || (newPositionR < -1000000)) {
    sc01.Enc_Clear();
  }
  EncL.publish( &encL_msg );
  EncR.publish( &encR_msg );
  nh.spinOnce();
  delay(10);
}

void receiveEvent(int howMany)
{
  sc01.EncoderRead();
}
