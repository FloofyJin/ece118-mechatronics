/*
 * File:   main.c
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

// DELAYS 
int wait = 0;
#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       18300
#define A_BIT_MORE  36600
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       183000
#define MOTOR_TIME (A_LOT<<2)

// BUMPERS
#define BUMPER_PORT PORTX
#define LEFT_BUMPER PIN3
#define RIGHT_BUMPER PIN4
#define BACK_BUMPER PIN5

// TRACK WIRE
#define LEFT_TRACK_WIRE AD_PORTV3
#define RIGHT_TRACK_WIRE AD_PORTV4
#define NUM_READINGS 20 

// TAPE DETECTOR 
#define TAPE_DETECT_PORT PORTZ

#define FRONT_LEFT_TAPE_ENA PIN3
#define FRONT_LEFT_TAPE_OUT PIN4
#define FRONT_RIGHT_TAPE_ENA PIN5
#define FRONT_RIGHT_TAPE_OUT PIN6

#define BACK_LEFT_TAPE_ENA PIN7
#define BACK_LEFT_TAPE_OUT PIN8
#define BACK_RIGHT_TAPE_ENA PIN9
#define BACK_RIGHT_TAPE_OUT PIN10

// MOTORS
#define MOTOR_PORT PORTY
#define MAX_MOTOR_SPEED 100

#define INTAKE_MOTOR PWM_PORTY04
#define INTAKE_INPUT1 PIN3
#define INTAKE_INPUT2 PIN5

#define LEFT_DRIVE_MOTOR PWM_PORTY12
#define LEFT_INPUT1 PIN6
#define LEFT_INPUT2 PIN7

#define RIGHT_DRIVE_MOTOR PWM_PORTY10
#define RIGHT_INPUT1 PIN8
#define RIGHT_INPUT2 PIN9

// RC SERVO 
#define RC_SERVO_PIN 

// Note to self: example of how to read a port 
//    if (IO_PortsReadPort(BUMPER_PORT) & LEFT_BUMPER) { 
//    }

int LeftMotorSpeed(int newSpeed){
    
    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED){
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

int RightMotorSpeed(int newSpeed){
    
    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED){
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

int IntakeMotorSpeed(int newSpeed){
    
    if (newSpeed > MAX_MOTOR_SPEED || newSpeed < -MAX_MOTOR_SPEED){
        return ERROR;
    }
    //newSpeed = -newSpeed;
    if (newSpeed < 0) {
//        PORTY03_LAT = 0;
//        PORTY04_LAT = 1;
        IO_PortsClearPortBits(MOTOR_PORT, INTAKE_INPUT1);
        IO_PortsSetPortBits(MOTOR_PORT, INTAKE_INPUT2);
        newSpeed = newSpeed * (-1); 
    } else {
//        PORTY03_LAT = 1;
//        PORTY04_LAT = 0;
        IO_PortsClearPortBits(MOTOR_PORT, INTAKE_INPUT2);
        IO_PortsSetPortBits(MOTOR_PORT, INTAKE_INPUT1);
    }
    if (PWM_SetDutyCycle(INTAKE_MOTOR, newSpeed * (MAX_PWM / MAX_MOTOR_SPEED)) == ERROR) {
        return (ERROR);
    }
    return (SUCCESS);   
}

int ReadTrackWire(){
}

int ReadBumperWire(){
}


int main(void) {
    
    // INITIALIZATION 
    BOARD_Init();
    SERIAL_Init();
    AD_Init();
    PWM_Init();
    LED_Init();
    RC_Init();
    
    // BUMPERS 
    IO_PortsSetPortInputs(BUMPER_PORT, LEFT_BUMPER);
    IO_PortsSetPortInputs(BUMPER_PORT, RIGHT_BUMPER);
    IO_PortsSetPortInputs(BUMPER_PORT, BACK_BUMPER);
    
    // TRACK WIRE 
    AD_AddPins(LEFT_TRACK_WIRE); 
    AD_AddPins(RIGHT_TRACK_WIRE); 
    
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
    
    // TAPE DETECTOR
    IO_PortsSetPortOutputs(TAPE_DETECT_PORT, FRONT_LEFT_TAPE_ENA); // TAPE DETECTOR 1 ENA: PORTX6
    IO_PortsSetPortInputs(TAPE_DETECT_PORT, FRONT_LEFT_TAPE_OUT); // TAPE DETECTOR 2 OUT: PORTX7
    
    IO_PortsSetPortOutputs(TAPE_DETECT_PORT, FRONT_RIGHT_TAPE_ENA); // TAPE DETECTOR 1 ENA: PORTX6
    IO_PortsSetPortInputs(TAPE_DETECT_PORT, FRONT_RIGHT_TAPE_OUT); // TAPE DETECTOR 2 OUT: PORTX7
    
    IO_PortsSetPortOutputs(TAPE_DETECT_PORT, BACK_LEFT_TAPE_ENA); // TAPE DETECTOR 1 ENA: PORTX6
    IO_PortsSetPortInputs(TAPE_DETECT_PORT, BACK_LEFT_TAPE_OUT); // TAPE DETECTOR 2 OUT: PORTX7
    
    IO_PortsSetPortOutputs(TAPE_DETECT_PORT, BACK_RIGHT_TAPE_ENA); // TAPE DETECTOR 1 ENA: PORTX6
    IO_PortsSetPortInputs(TAPE_DETECT_PORT, BACK_RIGHT_TAPE_OUT); // TAPE DETECTOR 2 OUT: PORTX7
    
    // RC SERVO
    RC_AddPins(RC_PORTW08);
  
    // LEDs
    LED_AddBanks(0x07); // ALL LEDS
    LED_SetBank(LED_BANK1, 0x00); 
    LED_SetBank(LED_BANK2, 0x00); 
    LED_SetBank(LED_BANK3, 0x00); 
    
//    // MOVING AVERAGE FOR TRACK WIRE INIT
//    unsigned int TRACK_WIRE = 0; 
//    int readings[NUM_READINGS];
//    int readIndex = 0;
//    int total = 0;
//    int average = 0;
//    for (int i = 0; i < NUM_READINGS; i++) {
//        readings[i] = 1023;
//    }
    
    printf("\n\rSENSOR TEST HARNESS \n");  
        
    // TESTING TRACK WIRE
//        total = total - readings[readIndex]; // Subtract the last reading from the total
//        int currentReading = AD_ReadADPin(TRACK_WIRE_1_OUT); // Read the sensor value
//        readings[readIndex] = currentReading; // Store the current reading in the array
//        total = total + readings[readIndex]; // Add the current reading to the total
//        readIndex = readIndex + 1; // Move to the next position in the array
//        if (readIndex >= NUM_READINGS) { // Wrap around to the beginning if necessary
//            readIndex = 0;
//        }
//        average = total / NUM_READINGS; // Calculate the average
//        printf("Current Reading: %d, Average: %d \n\r", currentReading, average); // Print the current reading and the average
//        
//        if (average < -10) {
//            LED_SetBank(LED_BANK3, 0xFF); 
//        } else {
//            LED_SetBank(LED_BANK3, 0x00); 
//        } 
//        TRACK_WIRE = AD_ReadADPin(TRACK_WIRE_1_OUT);
//        printf("%d \n\r", TRACK_WIRE);   
//        
//        if (TRACK_WIRE < 1023) {
//            LED_SetBank(LED_BANK3, 0xFF); 
//        }
//        else {
//            LED_SetBank(LED_BANK3, 0x00); 
//        }
        
    //TESTING MOTORS
    PWM_SetFrequency(1000);
        
    while (1) {

//        // IR SENSOR TEST
//        IO_PortsSetPortOutputs(PORTX, PIN6); // setting PORTX6 to be output from uno to enable the IR sensor high
//        IO_PortsSetPortInputs(PORTX, PIN7); // setting PORTX7 to be input which takes the output of the IR sensor 
//        
//        IO_PortsSetPortBits(PORTX, PIN6);
//        
//        int16_t output;
//        int objectDetect;
//        
//        output = PORTX07_BIT; // reads PORTX7 bit
//        
//        if (output) {
//            objectDetect = 0;
//        }
//        else{
//            DELAY(210); 
//            if (output){
//                objectDetect = 0;
//            }
//            else {
//                objectDetect = 1;
//            }
//        }
//        DELAY(263);
//        printf("%d", objectDetect); 
            
//        // SERVO TEST (servo pulse range from 500 - 2400)
//        RC_SetPulseTime(RC_PORTW08, 500);
//        DELAY(MOTOR_TIME);
//        RC_SetPulseTime(RC_PORTW08, 1500);
//        DELAY(MOTOR_TIME);
        
//        // MOTOR TEST
//        LeftMotorSpeed(100);
//        RightMotorSpeed(100);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(80);
//        RightMotorSpeed(80);
//        DELAY(MOTOR_TIME);
//        RightMotorSpeed(60);
//        LeftMotorSpeed(60);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(40);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(20);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(0);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(-100);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(-80);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(-60);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(-40);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(-20);
//        DELAY(MOTOR_TIME);
//        LeftMotorSpeed(0);
    }
    return 0;
}