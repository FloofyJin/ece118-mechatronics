/*
 * File: OlympicPt2SubHSM.h
 * Author: Shreya Sinha 
 * Modified: Eric Vetha
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopHSM.h"
#include "OlympicPt2SubHSM.h"
#include "Actuator.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitOlympicState,
    Buffer,
    FindTape,
    Collision_NoTape_Backup,
    Collision_NoTape_Turn,
    Collision_NoTape_Forward,
    Collision_Tape_Backup,
    Collision_Tape_Turn,
    Collision_Tape_Forward,
    AlignLeftTape,
    AlignRightTape,
    AlignRightTapeForward,
    SwerveL,
    GoBackBuffer,
    GoBack,
    Delay,
    SwerveR,
    SwerveB,
    AvoidObject,
    TurnRight,
    PreLineFollow,
    PreLineFollowThe2nd,
    LineFollow,
    LineFollowBuffer,
    LineFollow_RealignFront,
    LePetitRealign,
    LePetitRealign2,
    GoOver2ElectricBoogalo,
    Halt,
    FindTapeBuffer
} OlympicSubHSMState_t;

static const char *StateNames[] = {
    "InitOlympicState",
    "Buffer",
    "FindTape",
    "Collision_NoTape_Backup",
    "Collision_NoTape_Turn",
    "Collision_NoTape_Forward",
    "Collision_Tape_Backup",
    "Collision_Tape_Turn",
    "Collision_Tape_Forward",
    "AlignLeftTape",
    "AlignRightTape",
    "AlignRightTapeForward",
    "SwerveL",
    "Delay",
    "GoOver",
    "GoBack",
    "SwerveR",
    "SwerveB",
    "AvoidObject",
    "TurnRight",
    "PreLineFollow",
    "PreLineFollowThe2nd",
    "LineFollow",
    "LineFollow_RealignFront",
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

static OlympicSubHSMState_t CurrentState = InitOlympicState; // <- change name to match ENUM
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
uint8_t InitOlympicSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitOlympicState;
    returnEvent = RunOlympicSubHSM(INIT_EVENT);
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
ES_Event RunOlympicSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    OlympicSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    //    if (ThisEvent.EventType == ES_TIMEOUT) {
    //        if (ThisEvent.EventParam == STOP_TIMER) {
    //            nextState = Collision_NoTape_Backup;
    //            makeTransition = TRUE;
    //            ThisEvent.EventType = ES_NO_EVENT;
    //        }
    //    }
    //    ES_Timer_InitTimer(STOP_TIMER, 5000);

    //    printf("Current state: %d\n\n", CurrentState);

    switch (CurrentState) {
        case InitOlympicState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = Buffer;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Buffer:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, 70);
                    break;
                case (ES_TIMEOUT):
                    //printf("Buffer: %d\n\n", ThisEvent.EventParam);
                    nextState = FindTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case FindTapeBuffer:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(87, 80);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = FindTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case FindTape: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    //printf("Find Tape \n\n");
                    ES_Timer_InitTimer(HSM_TIMER, 10000); // watchdog timer
                    Drive(87, 80);
                    break;
                case (TAPE_SENSED):
                    if ((ThisEvent.EventParam & FRONT_RIGHT_BIT) && (ThisEvent.EventParam & FRONT_LEFT_BIT)) {
                        nextState = Delay;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = AlignLeftTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        nextState = AlignRightTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == HSM_TIMER) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case AlignLeftTape:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(STOP_TIMER, 4000); // watchdog timer
                    //printf("Align Left Tape \n\n");
                    Drive(70, 0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        nextState = Delay;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == STOP_TIMER) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case AlignRightTape:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(STOP_TIMER, 4000); // watchdog timer
                    Drive(0, 70);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = Delay;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == STOP_TIMER) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

            //        case GoOver:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(HSM_TIMER, 75); // go over enough to clear tape AND not be close to falling
            //                    Drive(70, 70);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    nextState = Delay;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //            }
            //            break;

        case Delay:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 250);
                    Drive(0, 0);
                    break;
                case (ES_TIMEOUT):
                    nextState = SwerveL;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case SwerveL:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(STOP_TIMER, 5000);
                    Drive(-70, 70);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                        nextState = SwerveR;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == STOP_TIMER) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;


        case SwerveR:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(STOP_TIMER, 5000);
                    Drive(70, 0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = LineFollow;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_TIMEOUT):
                    if (ThisEvent.EventParam == STOP_TIMER) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case SwerveB:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, 0);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = PreLineFollow;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

            //        case GoBack:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    ES_Timer_InitTimer(HSM_TIMER, 1400); // go over enough to clear tape AND not be close to falling
            //                    Drive(-80, -40);
            //                    break;
            //                case (ES_TIMEOUT):
            //                    nextState = PreLineFollowThe2nd;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //            }
            //            break;

        case GoBackBuffer:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(0, 0);
                    break;
                case (ES_TIMEOUT):
                    //printf("Buffer: %d\n\n", ThisEvent.EventParam);
                    nextState = GoBack;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    //                case TAPE_SENSED:
                    //                    if (~(ThisEvent.EventParam & FRONT_LEFT_BIT)) {
                    //                        nextState = GoBack;
                    //                        makeTransition = TRUE;
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    }
                    //                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case GoBack:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, 70);
                    break;
                case (TAPE_SENSED):
                    //                    if (ThisEvent.EventParam & BACK_LEFT_BIT) {
                    //                        if (ThisEvent.EventParam & FRONT_RIGHT_BIT) { // will never happen ong no cap
                    //                            nextState = LineFollow;
                    //                            makeTransition = TRUE;
                    //                            ThisEvent.EventType = ES_NO_EVENT;
                    //                        } else {
                    //                            nextState = LePetitRealign;
                    //                            makeTransition = TRUE;
                    //                            ThisEvent.EventType = ES_NO_EVENT;
                    //                        }
                    //                    }
                    break;
            }
            break;

            //        case LePetitRealign2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(0, 70);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = LePetitRealign;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;

        case LePetitRealign:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(70, -50);
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = LineFollow;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

            //        case LePetitRealign2:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(0, 70);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & BACK_RIGHT_BIT) {
            //                        nextState = LePetitRealign;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //            }
            //            break;

            //        case PreLineFollow:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(80, 60);
            //                    // Drive(0, 0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = GoBack;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    } else if (~(ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
            //                        nextState = LineFollow_RealignFront;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = Collision_Tape_Backup;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_BUMP) {
            //                        nextState = Collision_Tape_Forward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;

            //        case PreLineFollowThe2nd:
            //            switch (ThisEvent.EventType) {
            //                case (ES_ENTRY):
            //                    Drive(70, 60);
            //                    // Drive(0, 0);
            //                    break;
            //                case (TAPE_SENSED):
            //                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
            //                        nextState = GoBack;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    } else if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
            //                        nextState = LineFollow;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case (BUMPER_PRESSED):
            //                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
            //                        nextState = Collision_Tape_Backup;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    if (ThisEvent.EventParam & BACK_BUMP) {
            //                        nextState = Collision_Tape_Forward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                case (ES_NO_EVENT):
            //                    break;
            //            }
            //            break;

        case LineFollow:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(-70, 70);
                    ES_Timer_InitTimer(HSM_TIMER, 5000); // watchdog timer 
                    break;
                case (TAPE_SENSED):
                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        // nextState = GoBackBuffer;
                        nextState = SwerveL;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (~(ThisEvent.EventParam & FRONT_RIGHT_BIT)) {
                        nextState = FindTapeBuffer;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    if (ThisEvent.EventParam & BACK_BUMP) {
                        nextState = Collision_Tape_Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                case ES_TIMEOUT:
                    nextState = Collision_Tape_Backup;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case (ES_NO_EVENT):
                    break;
            }
            break;

        case LineFollowBuffer:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 50);
                    break;
                case ES_TIMEOUT:
                    nextState = LineFollow_RealignFront;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    if (ThisEvent.EventParam & BACK_BUMP) {
                        nextState = Collision_Tape_Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case LineFollow_RealignFront:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    Drive(90, 90);
                    break;
                case TAPE_SENSED:
                    if ((ThisEvent.EventParam & FRONT_RIGHT_BIT) || (ThisEvent.EventParam & BACK_RIGHT_BIT)) {
                        nextState = LineFollow;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        nextState = GoBackBuffer;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    if (ThisEvent.EventParam & BACK_BUMP) {
                        nextState = Collision_Tape_Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case Collision_NoTape_Backup:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, -70);
                    break;
                case ES_TIMEOUT:
                    nextState = Collision_NoTape_Turn;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
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
                    nextState = FindTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case Collision_Tape_Backup:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, -70);
                    break;
                case ES_TIMEOUT:
                    nextState = Collision_Tape_Turn;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case Collision_Tape_Turn:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 500);
                    Drive(-70, 70);
                    break;
                case ES_TIMEOUT:
                    nextState = AvoidObject;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case AvoidObject:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 2000);
                    Drive(70, 70);
                    break;
                case (BUMPER_PRESSED):
                    if ((ThisEvent.EventParam & FRONT_LEFT_BUMP) || (ThisEvent.EventParam & FRONT_RIGHT_BUMP)) {
                        nextState = Collision_Tape_Backup;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                    break;
                case (TAPE_SENSED):
                    if ((ThisEvent.EventParam & FRONT_RIGHT_BIT) && (ThisEvent.EventParam & FRONT_LEFT_BIT)) {
                        nextState = Delay;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam & FRONT_RIGHT_BIT) {
                        nextState = AlignLeftTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (ThisEvent.EventParam & FRONT_LEFT_BIT) {
                        nextState = AlignRightTape;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_TIMEOUT:
                    nextState = TurnRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case TurnRight:
            switch (ThisEvent.EventType) {
                case (ES_ENTRY):
                    ES_Timer_InitTimer(HSM_TIMER, 700);
                    Drive(70, -70);
                    break;
                case ES_TIMEOUT:
                    nextState = FindTape;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
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
                    nextState = Collision_NoTape_Turn;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

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
        RunOlympicSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunOlympicSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
