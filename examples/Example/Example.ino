#include <Wire.h>
#include <SC_iMotor.h>

SC_iMotor sc01;

void setup() 
{
  Serial.begin(9600);
  
  Wire.onReceive(receiveEvent); // register event
}

void loop() 
{
  //sc01.motor(Motor number, Speed -100 to 100, reverse : 0 - false | 1 - true)
  sc01.motor(1, 100, 0);
  sc01.motor(2, 100, 0);
  sc01.motor(3, 100, 0);
  sc01.motor(4, 100, 0);
  delay(1000);

  Serial.print("Encoder 1 : ");
  Serial.print(sc01.Enc1_Read());
  Serial.print(" Encoder 2 : ");
  Serial.print(sc01.Enc2_Read());
  Serial.print(" Encoder 3 : ");
  Serial.print(sc01.Enc3_Read());
  Serial.print(" Encoder 4 : ");
  Serial.println(sc01.Enc4_Read());

  sc01.motor(1, 0, 0);
  sc01.motor(2, 0, 0);
  sc01.motor(3, 0, 1);
  sc01.motor(4, 0, 1);
  delay(1000);

  sc01.Enc_Clear();
  
}

void receiveEvent(int howMany)
{
  sc01.EncoderRead();
}
