/* 
 * File:   Timer_Functions.h
 * Author: rmcnamee
 *
 * Created on December 8, 2017, 8:44 AM
 */

#ifndef TIMER_FUNCTIONS_H
#define	TIMER_FUNCTIONS_H

#include "main.h"

typedef enum
{
    TIMER_SWITCH_SCAN = 0,
    TIMER_SWITCH1_LOOP,
    TIMER_SWITCH2_LOOP,
    TIMER_SWITCH1_BACKLIGHT,
    TIMER_SWITCH2_BACKLIGHT,
    TIMER_SERIAL_TIMEOUT,
}TIMER_TYPE_ENUM;

#define NUMBER_OF_TIMERS 6 // INCREASE THIS WHEN ADDING TO ABOVE


/**
   @Param
    none
   @Returns
    none
   @Description
    Does any setup required to run timers
   @Example
    SetupTimers();
 */
void SetupTimers(void);


/**
   @Param
    none
   @Returns
    none
   @Description
    Stops all timers (except for the switch press timer)
   @Example
    StopAllTimers();
 */
void StopAllTimers(void);

/**
   @Param
 * timer - The timer to start
 * milliseconds - the amount of time in milliseonds the timer runs
   @Returns
    none
   @Description
    Starts the specified timer for the specified time
   @Example
    StartTimer(TIMER_SERIAL_TIMEOUT, 100);
 */
void StartTimer(TIMER_TYPE_ENUM timer, unsigned int milliseconds);

/**
   @Param
 * timer - The timer to start
   @Returns
    none
   @Description
    Starts the specified timer using the previously set settings
   @Example
    RestartTimer(TIMER_SERIAL_TIMEOUT);
 */
void RestartTimer(TIMER_TYPE_ENUM timer);

/**
   @Param
 * timer - The timer to stop
   @Returns
    none
   @Description
    Stops the specified timer
   @Example
    StopTimer(TIMER_SERIAL_TIMEOUT);
 */
void StopTimer(TIMER_TYPE_ENUM timer);

/**
   @Param
 * timer - The timer to check
   @Returns
    True if the timer has expired, false otherwise
   @Description
    Checks if the specified timer has expired
   @Example
    bool expired = CheckIfTimerExpired(TIMER_SERIAL_TIMEOUT);
 */
bool CheckIfTimerExpired(TIMER_TYPE_ENUM timer);

/**
   @Param
 * timer - The timer to check
   @Returns
    True if the timer is running, false otherwise
   @Description
    Checks if the specified timer is running
   @Example
    bool running = CheckIfTimerRunning(TIMER_SERIAL_TIMEOUT);
 */
bool CheckIfTimerRunning(TIMER_TYPE_ENUM timer);

#endif	/* TIMER_FUNCTIONS_H */

