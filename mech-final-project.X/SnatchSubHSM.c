/*
 * File: SnatchSubHSM.h
 * Author: Eric Vetha
 * Modified: Shreya Sinha
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopHSM.h"
#include "SnatchSubHSM.h"
#include "Actuator.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define TURN_SPEED_100 90
#define TURN_SPEED_0 0

#define MS_HALFWAY 500
#define PL1 90
#define PR1 82
#define PL2 85
#define PR2 90

#define WATCH_DOG_TIMER 3000

static int rotationsDone;

typedef enum {
    InitSnatchState,
    DueWest1,
    DueWest2,
    West_SlideDownTape_AlignLeft,
    West_SlideDownTape_AlignRight,
    West_ButtWink_FindTape,
    West_ButtWink_GoBack,
    ButtWink_Reset,
    West_SlideDownTape0, // front right tape off
    West_SlideDownTape1, // back right tape on
    West_SlideDownTape2, // align back left 
    West_SlideDownTape3, // align back right
    West_SlideDownTape_AlignBackLeft,
    West_SlideDownTape_AlignBackRight,
    West_SlideDownTape_AlignBackRight2,
    West_Collision_Buffer,
    West_Collision_BackUp1,
    West_Collision_BackUp2,
    West_Collision_AlignLeft,
    West_Collision_AlignRight,
    West_Collision_SlideDown,
    West_Collision_TurnAround1,
    West_Collision_TurnAround2,
    West_Collision_TurnAround3,
    West_Collision_TurnAround4,
    West_Collision_Realign,
    DueEast1,
    DueEast2,
    East_SlideDownTape_AlignLeft,
    East_SlideDownTape_AlignRight,
    East_SlideDownTape0, // front right tape off
    East_SlideDownTape1, // back right tape on
    East_SlideDownTape2, // align back left 
    East_SlideDownTape3, // align back right
    East_SlideDownTape_AlignBackLeft,
    East_SlideDownTape_AlignBackRight,
    East_SlideDownTape_AlignBackRight2,
    East_Collision_Buffer,
    East_Collision_BackUp1,
    East_Collision_BackUp2,
    East_Collision_AlignLeft,
    East_Collision_AlignRight,
    East_Collision_SlideDown,
    East_Collision_TurnAround1,
    East_Collision_TurnAround2,
    East_Collision_TurnAround3,
    East_Collision_TurnAround4,
    East_Collision_Realign,
    BackUp,

    // New States
    DueWest_Onwards,
    DueWest_BackUp,
    DueEast_Onwards,
    DueEast_BackUp,
    Halt,
} SnatchSubHSMState_t;

static const char *StateNames[] = {
    "InitSnatchState",
    "DueEast",
    "DueWest",
    "West_SlideDownTape_AlignLeft",
    "West_SlideDownTape_AlignRight",
    "West_SlideDownTape0",
    "West_SlideDownTape1",
    "West_SlideDownTape2",
    "West_SlideDownTape3",
    "West_SlideDownTape_AlignBackLeft",
    "West_SlideDownTape_AlignBackRight",
    "Halt",
};

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SnatchSubHSMState_t CurrentState = InitSnatchState; // <- change name to match ENUM
static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitSnatchSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitSnatchState;
    returnEvent = RunSnatchSubHSM(INIT_EVENT);

    rotationsDone = 0;

    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunSnatchSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SnatchSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitSnatchState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT) // only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = DueWest_Onwards;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case DueWest_Onwards:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(90, 60);
                    ES_Timer_InitTimer(SNATCH_TIMER, WATCH_DOG_TIMER);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        nextState = West_SlideDownTape1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (BUMPER_PRESSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BUMP) {
                        nextState = DueWest_BackUp;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    if (ThisEvent.EventParam & FRONT_LEFT_BUMP) {
                        nextState = DueWest_BackUp; // failed most likely
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueWest_BackUp; // 50/50 failed
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case DueWest_BackUp:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-90, 0);
                    ES_Timer_StopTimer(SNATCH_TIMER);
                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        if (rotationsDone < 2) {
                            nextState = DueWest_Onwards; // 50/50 failed
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = SNATCH_COMPLETE;
                        }
                    }
                    break;
            }
            break;

        case West_SlideDownTape0:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
                    break;
                case (TAPE_SENSED):
                    if (~(ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
                        nextState = West_SlideDownTape1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case West_SlideDownTape1:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
                    ES_Timer_InitTimer(SNATCH_TIMER, 4000);
                    break;
                case (TAPE_SENSED):
                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                    //                        nextState = Halt;
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                        break;
                    //                    }
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        rotationsDone++;
                        nextState = DueEast_Onwards;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueWest_BackUp; // 50/50 failed
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case West_SlideDownTape2:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    //                    Drive(90, 50);
                    Drive(90, 90);
                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
                    rotationsDone++;
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        if (rotationsDone < 4) {
                            nextState = West_SlideDownTape3;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = SNATCH_COMPLETE;
                        }
                        break;
                    }
                    break;
            }
            break;

        case West_SlideDownTape3: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, -70);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        nextState = West_SlideDownTape_AlignBackLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = West_SlideDownTape_AlignBackRight;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case West_SlideDownTape_AlignBackLeft: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = West_SlideDownTape_AlignBackRight2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case West_SlideDownTape_AlignBackRight: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        nextState = West_SlideDownTape_AlignBackRight2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case West_SlideDownTape_AlignBackRight2: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(0, 0);
                    ES_Timer_InitTimer(SNATCH_TIMER, 250);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueEast_Onwards;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case DueEast_Onwards:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(60, 90);
                    ES_Timer_InitTimer(SNATCH_TIMER, WATCH_DOG_TIMER);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = East_SlideDownTape1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (BUMPER_PRESSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BUMP) {
                        nextState = DueEast_BackUp;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    if (ThisEvent.EventParam & FRONT_LEFT_BUMP) {
                        nextState = DueEast_BackUp; // failed most likely
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueEast_BackUp; // 50/50 failed
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case DueEast_BackUp:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(0, -90);
                    ES_Timer_StopTimer(SNATCH_TIMER);
                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        if (rotationsDone < 4) {
                            nextState = DueEast_Onwards; // 50/50 failed
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = SNATCH_COMPLETE;
                        }
                    }
                    break;
            }
            break;

        case East_SlideDownTape1:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
                    ES_Timer_InitTimer(SNATCH_TIMER, WATCH_DOG_TIMER);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        rotationsDone++;
                        nextState = DueWest_Onwards;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueEast_BackUp; // 50/50 failed
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case East_SlideDownTape2:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(90, 90);
                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
                    rotationsDone++;
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        if (rotationsDone < 4) {
                            nextState = East_SlideDownTape3;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            ThisEvent.EventType = SNATCH_COMPLETE;
                        }
                        break;
                    }
                    break;
            }
            break;

        case East_SlideDownTape3: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, -70);
                    break;
                case (TAPE_SENSED):
                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                    //                        nextState = Halt;
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                        break;
                    //                    }
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        nextState = East_SlideDownTape_AlignBackLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = East_SlideDownTape_AlignBackRight;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case East_SlideDownTape_AlignBackLeft: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = East_SlideDownTape_AlignBackRight2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case East_SlideDownTape_AlignBackRight: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        nextState = East_SlideDownTape_AlignBackRight2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case East_SlideDownTape_AlignBackRight2: // go over the tape
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(0, 0);
                    ES_Timer_InitTimer(SNATCH_TIMER, 250);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == SNATCH_TIMER) {
                        nextState = DueWest_Onwards;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

            //        case DueWest1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(PL1, PR1);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueWest2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) && (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        nextState = West_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = West_SlideDownTape_AlignRight;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape_AlignLeft;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = West_Collision_Buffer;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            //        case DueWest2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(PL2, PR2);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueWest1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) && (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        nextState = West_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = West_SlideDownTape_AlignRight;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape_AlignLeft;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = West_Collision_Buffer;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            ////        case West_ButtWink_FindTape:
            ////            switch (ThisEvent.EventType) {
            ////                case (ES_ENTRY):
            ////                    Drive(-50, -90);
            ////                    ES_Timer_InitTimer(SNATCH_TIMER, 1200);
            ////                    break;
            ////                case (ES_TIMEOUT):
            ////                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            ////                        nextState = West_ButtWink_GoBack;
            ////                        makeTransition = TRUE;
            ////                        ThisEvent.EventType = ES_NO_EVENT;
            ////                        break;
            ////                    }
            ////                    break;
            ////                case (TAPE_SENSED):
            ////                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            ////                        nextState = ButtWink_Reset;
            ////                        makeTransition = TRUE;
            ////                        ThisEvent.EventType = ES_NO_EVENT;
            ////                        break;
            ////                    }
            ////                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            ////                        nextState = ButtWink_Reset;
            ////                        makeTransition = TRUE;
            ////                        ThisEvent.EventType = ES_NO_EVENT;
            ////                        break;
            ////                    }
            ////                    break;
            ////            }
            ////            break;
            ////
            ////        case West_ButtWink_GoBack: // go over the tape
            ////            switch (ThisEvent.EventType) {
            ////                case (ES_ENTRY):
            ////                    Drive(50, 90);
            ////                    break;
            ////                case (TAPE_SENSED):
            ////                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) || (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            ////                        if ((ThisEvent.EventParam & FRONT_LEFT_BIT) && (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            ////                            nextState = West_SlideDownTape0;
            ////                            makeTransition = TRUE;
            ////                            ThisEvent.EventType = ES_NO_EVENT;
            ////                            break;
            ////                        }
            ////                        if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            ////                            nextState = West_SlideDownTape_AlignRight;
            ////                            makeTransition = TRUE;
            ////                            ThisEvent.EventType = ES_NO_EVENT;
            ////                            break;
            ////                        }
            ////                        if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            ////                            nextState = West_SlideDownTape_AlignLeft;
            ////                            makeTransition = TRUE;
            ////                            ThisEvent.EventType = ES_NO_EVENT;
            ////                            break;
            ////                        }
            ////                    }
            ////                    break;
            ////            }
            ////            break;
            ////
            ////        case ButtWink_Reset: // HALT
            ////            switch (ThisEvent.EventType) {
            ////                case (ES_ENTRY):
            ////                    Drive(50, 50);
            ////                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
            ////                    break;
            ////                case (ES_TIMEOUT):
            ////                    ThisEvent.EventType = SNATCH_COMPLETE;
            ////                    break;
            ////            }
            ////            break;
            //
            //        case West_SlideDownTape_AlignRight:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape_AlignLeft:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = West_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape0:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (~(ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        nextState = West_SlideDownTape1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                    //                        nextState = Halt;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    //                    Drive(90, 50);
            //                    Drive(70, 70);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = West_SlideDownTape3;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                    //                case (TAPE_SENSED):
            //                    //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                    //                        nextState = BackUp;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                    //                        nextState = BackUp;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    //                    break;
            //            }
            //            break;
            //
            //        case BackUp: // HALT
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-50, -50);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    ThisEvent.EventType = SNATCH_COMPLETE;
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape3: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-70, -70);
            //                    break;
            //                case (TAPE_SENSED):
            //                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                    //                        nextState = Halt;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape_AlignBackLeft;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = West_SlideDownTape_AlignBackRight;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape_AlignBackLeft: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = West_SlideDownTape_AlignBackRight2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape_AlignBackRight: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape_AlignBackRight2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_SlideDownTape_AlignBackRight2: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(0, 0);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 250);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueWest1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_Buffer:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-50, -50);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = West_Collision_BackUp1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_BackUp1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    Drive(-PL2, -PL2);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = West_Collision_BackUp2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & BACK_LEFT_BIT) || (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & BACK_LEFT_BIT) && (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                            nextState = West_Collision_SlideDown;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                            nextState = West_Collision_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                            nextState = West_Collision_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_BackUp2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    Drive(-PL1, -PL1);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = West_Collision_BackUp1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & BACK_LEFT_BIT) || (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & BACK_LEFT_BIT) && (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                            nextState = West_Collision_SlideDown;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                            nextState = West_Collision_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                            nextState = West_Collision_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_AlignRight:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_Collision_SlideDown;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_AlignLeft:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = West_Collision_SlideDown;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_SlideDown:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = West_Collision_TurnAround1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_TurnAround1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(70, 70);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 100);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = West_Collision_TurnAround2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_TurnAround2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_Collision_TurnAround3;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_TurnAround3:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = West_Collision_TurnAround4;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case West_Collision_TurnAround4:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = East_SlideDownTape2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case DueEast1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(PL1, PR1);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueEast2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) || (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & FRONT_LEFT_BIT) && (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                            nextState = East_SlideDownTape0;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                            nextState = East_SlideDownTape_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                            nextState = East_SlideDownTape_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = East_Collision_Buffer;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            //        case DueEast2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(PL2, PR2);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueEast1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) || (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & FRONT_LEFT_BIT) && (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                            nextState = East_SlideDownTape0;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                            nextState = East_SlideDownTape_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                            nextState = East_SlideDownTape_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = East_Collision_Buffer;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape_AlignRight:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = East_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape_AlignLeft:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = East_SlideDownTape0;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape0:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (~(ThisEvent.EventParam & FRONT_LEFT_BIT)) {
            //                        nextState = East_SlideDownTape1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                    //                        nextState = Halt;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = East_SlideDownTape2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(50, 90);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 1200);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = East_SlideDownTape3;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = BackUp;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = BackUp;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape3: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-50, -90);
            //                    break;
            //                case (TAPE_SENSED):
            //                    //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                    //                        nextState = Halt;
            //                    //                        makeTransition = TRUE;
            //                    //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    //                        break;
            //                    //                    }
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = East_SlideDownTape_AlignBackLeft;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = East_SlideDownTape_AlignBackRight;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape_AlignBackLeft: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = East_SlideDownTape_AlignBackRight2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape_AlignBackRight: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = East_SlideDownTape_AlignBackRight2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_SlideDownTape_AlignBackRight2: // go over the tape
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(0, 0);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 250);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = DueWest1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_Buffer:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-50, -50);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 500);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = East_Collision_BackUp1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_BackUp1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    Drive(-PL2, -PL2);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = East_Collision_BackUp2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & BACK_LEFT_BIT) || (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & BACK_LEFT_BIT) && (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                            nextState = East_Collision_SlideDown;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                            nextState = East_Collision_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                            nextState = East_Collision_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_BackUp2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(SNATCH_TIMER, MS_HALFWAY);
            //                    Drive(-PL1, -PL1);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = East_Collision_BackUp1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & BACK_LEFT_BIT) || (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                        if ((ThisEvent.EventParam & BACK_LEFT_BIT) && (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
            //                            nextState = East_Collision_SlideDown;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                            nextState = East_Collision_AlignRight;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                        if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                            nextState = East_Collision_AlignLeft;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            break;
            //                        }
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_AlignRight:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = East_Collision_SlideDown;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_AlignLeft:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(-TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = East_Collision_SlideDown;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_SlideDown:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, TURN_SPEED_0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = East_Collision_TurnAround1;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_TurnAround1:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(70, 70);
            //                    ES_Timer_InitTimer(SNATCH_TIMER, 100);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == SNATCH_TIMER) {
            //                        nextState = East_Collision_TurnAround2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        break;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_TurnAround2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = East_Collision_TurnAround3;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_TurnAround3:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_100, -TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = East_Collision_TurnAround4;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case East_Collision_TurnAround4:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(TURN_SPEED_0, TURN_SPEED_100);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = West_SlideDownTape2;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;

        case Halt: // HALT
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(0, 0);
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSnatchSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunSnatchSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/