/*
 * File: TemplateService.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a simple service to work with the Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on 23/Oct/2011
 * Updated on 13/Nov/2013
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BumperService.h"
#include <stdio.h>
#include "EventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "LED.h"
#include "IO_Ports.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define BATTERY_DISCONNECT_THRESHOLD 175
#define TIMER_0_TICKS 20

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */

static uint8_t MyPriority;

static uint16_t previousBumperEvents;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    previousBumperEvents = 0;
    //    printf("bumper init\n");

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    IO_PortsSetPortInputs(PORTV, PIN3);
    IO_PortsSetPortInputs(PORTV, PIN6);
    IO_PortsSetPortInputs(PORTV, PIN8);

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(BUMPER_SERVICE_TIMER, TIMER_0_TICKS);
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostBumperService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBumperService(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = BUMPER_UNPRESSED;
    ES_EventTyp_t curEvent;
    //    IO_PortsSetPortBits(PORTV, PIN4);
    uint16_t output = IO_PortsReadPort(PORTV);
    //    uint16_t a = ((((potValue >> 3)&0x1)) << 2);
    //    uint16_t b = ((((potValue >> 6)&0x1)) << 1);
    //    uint16_t c = (((potValue >> 8)&0x1));
    uint16_t leftBumper = ((output & PIN3) >> 3);
    uint16_t backBumper = ((output & PIN6) >> 6);
    uint16_t rightBumper = ((output & PIN8) >> 8);
//    uint16_t val = a | b | c;
    uint16_t val = (leftBumper << 2) + (backBumper << 1) + rightBumper;

    // printf("portf4: %d, a: %d, b: %d, c: %d\r\n", potValue,a,b,c);
    //                    504 (111111000)
    // port 8, potvalue = 248 (011111000) -> 504
    // port 6, potvalue = 440 (110111000) -> 504
    // port 4, potvalue = 488 (111101000)-> 504
    // port 6,8 potvalue = 184(010111000)
    switch (ThisEvent.EventType) {
        case ES_INIT:
            break;
        case ES_TIMERACTIVE:
            break;
        case ES_TIMERSTOPPED:
            break;
        case ES_TIMEOUT:
            ES_Timer_InitTimer(BUMPER_SERVICE_TIMER, TIMER_0_TICKS);
            //        potValue = IO_PortsReadPort(PORTV);
            if (val == 0) {
                LED_SetBank(LED_BANK1, val);
                curEvent = BUMPER_PRESSED;
            } else {
                LED_SetBank(LED_BANK1, val);
                curEvent = BUMPER_PRESSED;
            }
            //        printf("potval: %d, p4: %d, p6: %d, p8: %d, switch read %d \r\n", potValue, p4, p6, p8, val);
            if (previousBumperEvents != val) { // check for change from last time
//                printf("(%x)\n\n", val);
                ReturnEvent.EventType = curEvent;
                ReturnEvent.EventParam = val;
                previousBumperEvents = val;
                lastEvent = curEvent; // update history
                //            PostBumperService(ReturnEvent);
                PostTopHSM(ReturnEvent);
            }
            break;
        default:
            printf("\r\nEvent: %s\tParam: 0x%X",
                    EventNames[ThisEvent.EventType], ThisEvent.EventParam);
            break;
    }

    return ReturnEvent;
}



/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
