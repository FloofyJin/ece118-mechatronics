/*
 * File: OlympicSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopHSM.h"
#include "DisposalSubHSM.h"
#include "Actuator.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitDisposalState,
    HitWall,
    PullForward,
    Adjusting,
    Preparing,
    Wait,
    WalkUp,
    Dumping,
    Pullout,
    WaitAgain,
    LeftTurn,
    AlignLeftTape,
    AlignRightTape,
    TurnToBackLeft,
    KeepTurningBackRight,
    BackIntoTape,
    GoForward,
    GoOver,
    GoBack,
    Stop,
    TapeL,
    TapeR,
    BackUp,
    BackAndTurn,
    Collision_NoTape_Backup,
    Collision_NoTape_Turn,
    Collision_NoTape_Forward
} DisposalSubHSMState_t;

static const char *StateNames[] = {
    "InitDisposalState",
    "HitWall",
    "PullForward",
    "Adjusting",
    "Preparing",
    "Wait",
    "WalkUp",
    "Dumping",
    "Pullout",
    "WaitAgain",
    "LeftTurn",
    "AlignLeftTape",
    "AlignRightTape",
    "TurnToBackLeft",
    "KeepTurningBackRight",
    "BackIntoTape",
    "GoForward",
    "GoOver",
    "GoBack",
    "Stop",
    "TapeL",
    "TapeR",
    "BackUp",
    "BackAndTurn",
    "Collision_NoTape_Backup",
    "Collision_NoTape_Turn",
    "Collision_NoTape_Forward"
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

static DisposalSubHSMState_t CurrentState = InitDisposalState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t Round;

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
uint8_t InitDisposalSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitDisposalState;
    returnEvent = RunDisposalSubHSM(INIT_EVENT);
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
ES_Event RunDisposalSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    DisposalSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitDisposalState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = Adjusting;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Adjusting: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 900);
                    Drive(-70, -70);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = WalkUp;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case WalkUp:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 1400);
                    ServoDown();
                    Drive(80, 80);
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = Dumping;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case Dumping:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 4000);
                    Drive(90, 90);
                    Intake(-100);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = Pullout;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case Pullout:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, -70);
                    IntakeMotorSpeed(100);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = WaitAgain;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case WaitAgain:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 300);
                    ServoUp();
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = PullForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case PullForward:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(60, 60);
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = LeftTurn;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case LeftTurn:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, 30);
                    IntakeMotorSpeed(100);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = GoForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case GoForward:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(70, 70);
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = BackIntoTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case BackIntoTape:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-80, -80);
                    break;
                case (TAPE_SENSED):
                    if ((ThisEvent.EventParam & BACK_RIGHT_BIT) || (ThisEvent.EventParam & BACK_LEFT_BIT)) {
                        ThisEvent.EventType = ROUND_MAX;
                        //makeTransition = TRUE;
                        break;
                    } else if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        nextState = AlignLeftTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    } else if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = AlignRightTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
            }
            break;

        case AlignRightTape:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(0, -50);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
                        ThisEvent.EventType = ROUND_MAX;
                        //makeTransition = TRUE;
                    }
                    break;
            }
            break;

        case AlignLeftTape:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-50, 0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        ThisEvent.EventType = ROUND_MAX;
                        //makeTransition = TRUE;
                    }
                    break;
            }
            break;

            //        case TapeL:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(HSM_TIMER, 2000);
            //                    //ES_Timer_InitTimer(WATCH_DOG_TIMER, 7000);
            //                    Drive(90, 80);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) || (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        Round += 1;
            //                        if (Round == 3) {
            //                            nextState = BackUp;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                            makeTransition = TRUE;
            //                            Round = 0;
            //                        } else {
            //                            nextState = GoOver;
            //                            makeTransition = TRUE;
            //                            ThisEvent.EventType = ES_NO_EVENT;
            //                        }
            //                    }
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == HSM_TIMER) {
            //                        nextState = TapeR;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        makeTransition = TRUE;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = Collision_NoTape_Backup;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_BUMP) {
            //                        nextState = Collision_NoTape_Forward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            //        case TapeR:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    printf("Tape right \n\n");
            //                    ES_Timer_InitTimer(HSM_TIMER, 2000);
            //                    //ES_Timer_InitTimer(WATCH_DOG_TIMER, 7000);
            //                    Drive(80, 90);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    if (ThisEvent.EventParam == HSM_TIMER) {
            //                        Drive(82, 80);
            //                        //                        nextState = TapeL;
            //                        //                        ThisEvent.EventType = ES_NO_EVENT;
            //                        //                        makeTransition = TRUE;
            //                    }
            //                    break;
            //                case (TAPE_SENSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BIT) || (ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        nextState = GoOver;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = Collision_NoTape_Backup;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_BUMP) {
            //                        nextState = Collision_NoTape_Forward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;
            //
            //        case BackUp:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(HSM_TIMER, 1000);
            //                    Drive(-50, -50);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    ThisEvent.EventType = ROUND_MAX;
            //                    makeTransition = TRUE;
            //                    break;
            //            }
            //            break;
            //
            //        case GoOver:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(HSM_TIMER, 100); // go over enough to clear tape AND not be close to falling
            //                    Drive(70, 70);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    nextState = TurnToBackLeft;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //            }
            //            break;
            //
            //        case TurnToBackLeft:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(50, -50);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
            //                        nextState = KeepTurningBackRight;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;
            //
            //        case KeepTurningBackRight:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(50, -50);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = GoForward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;

        case Collision_NoTape_Backup:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 200);
                    Drive(-70, -70);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = Collision_NoTape_Turn;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case Collision_NoTape_Turn:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, 70);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = TapeL;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case Collision_NoTape_Forward:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(70, 70);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = Collision_NoTape_Turn;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunDisposalSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunDisposalSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/