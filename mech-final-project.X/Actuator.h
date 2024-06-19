/*
 * File: Actuator.h
 * Author: Shreya 
 *
 * Created on 20/May/2024
 */

#ifndef ACTUATOR_H
#define	ACTUATOR_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

void motorInit();

void servoInit();

void Drive(int newLeftSpeed, int newRightSpeed);

void Intake(int newIntakeSpeed);

int LeftMotorSpeed(int newSpeed);

int RightMotorSpeed(int newSpeed);

int IntakeMotorSpeed(int newSpeed);

void ServoUp();

void ServoDown();


#endif	/* ACTUATOR_H */

