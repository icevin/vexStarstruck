#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potCL,          sensorPotentiometer)
#pragma config(Sensor, in2,    potCR,          sensorPotentiometer)
#pragma config(Sensor, dgtl1,  touchSensL,     sensorTouch)
#pragma config(Sensor, dgtl2,  touchSensR,     sensorTouch)
#pragma config(Sensor, dgtl6,  quadL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  quadR,          sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           clawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           dLeftF, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           dLeftB, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           armL1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           armL2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           armR1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armR2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           dRightF, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           dRightB, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          clawR,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)

#define LOOPSPEED 50 //Time between user control loops in milliseconds - time alloted to other tasks while usercontrol is idle
#define DEADZONE 20 //Deadzone for joystick control
#define m_clawL 1
#define m_dLeftF 2
#define m_dLeftB 3
#define m_armL1 4
#define m_armL2 5
#define m_armR1 6
#define m_armR2 7
#define m_dRightF 8
#define m_dRightB 9
#define m_clawR 10

#define joy_left_vertical "Ch3"
#define joy_left_horizontal "Ch4"
#define joy_right_vertical "Ch2"
#define joy_right_horizontal "Ch1"

//GLOBAL VARIABLES
float powerExpanderBatteryV;
//Control variables
int dlC, drC, armC, forwardsC, backwardsC, musicCtrl;
int armMotors;
unsigned int beat = 0;

#include "Vex_Competition_Includes.c"
#include "music.h"
#include "StarstruckIncludes.h"
//#include "motor.c"





void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.

	bStopTasksBetweenModes = true;
}

task autonomous()
{
	wait1Msec(2500);
}

task nonMusic() {
	nSchedulePriority = 10;
	//Math variables
	int lastArmC, currArmC;

	int mReqD1, mReqD2, mReqD3, mReqD4;
	while(true){

		int joyLV = vexRT[Ch3];
		int joyLH = vexRT[Ch4];
		int joyRV = vexRT[Ch2];
		int joyRH = vexRT[Ch1];

		armC = vexRT[Ch2Xmtr2];
		forwardsC = vexRT[Btn7U];
		backwardsC = vexRT[Btn7D];

		musicCtrl = vexRT[Btn7UXmtr2];

	mReqD1 = vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4];
	mReqD2 = vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
	mReqD3 = vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4];
	mReqD4 = vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4];


	if(abs(mReqD1) > DEADZONE)
		motor[dLeftF] = mReqD1;
	else
		motor[dLeftF] = 0;

	if(abs(mReqD2) > DEADZONE)
		motor[dRightF] = mReqD2;
	else
		motor[dRightF] = 0;

	if(abs(mReqD3) > DEADZONE)
		motor[dLeftB] = mReqD3;
	else
		motor[dLeftB] = 0;

	if(abs(mReqD4) > DEADZONE)
		motor[dRightB] = mReqD4;
	else
		motor[dRightB] = 0;

		lastArmC = currArmC;
		currArmC = armC;

		if(abs(armC) > DEADZONE) {
			armMotors = armC;
			} else {
			armMotors = 0;
		}






		//Set Motors
		motor[armL1] = armMotors;
		motor[armL2] = armMotors;
		motor[armR1] = armMotors;
		motor[armR2] = armMotors;







		//Displays Battery Levels to VEX Remote Screen
		powerExpanderBatteryV = SensorValue[in1]/.28;
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0,0);
		displayNextLCDString("C Bat:");
		displayNextLCDNumber(nAvgBatteryLevel);
		displayLCDPos(1,0);
		displayNextLCDString("P.E Bat:");
		displayNextLCDNumber(powerExpanderBatteryV);

		wait1Msec(LOOPSPEED);
	}
}
/*
task motorSlewRate() {

}*/

task usercontrol()
{
	startTask(music);
	startTask(nonMusic);
	//startTask(motorSlew);
}
