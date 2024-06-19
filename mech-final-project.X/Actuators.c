/*
 * File:   Actuators.c
 * Author: shrey
 *
 * Created on May 14, 2024, 5:50 PM
 */

#include <BOARD.h>
#include <AD.h>
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "serial.h"
#include "pwm.h"
#include "IO_Ports.h"
#include "LED.h"
#include "RC_Servo.h"
#include "Actuator.h"

// DELAYS 
int wait = 0;
#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       18300
#define A_BIT_MORE  36600
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       183000
#define MOTOR_TIME (A_LOT<<2)

// MOTORS
#define MOTOR_PORT PORTY
#define MAX_MOTOR_SPEED 100

#define INTAKE_MOTOR PWM_PORTZ06
#define INTAKE_INPUT1 PIN3
#define INTAKE_INPUT2 PIN4
//#define INTAKE_MOTOR PWM_PORTY12
//#define INTAKE_INPUT1 PIN6
//#define INTAKE_INPUT2 PIN7

#define LEFT_DRIVE_MOTOR PWM_PORTY12
#define LEFT_INPUT1 PIN6
#define LEFT_INPUT2 PIN7
//#define LEFT_DRIVE_MOTOR PWM_PORTY04
//#define LEFT_INPUT1 PIN3
//#define LEFT_INPUT2 PIN4

#define RIGHT_DRIVE_MOTOR PWM_PORTY10
#define RIGHT_INPUT1 PIN8
#define RIGHT_INPUT2 PIN9

// RC SERVO 
#define RC_SERVO_PIN RC_PORTW08

void motorInit() {
    // MOTORS
    PWM_AddPins(INTAKE_MOTOR);
    IO_PortsSetPortOutputs(PORTZ, INTAKE_INPUT1);
    IO_PortsSetPortOutputs(PORTZ, INTAKE_INPUT2);
    PWM_AddPins(LEFT_DRIVE_MOTOR);
    IO_PortsSetPortOutputs(PORTY, LEFT_INPUT1);
    IO_PortsSetPortOutputs(PORTY, LEFT_INPUT2);
    PWM_AddPins(RIGHT_DRIVE_MOTOR);
    IO_PortsSetPortOutputs(PORTY, RIGHT_INPUT1);
    IO_PortsSetPortOutputs(PORTY, RIGHT_INPUT2);

    PWM_SetFrequency(1000);
}

void servoInit() {
    RC_Init();
    RC_AddPins(RC_SERVO_PIN);
}

void Intake(int newIntakeSpeed) {
    IntakeMotorSpeed(newIntakeSpeed);
}

void ServoUp() {
    RC_SetPulseTime(RC_SERVO_PIN, 1000);
}

void ServoDown() {
    RC_SetPulseTime(RC_SERVO_PIN, 2000);
}

void Drive(int newLeftSpeed, int newRightSpeed) {
    LeftMotorSpeed(newLeftSpeed);
    RightMotorSpeed(newRightSpeed);
    //    IntakeMotorSpeed(newRightSpeed);
}

int LeftMotorSpeed(int newSpeed) {
    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED) {
        return ERROR;
    }
    //newSpeed = -newSpeed;
    if (newSpeed < 0) {
        //        PORTY03_LAT = 0;
        //        PORTY04_LAT = 1;
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_INPUT1);
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_INPUT2);
        newSpeed = newSpeed * (-1);
    } else {
        //        PORTY03_LAT = 1;
        //        PORTY04_LAT = 0;
        IO_PortsClearPortBits(MOTOR_PORT, LEFT_INPUT2);
        IO_PortsSetPortBits(MOTOR_PORT, LEFT_INPUT1);
    }
    if (PWM_SetDutyCycle(LEFT_DRIVE_MOTOR, newSpeed * (MAX_PWM / MAX_MOTOR_SPEED)) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);
}

int RightMotorSpeed(int newSpeed) {
    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED) {
        return ERROR;
    }
    //newSpeed = -newSpeed;
    if (newSpeed < 0) {
        //        PORTY03_LAT = 0;
        //        PORTY04_LAT = 1;
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_INPUT1);
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_INPUT2);
        newSpeed = newSpeed * (-1);
    } else {
        //        PORTY03_LAT = 1;
        //        PORTY04_LAT = 0;
        IO_PortsClearPortBits(MOTOR_PORT, RIGHT_INPUT2);
        IO_PortsSetPortBits(MOTOR_PORT, RIGHT_INPUT1);
    }
    if (PWM_SetDutyCycle(RIGHT_DRIVE_MOTOR, newSpeed * (MAX_PWM / MAX_MOTOR_SPEED)) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);
}

int IntakeMotorSpeed(int newSpeed) {

    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED) {
        return ERROR;
    }
    newSpeed = -newSpeed;
    if (newSpeed < 0) {
        //        PORTY03_LAT = 0;
        //        PORTY04_LAT = 1;
        IO_PortsClearPortBits(PORTZ, INTAKE_INPUT1);
        IO_PortsSetPortBits(PORTZ, INTAKE_INPUT2);
        newSpeed = newSpeed * (-1);
    } else {
        //        PORTY03_LAT = 1;
        //        PORTY04_LAT = 0;
        IO_PortsClearPortBits(PORTZ, INTAKE_INPUT2);
        IO_PortsSetPortBits(PORTZ, INTAKE_INPUT1);
    }
    //        PORTY03_LAT = 0;
    //    PORTY04_LAT = 1;
    //            IO_PortsClearPortBits(MOTOR_PORT, INTAKE_INPUT2);
    //        IO_PortsSetPortBits(MOTOR_PORT, INTAKE_INPUT1);
    if (PWM_SetDutyCycle(INTAKE_MOTOR, newSpeed * (MAX_PWM / MAX_MOTOR_SPEED)) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);
}

// #define ACTUATOR_TEST_HARNESS
#ifdef ACTUATOR_TEST_HARNESS

int main(void) {

    // INITIALIZATION 
    BOARD_Init();
    SERIAL_Init();
    AD_Init();
    PWM_Init();
    LED_Init();
    RC_Init();

    // MOTORS
    PWM_AddPins(INTAKE_MOTOR);
    IO_PortsSetPortOutputs(PORTY, PIN3);
    IO_PortsSetPortOutputs(PORTY, PIN5);
    PWM_AddPins(LEFT_DRIVE_MOTOR);
    IO_PortsSetPortOutputs(PORTY, PIN6);
    IO_PortsSetPortOutputs(PORTY, PIN7);
    PWM_AddPins(RIGHT_DRIVE_MOTOR);
    IO_PortsSetPortOutputs(PORTY, PIN8);
    IO_PortsSetPortOutputs(PORTY, PIN9);

    // RC SERVO
    RC_AddPins(RC_SERVO_PIN);

    // LEDs
    LED_AddBanks(0x07); // ALL LEDS
    LED_SetBank(LED_BANK1, 0x00);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    printf("\n\rACTUATOR TEST HARNESS \n");

    // MOTOR TEST
    PWM_SetFrequency(1000);

    while (1) {

        LeftMotorSpeed(100);
        RightMotorSpeed(100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(100);
        RightMotorSpeed(100);
        DELAY(MOTOR_TIME);
        RightMotorSpeed(100);
        LeftMotorSpeed(100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(100);
        RightMotorSpeed(100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(100);
        RightMotorSpeed(100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(100);
        RightMotorSpeed(100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);
        DELAY(MOTOR_TIME);
        LeftMotorSpeed(-100);
        RightMotorSpeed(-100);

        // SERVO TEST (servo pulse range from 500 - 2400 so need to change value in header file)
        //RC_SetPulseTime(RC_SERVO_PIN, 1000);
        ServoUp();
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        //RC_SetPulseTime(RC_SERVO_PIN, 2000);
        ServoDown();
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
        DELAY(MOTOR_TIME);
    }
    return 0;
}
#endif