#include "SC_iMotor.h"
#include "Arduino.h"
#include "Wire.h"

SC_iMotor::SC_iMotor()
{
  Wire.begin(4);

  for (int clearcmd = 0; clearcmd <= 30; clearcmd++)
  {
    cmd_i2c[clearcmd ] = 0;
  }
}

void SC_iMotor::senddata_I2C(byte cmd0 , byte cmd1, byte cmd2, byte cmd3, byte cmd4, byte cmd5, byte cmd6, byte cmd7)
{
  Wire.beginTransmission(4);
  Wire.write(cmd0);
  Wire.write(cmd1);
  Wire.write(cmd2);
  Wire.write(cmd3);
  Wire.write(cmd4);
  Wire.write(cmd5);
  Wire.write(cmd6);
  Wire.write(cmd7);
  Wire.endTransmission();
}

void SC_iMotor::ControlMotor(byte Motor, byte directions, byte speeds)
{

  byte i;
  if (Motor < 80 )
  {
    i = Motor - 65; Motor = Motor + (directions * 32);
  }
  else
  {
    i = Motor - 97; Motor = Motor + (directions * -32);
  }
  Outcmd[i] = Motor;
  Outcmd[i + 4] = speeds;

  senddata_I2C(Outcmd[0], Outcmd[1], Outcmd[2], Outcmd[3], Outcmd[4], Outcmd[5], Outcmd[6], Outcmd[7]);
}

void SC_iMotor::EncoderRead()
{
  while (1 < Wire.available())
  {
    cmd_i2c[loop_input] = Wire.read();
    loop_input++;
  }
  cmd_i2c[loop_input] = Wire.read();
  loop_input = 0;
}

int32_t SC_iMotor::Enc1_Read()
{
  encoder[1] = cmd_i2c[4];
  encoder[2] = cmd_i2c[5];
  encoder[3] = cmd_i2c[6];
  
  encoder[2] = encoder[2] * 256; 
  encoder[3] = encoder[3] * 65536;

  Encode1 = encoder[1] + encoder[2] + encoder[3];


  if (cmd_i2c[0] > 80) Encode1 = Encode1 * -1;
  return Encode1;
}

void SC_iMotor::Enc1_Clear()
{
	senddata_I2C(69, Outcmd[1], Outcmd[2], Outcmd[3], Outcmd[4], Outcmd[5], Outcmd[6], Outcmd[7]);
	cmd_i2c[4] = 0;
	cmd_i2c[5] = 0;
	cmd_i2c[6] = 0;
}

void SC_iMotor::Enc2_Clear()
{
	senddata_I2C(Outcmd[0], 70, Outcmd[2], Outcmd[3], Outcmd[4], Outcmd[5], Outcmd[6], Outcmd[7]);
	cmd_i2c[7] = 0;
	cmd_i2c[8] = 0;
	cmd_i2c[9] = 0;

}

void SC_iMotor::Enc3_Clear()
{
	senddata_I2C(Outcmd[0], Outcmd[1],70 , Outcmd[3], Outcmd[4], Outcmd[5], Outcmd[6], Outcmd[7]);
	cmd_i2c[10] = 0;
	cmd_i2c[11] = 0;
	cmd_i2c[12] = 0;
}

void SC_iMotor::Enc4_Clear()
{
	senddata_I2C(Outcmd[0], Outcmd[1], Outcmd[2], 71, Outcmd[4], Outcmd[5], Outcmd[6], Outcmd[7]);
	cmd_i2c[13] = 0;
	cmd_i2c[14] = 0;
	cmd_i2c[15] = 0;

}


int32_t SC_iMotor::Enc2_Read()
{
  encoder[4] = cmd_i2c[7];
  encoder[5] = cmd_i2c[8];
  encoder[6] = cmd_i2c[9];
  
  encoder[5] = encoder[5] * 256; 
  encoder[6] = encoder[6] * 65536;

  Encode2 = encoder[4] + encoder[5] + encoder[6];


  if (cmd_i2c[1] > 80) Encode2 = Encode2 * -1;
  return Encode2;
}

int32_t SC_iMotor::Enc3_Read()
{
  encoder[7] = cmd_i2c[10];
  encoder[8] = cmd_i2c[11];
  encoder[9] = cmd_i2c[12];
  
  encoder[8] = encoder[8] * 256; 
  encoder[9] = encoder[9] * 65536;

  Encode3 = encoder[7] + encoder[8] + encoder[9];


  if (cmd_i2c[2] > 80) Encode3 = Encode3 * -1;
  return Encode3;
}

int32_t SC_iMotor::Enc4_Read()
{
  encoder[10] = cmd_i2c[13];
  encoder[11] = cmd_i2c[14];
  encoder[12] = cmd_i2c[15];
  
  encoder[11] = encoder[11] * 256; 
  encoder[12] = encoder[12] * 65536;

  Encode4 = encoder[10] + encoder[11] + encoder[12];

  if (cmd_i2c[3] > 80)  Encode4 = Encode4 * -1;
  return Encode4;
}

void SC_iMotor::setmotor_Diff(int M1, int M2, bool reverse1, bool reverse2)
{
  if (M1 == 1) Motor1 = 65;
  if (M1 == 2) Motor1 = 66;
  if (M1 == 3) Motor1 = 67;
  if (M1 == 4) Motor1 = 68;

  if (M2 == 1) Motor2 = 65;
  if (M2 == 2) Motor2 = 66;
  if (M2 == 3) Motor2 = 67;
  if (M2 == 4) Motor2 = 68;

  Mode = 0;

  if (reverse1 == true) Motor1 += 32;
  if (reverse2 == true) Motor2 += 32;
}

void SC_iMotor::setmotor_Holonomic(int M1, int M2,int M3 ,bool reverse1, bool reverse2, bool reverse3)
{
  if (M1 == 1) Motor1 = 65;
  if (M1 == 2) Motor1 = 66;
  if (M1 == 3) Motor1 = 67;
  if (M1 == 4) Motor1 = 68;

  if (M2 == 1) Motor2 = 65;
  if (M2 == 2) Motor2 = 66;
  if (M2 == 3) Motor2 = 67;
  if (M2 == 4) Motor2 = 68;

  if (M2 == 1) Motor3 = 65;
  if (M2 == 2) Motor3 = 66;
  if (M2 == 3) Motor3 = 67;
  if (M2 == 4) Motor3 = 68;


  Mode = 1;

  if (reverse1 == true) Motor1 += 32;
  if (reverse2 == true) Motor2 += 32;
  if (reverse3 == true) Motor3 += 32;
}


void SC_iMotor::motor_direct(int speeds)
{
  if (Mode == 0)
  {
    if (speeds > 0)
    {
      ControlMotor(Motor1, 0, abs(speeds));
      ControlMotor(Motor2, 0, abs(speeds));
    }
    else
    {
      ControlMotor(Motor1, 1, abs(speeds));
      ControlMotor(Motor2, 1, abs(speeds));
    }
  }
  if (Mode == 1)
  {
	
  }
}

void SC_iMotor::motor_rota(int degree, int speeds)
{
  if (Mode == 0)
  {
    degree = map(degree, 0, 100, 0, speeds);

    MR = speeds + (degree * 2);
    ML = speeds - (degree * 2);
    if (MR > speeds ) {
      MR = speeds ;
    }
    if (MR < -speeds ) {
      MR = -speeds ;
    }
    if (ML > speeds ) {
      ML = speeds ;
    }
    if (ML < -speeds ) {
      ML = -speeds ;
    }

    if (MR > 0) ControlMotor(Motor1, 0, abs(MR));
    else ControlMotor(Motor1, 1, abs(MR));

    if (ML > 0) ControlMotor(Motor2, 0, abs(ML));
    else ControlMotor(Motor2, 1, abs(ML));
  }
}

void SC_iMotor::motor(int motor, int speeds, int reverse)
{
  motor += 64;
  if (reverse == true) motor += 32;
  if(speeds >= 0)
  {
    ControlMotor(motor , 0, abs(speeds ));
  }
  else
  {
    ControlMotor(motor , 1, abs(speeds ));

  }
}

