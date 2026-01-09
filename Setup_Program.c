/*
 * File:   Setup_Program.c
 * Author: rmcnamee
 *
 * Created on December 7, 2017, 9:06 AM
 */

#include "Communication_Handler.h"
#include "Setup_Program.h"
#include "Flash_Functions.h"
#include "IO_Functions.h"
#include "Switch_Functions.h"
#include "Timer_Functions.h"

// Runs all of the setups for the individual modules
void SetupProgram(void)
{   
    // NKK Initializations
    SetupIo();    
    SetupTimers();
    SetupCommunications();        
    SetupFlash();
    SetupSwitches(); // This must be last as it depends on the communications setup
    
    SendSerialByte(RESPONSE_SETUP_COMPLETE);
    return;
}
