/*
 * File:   Timer_Functions.c
 * Author: rmcnamee
 *
 * Created on December 8, 2017, 8:44 AM
 */

#include "Timer_Functions.h"
#include "mcc_generated_files/tmr0.h"
#include "Communication_Handler.h"
#include "Switch_Functions.h"

#define SCAN_SWITCH_TIMER_MS 50 // Set a default time to scan the switches for being pressed
#define SERIAL_TIMER_MS 100 // Set a default time to say that serial communications timed out

unsigned int scanSwitchTimer;

unsigned int _timerCounterdown[NUMBER_OF_TIMERS];
unsigned int _lastTimerValue[NUMBER_OF_TIMERS];

void TimerInterruptHandler(void);

void SetupTimers(void)
{
    TMR0_SetInterruptHandler(TimerInterruptHandler);
}

void StartTimer(TIMER_TYPE_ENUM timer, unsigned int milliseconds)
{
    if (timer >= NUMBER_OF_TIMERS)
    {
        return; // Error catching
    }
    
    _timerCounterdown[timer] = milliseconds + 1;        
    _lastTimerValue[timer] = _timerCounterdown[timer]; // Set the last value of the timer
}

void RestartTimer(TIMER_TYPE_ENUM timer)
{
    if (timer >= NUMBER_OF_TIMERS)
    {
        return; // Error catching
    }
    
    _timerCounterdown[timer] = _lastTimerValue[timer];
}

void StopTimer(TIMER_TYPE_ENUM timer)
{
    if (timer >= NUMBER_OF_TIMERS)
    {
        return; // Error catching
    }
    
    _timerCounterdown[timer] = 0;
}

bool CheckIfTimerExpired(TIMER_TYPE_ENUM timer)
{
    if (timer >= NUMBER_OF_TIMERS)
    {
        return false; // Error catching
    }
    
    if (_timerCounterdown[timer] == 1)
    {
        return true;
    }
    
    return false;
}

bool CheckIfTimerRunning(TIMER_TYPE_ENUM timer)
{
    if (timer >= NUMBER_OF_TIMERS)
    {
        return false; // Error catching
    }
    
    if (_timerCounterdown[timer] > 1)
    {
        return true;
    }
    
    return false;
}

// If new timers are added, add them to this list so they will be stopped when the
// host sends the command
void StopAllTimers(void)
{
    int i = 0;
    for (i = 0; i < NUMBER_OF_TIMERS; i++)
    {
        _timerCounterdown[i] = 0;
    }
}

void TimerInterruptHandler(void)
{
    int i = 0;
    for (i = 0; i < NUMBER_OF_TIMERS; i++)
    {
        if (_timerCounterdown[i] > 1)
        {
            (_timerCounterdown[i])--;
        }        
    }
    
    ParseSerialTxAndSendByte();
    RefreshSwitchImage(); // Refresh the screen every interrupt
}