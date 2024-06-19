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
#include "IrService.h"
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

#define TIMER_0_TICKS 10

static uint16_t lastVal;

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
uint8_t InitIrService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    //    printf("ir init\n");

    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    IO_PortsSetPortOutputs(PORTX, PIN3);
    IO_PortsSetPortOutputs(PORTX, PIN4);
    IO_PortsSetPortOutputs(PORTX, PIN5);
    IO_PortsSetPortOutputs(PORTX, PIN6);
    IO_PortsSetPortInputs(PORTX, PIN10);
    IO_PortsSetPortInputs(PORTX, PIN9);
    IO_PortsSetPortInputs(PORTX, PIN8);
    IO_PortsSetPortInputs(PORTX, PIN7);
    lastVal = 0;
    AD_AddPins(AD_PORTW5);

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(IR_SERVICE_TIMER, TIMER_0_TICKS);
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
uint8_t PostIrService(ES_Event ThisEvent) {
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
ES_Event RunIrService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = TAPE_UNSENSED;
    ES_EventTyp_t curEvent;
    //    IO_PortsSetPortBits(PORTX, PIN4);
    //    uint16_t output = IO_PortsReadPort(PORTX);0x1111000000
    uint16_t output = IO_PortsReadPort(PORTX);
//    printf("output: %d", output);
    //    uint16_t frontL = ~((((output & PIN7)>>7)&0x1)^0x1); // output port7
    //    uint16_t frontR = ~(((((output & PIN8)>>8)&0x1)^0x1)<<1); // output port8
    //    uint16_t backL = ((((output & PIN9)>>9)&0x1)^0x1)<<2; // output port9
    //    uint16_t backR = ((((output & PIN10)>>10)&0x1)^0x1)<<3; // output port10   
    uint16_t frontL = ((output & PIN7) >> 7);
    uint16_t frontR = ((output & PIN8) >> 8);
    uint16_t backL = ((output & PIN9) >> 9);
    uint16_t backR = ((output & PIN10) >> 10);
    uint16_t val = frontL + (frontR << 1) + (backL << 2)+ (backR << 3);
    switch (ThisEvent.EventType) {
        case ES_INIT:
            IO_PortsSetPortBits(PORTX, PIN3); // port 3 enable frontL
            IO_PortsSetPortBits(PORTX, PIN4); // port 4 enable frontR
            IO_PortsSetPortBits(PORTX, PIN5); // port 5 enable backL
            IO_PortsSetPortBits(PORTX, PIN6); // port 6 enable backR
            //            printf("initing\n");
            break;
        case ES_TIMERACTIVE:
            //            printf("timer activing\n");
            break;
        case ES_TIMERSTOPPED:
            //            printf("timer stopped\n");
            break;
        case ES_TIMEOUT:
            
//            printf("%d\n\n", AD_ReadADPin(AD_PORTW5));
            
            ES_Timer_InitTimer(IR_SERVICE_TIMER, TIMER_0_TICKS);
            if (val > 0) {
                LED_SetBank(LED_BANK2, 0xF);
                curEvent = TAPE_SENSED;
            } else {
                LED_SetBank(LED_BANK2, 0x0);
                curEvent = TAPE_SENSED;
            }
//            printf("%d penis ", output);
//            printf("output: %d, potval: %d, p7: %d, p8: %d, p9: %d, p10: %d\r\n", output, val, frontL, frontR, backL, backR);
            if (val != lastVal) { // check for change from last time
                lastVal = val;
                ReturnEvent.EventType = curEvent;
                ReturnEvent.EventParam = val;
                lastEvent = curEvent; // update history
                //            PostIrService(ReturnEvent);
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

