#ifndef SC_iMotor_H
#define SC_iMotor_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SC_iMotor
{
  public:
    	SC_iMotor();

	void motor(int motor, int speeds, int reverse);
    	void setmotor_Diff(int M1, int M2,bool reverse1,bool reverse2);
	void setmotor_Holonomic(int M1, int M2,int M3 ,bool reverse1, bool reverse2, bool reverse3);
	void motor_rota(int degree, int speeds);
	void motor_direct(int speeds);
	void EncoderRead();

	int32_t Enc1_Read();
	int32_t Enc2_Read();
	int32_t Enc3_Read();
	int32_t Enc4_Read();

     	void Enc_Clear();

  private:
	void senddata_I2C(byte cmd0 , byte cmd1, byte cmd2, byte cmd3, byte cmd4, byte cmd5, byte cmd6, byte cmd7);
	void ControlMotor(byte Motor, byte directions, byte speeds);
	
	byte Motor1;
    	byte Motor2;
    	byte Motor3;
    	byte Motor4;
	int MR;
	int ML;	

    	int Mode;
	
	byte cmd_i2c[30];
	byte Outcmd[20];
	byte loop_input;

	int32_t Encode1;
	int32_t Encode2;
	int32_t Encode3;
	int32_t Encode4;

	uint32_t encoder[15];
};

#endif
