#include <BOARD.h>
#include <AD.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "serial.h"
#include "pwm.h"
#include "IO_Ports.h"
#include "LED.h"
#include "Actuator.h"

#define TRACK_WIRE_1_OUT AD_PORTW3 
#define TRACK_WIRE_2_OUT AD_PORTW4
#define INTAKE_MOTOR PWM_PORTZ06
#define LEFT_DRIVE_MOTOR PWM_PORTY12
#define RIGHT_DRIVE_MOTOR PWM_PORTY10

void main(void) {
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");

    // Your hardware initialization function calls go here
    SERIAL_Init();
    AD_Init();
    PWM_Init();
    LED_Init();

    // ADDING PINS 
    AD_AddPins(TRACK_WIRE_1_OUT); // TRACK WIRE 1: PORTV3 
    AD_AddPins(TRACK_WIRE_2_OUT); // TRACK WIRE 2: PORTV4


    LED_AddBanks(0x07); // ALL LEDS
    LED_SetBank(LED_BANK1, 0x00);
    LED_SetBank(LED_BANK2, 0x00);
    LED_SetBank(LED_BANK3, 0x00);

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
        case FailedPointer:
            printf("Failed on NULL pointer");
            break;
        case FailedInit:
            printf("Failed Initialization");
            break;
        default:
            printf("Other Failure: %d", ErrorType);
            break;
    }
    for (;;)
        ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
