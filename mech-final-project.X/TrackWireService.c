/*
 * File: TrackWireService.h
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
#include "TrackWireService.h"
#include <stdio.h>
#include "LED.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//int wait = 0;
//#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define BATTERY_DISCONNECT_THRESHOLD 175
#define TIMER_0_TICKS 100
#define TRACK_WIRE_1_OUT AD_PORTW3 
#define TRACK_WIRE_2_OUT AD_PORTW4
#define MAX_AVERAGE_VAL -2
#define NUM_READINGS 20  // Change to 10 or 20 depending on your preference

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

#define BUFFER_SIZE 8
static int circularBuffer[BUFFER_SIZE];
static int buffer_idx;

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
uint8_t InitTrackWireService(uint8_t Priority) {
    ES_Event ThisEvent;

    MyPriority = Priority;
    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    ES_Timer_InitTimer(TRACK_SERVICE_TIMER, TIMER_0_TICKS);

    buffer_idx = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
        circularBuffer[i] = 0;

    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTrackWireService(ES_Event ThisEvent) {
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
ES_Event RunTrackWireService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = TRACK_WIRE_NOT_DETECTED;
    ES_EventTyp_t curEvent;
    uint16_t trackWireVal = AD_ReadADPin(TRACK_WIRE_1_OUT); // read the output of the track wire
    int trackWireAverage;

    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            // This section is used to reset service for some reason
            break;

        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break;

        case ES_TIMEOUT:
            ES_Timer_InitTimer(TRACK_SERVICE_TIMER, TIMER_0_TICKS);

            buffer_idx++;
            if (buffer_idx == BUFFER_SIZE) {
                buffer_idx = 0;
            }
            circularBuffer[buffer_idx] = trackWireVal;

            trackWireAverage = 0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                trackWireAverage += circularBuffer[i];
            }
            trackWireAverage = (int) (trackWireAverage / BUFFER_SIZE);

//            printf("\n Raw Reading: %d\t Average: %d\n", trackWireVal, trackWireAverage);

            if (trackWireAverage < 900) { // if the output is less than the max voltage
                curEvent = TRACK_WIRE_DETECTED;
                //            LED_SetBank(LED_BANK3, 0xFF);
            } else {
                curEvent = TRACK_WIRE_NOT_DETECTED;
                //            LED_SetBank(LED_BANK3, 0x00); 
            }
            if (curEvent != lastEvent) { // check for change from last time
                ReturnEvent.EventType = curEvent;
                ReturnEvent.EventParam = trackWireVal;
                lastEvent = curEvent; // update history
                PostTopHSM(ReturnEvent);
            }
            break;
    }

    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
