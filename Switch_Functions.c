/*
 * File:   Setup_Program.c
 * Author: rmcnamee
 *
 * Created on December 13, 2017, 10:29 AM
 */

#include "mcc_generated_files/eusart2.h"
#include "mcc_generated_files/pwm3.h"
#include "Switch_Functions.h"
#include "Flash_Functions.h"
#include "IO_Functions.h"
#include "Timer_Functions.h"
#include "Communication_Handler.h"

#define BACKLIGHT_COLOR_TIME_ON 1000 // Set a time of 1 second between changing backlight colors (For demonstration)

unsigned int switchImageBuffer[24][10]; // Holds the images from flash memory for refreshing the switches.
unsigned char currentImageRefreshLine; // Lines 0-23, on 24 resets back to 0

void ConfigureSwitchInialSettings(void);
void ReadImageAttribute(uint24_t flashAddress, imageAttributeStruct* attributeStruct);
void LoadStartingImageAndAttribute(void);
void LoadSwitch1Image(uint24_t attributeAddress);
void LoadSwitch2Image(uint24_t attributeAddress);
void DoSwitch1PressedBehavior(void);
void DoSwitch2PressedBehavior(void);
void CheckIfSwitch1LoopTimerNeedsStarting(void);
void CheckIfSwitch2LoopTimerNeedsStarting(void);
void ChangeSwitchBacklight(void);
void CheckIfSwitch1BacklightTimerNeedsStarting(void);
void CheckIfSwitch2BacklightTimerNeedsStarting(void);
unsigned char SerializeAttributeBacklightColor(void);
void SendSwitch1ImageChangedNotification(uint24_t imageAddress);
void SendSwitch2ImageChangedNotification(uint24_t imageAddress);
void ReadBacklightColors(uint24_t address, unsigned char* colorBuffer);
void LoopSwitch1BacklightColor(void);
void LoopSwitch2BacklightColor(void);

imageAttributeStruct switch1ImageAttributes; // A struct to hold the attributes for switch 1
imageAttributeStruct switch2ImageAttributes; // A struct to hold the attributes for switch 2

bool switch1PressedPreviously; // For debouncing, don't want to trigger on user holding down
bool switch2PressedPreviously; // For debouncing, don't want to trigger on user holding down
bool attributeTableInvalid; // Flag if the attribute table has not been loaded, don't do anything if the switch is pressed

// Provides the setup needed for correct switch operation
void SetupSwitches(void)
{
    SetSwitchSerialClockHigh(); // Clock is default high
    EnablePowerToSwitches();    
    
    ConfigureSwitchInialSettings();
    LoadStartingImageAndAttribute();        
    
    StartTimer(TIMER_SWITCH_SCAN, 100);
}

// Sends commands to both switches to configure them initially
void ConfigureSwitchInialSettings(void)
{
     // No setup to do, contrast already set by PWM3 and backlight color will be set after loading attributes
}

// Reads the setup attribute (0x00) and configures appropriately
void ReadSetupAttributes(void)
{
    unsigned char attributeData[16];
    uint24_t attributeSize;
    uint24_t flashAddress;
    
    ReadFlashMemory(FLASH_ATTRIBUTE_START_ADDRESS,attributeData,GetCurrentSwitchAttributeSize()); // Initial settings are in attribute 0x0000
    
    if (attributeData[SETUP_SETUP_ADDRESS_HIGH] == FLASH_ATTRIBUTE_NOT_PROGRAMMED_BYTE)
    {
        switch1ImageAttributes.currentAddress = 0x0001;        
        switch2ImageAttributes.currentAddress = 0x0002;
        SetSwitchBrightness(SWITCH_CONTRAST_IDEAL);
    }
    else
    {
        switch1ImageAttributes.currentAddress = 0x0001; // Switch 1 always starts at address 1, to not let user get lost
        switch2ImageAttributes.currentAddress = (attributeData[SETUP_SWITCH2_START_ADDRESS_HIGH] << 8) | attributeData[SETUP_SWITCH2_START_ADDRESS_LOW];            
        SetSwitchBrightness(attributeData[SETUP_CONTRAST]);
    }
    
        attributeSize = GetCurrentSwitchAttributeSize();
        flashAddress = (uint24_t) ((switch1ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS); // We define the flash attributes to be in a specific part of memory
    
        ReadImageAttribute(flashAddress, &switch1ImageAttributes); // Loads the attributes into the struct
    
        flashAddress = (uint24_t) ((switch2ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS);
        ReadImageAttribute(flashAddress, &switch2ImageAttributes); // Loads the attributes into the struct                
}

// Loads the starting attribute and image
void LoadStartingImageAndAttribute(void)
{     
    ReadSetupAttributes();
    
    if (switch1ImageAttributes.currentAddress > SWITCH_MAX_IMAGES) // We limit the addresses, so if we read above that it's invalid
    {         
        attributeTableInvalid = true;
        
        switch1ImageAttributes.currentAddress = 0x0001;
        switch2ImageAttributes.currentAddress = 0x0002;
    }            
    
    LoadSwitch1Image(switch1ImageAttributes.currentAddress);  // Loads the image on to the switch
    LoadSwitch2Image(switch2ImageAttributes.currentAddress);
    
    CheckIfSwitch1LoopTimerNeedsStarting();
    CheckIfSwitch2LoopTimerNeedsStarting();
    
    CheckIfSwitch1BacklightTimerNeedsStarting();
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

// Reads the attribute at the given flash address and loads all the values into the given struct
void ReadImageAttribute(uint24_t flashAddress, imageAttributeStruct* attributeStruct)
{
    unsigned char attributeData[16];    
    ReadFlashMemory(flashAddress,attributeData,GetCurrentSwitchAttributeSize());
 
    attributeStruct->currentAddress = (((uint24_t)(attributeData[ATTRIBUTE_CURRENT_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_CURRENT_ADDRESS_LOW];
    attributeStruct->loopEndAddress = (((uint24_t)(attributeData[ATTRIBUTE_LOOP_END_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_LOOP_END_ADDRESS_LOW];
    attributeStruct->timer1 = attributeData[ATTRIBUTE_TIMER1];
    attributeStruct->timer2 = attributeData[ATTRIBUTE_TIMER2];
    attributeStruct->switch1PressAddress = (((uint24_t)(attributeData[ATTRIBUTE_SW1_PRESS_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_SW1_PRESS_ADDRESS_LOW];
    attributeStruct->switch2PressAddress = (((uint24_t)(attributeData[ATTRIBUTE_SW2_PRESS_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_SW2_PRESS_ADDRESS_LOW];
    attributeStruct->switch1TimerExpiredJumpAddress = (((uint24_t)(attributeData[ATTRIBUTE_SW1_TIMER_EXPIRED_JUMP_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_SW1_TIMER_EXPIRED_JUMP_ADDRESS_LOW];
    attributeStruct->switch2TimerExpiredJumpAddress = (((uint24_t)(attributeData[ATTRIBUTE_SW2_TIMER_EXPIRED_JUMP_ADDRESS_HIGH])) << 8) | attributeData[ATTRIBUTE_SW2_TIMER_EXPIRED_JUMP_ADDRESS_LOW];
    attributeStruct->backlightColorState1 = attributeData[ATTRIBUTE_BACKLIGHT_COLOR_STATE1];
    attributeStruct->backlightColorState2 = attributeData[ATTRIBUTE_BACKLIGHT_COLOR_STATE2];
    
    return;    
}

// Loads the image into (half) the switchImageBuffer array, which is sent to the switches ~500 uSec
void LoadSwitch1Image(uint24_t imageAddress)
{    
    unsigned char databuffer[5];
    unsigned char lineNumber = 0;
        
    uint24_t totalImageSize = GetCurrentSwitchTotalSize();
    uint24_t flashAddress = (imageAddress * totalImageSize) + FLASH_IMAGE_START_ADDRESS;
    
    for (unsigned int i = 0; i < totalImageSize; i += 5) // We read 5 bytes at a time, for 36 bits + padded 0s for 40 bits
    {
        uint24_t address = flashAddress + i;
        ReadFlashMemory(address, databuffer, 5);        
        for (unsigned char j = 0; j < 5; j++)
        {
            switchImageBuffer[lineNumber][j] = databuffer[j]; // Bytes 0-4 are for the switch 1 image in the buffer
        }          
        
        lineNumber++;
    }
    
    SendSwitch1ImageChangedNotification(imageAddress);
}

// Loads the image into (half) the switchImageBuffer array, which is sent to the switches ~500 uSec
void LoadSwitch2Image(uint24_t imageAddress)
{
    unsigned char databuffer[5];
    unsigned char lineNumber = 0;
        
    uint24_t totalImageSize = GetCurrentSwitchTotalSize();
    uint24_t flashAddress = (imageAddress * totalImageSize) + FLASH_IMAGE_START_ADDRESS;
    
    for (unsigned int i = 0; i < totalImageSize; i += 5) // We read 5 bytes at a time, for 36 bits + padded 0s for 40 bits
    {
        uint24_t address = flashAddress + i;
        ReadFlashMemory(address, databuffer, 5);        
        for (unsigned char j = 0; j < 5; j++)
        {
            switchImageBuffer[lineNumber][(j+5)] = databuffer[j]; // Increment j by 5 because bytes 5-9 are for the switch 2 image in the buffer
        }          
        
        lineNumber++;
    }
    
    SendSwitch2ImageChangedNotification(imageAddress);
}

// Reads the backlight colors of the sent address, and puts them in the legnth 2 buffer provided
void ReadBacklightColors(uint24_t address, unsigned char* colorBuffer)
{
    uint24_t attributeSize;
    uint24_t flashAddress;
    unsigned char attributeData[16];   
    
    attributeSize = GetCurrentSwitchAttributeSize();
    flashAddress = (uint24_t) ((address * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS); // We define the flash attributes to be in a specific part of memory
    
    ReadFlashMemory(flashAddress,attributeData,GetCurrentSwitchAttributeSize());
    
    colorBuffer[0] = attributeData[ATTRIBUTE_BACKLIGHT_COLOR_STATE1];
    colorBuffer[1] = attributeData[ATTRIBUTE_BACKLIGHT_COLOR_STATE2];
}

// Updates the backlight values of both switches
void ChangeSwitchBacklight(void)
{               
    unsigned char serializedBacklight = SerializeAttributeBacklightColor();
    for (signed char i = 7; i >= 0; i--) // The chipe requires the highest bit to be sent first
    {
        if ((serializedBacklight & (1 << i)) > 0) // Scans through the bits and sets the led based on the bit
        {      
            SetLedSerialDataHigh();    
        }
        else
        {
            SetLedSerialDataLow();
        }
        
        SetLedSerialClockHigh();   
        SetLedSerialClockLow();   
    }    
    
    SetLedLatchPulseHigh();
    SetLedLatchPulseLow();
}

// Takes the attributes from both switches and figures out what to send the led driver chip
// (This is needed because one serial command controls both switch colors)
unsigned char SerializeAttributeBacklightColor(void)
{
    unsigned char serializedBacklight = 0;
    
    if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_BLUE_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_BLUE_ENABLED;
    }
    else if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_BLUE_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_BLUE_ENABLED;
    }
    
    if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_GREEN_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_GREEN_ENABLED;
    }
    else if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_GREEN_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_GREEN_ENABLED;   
    }
    
    if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_RED_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_RED_ENABLED;
    }
    else if ((switch1ImageAttributes.currentBacklightColor & ATTRIBUTE_RED_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH1_RED_ENABLED;
    }
    
    if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_BLUE_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_BLUE_ENABLED;
    }
    else if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_BLUE_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_BLUE_ENABLED;
    }
    
    if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_GREEN_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_GREEN_ENABLED;
    }
    else if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_GREEN_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_GREEN_ENABLED;
    }
    
    if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_RED_ENABLED1) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_RED_ENABLED;
    }   
    else if ((switch2ImageAttributes.currentBacklightColor & ATTRIBUTE_RED_ENABLED2) > 0)
    {
        serializedBacklight |= 1 << LED_SWITCH2_RED_ENABLED;
    }
    
    return serializedBacklight;
}

// Scans both switches for being pressed, and does whatever behavior the attribute
// specifies if the switch was pressed
void ScanSwitchesForPress(void)
{
    if (CheckIfTimerExpired(TIMER_SWITCH_SCAN) == false)
    {
        return; // Don't do anything if it's not time to check
    }
    
    if (CheckIfSwitch1Pressed() == true)
    {
        if (switch1PressedPreviously != true)
        {
            switch1PressedPreviously = true;
            DoSwitch1PressedBehavior();
            responsesEnum response = RESPONSE_SWITCH1_PRESSED;
            SendResponseOverSerial(response);
        }
    }
    else
    {
        if (switch1PressedPreviously == true)
        {      
            responsesEnum response = RESPONSE_SWITCH1_RELEASED;
            SendResponseOverSerial(response);
        }
        switch1PressedPreviously = false;
    }
    
    if (CheckIfSwitch2Pressed() == true)
    {
        if (switch2PressedPreviously != true)
        {
            switch2PressedPreviously = true;
            DoSwitch2PressedBehavior();
            responsesEnum response = RESPONSE_SWITCH2_PRESSED;
            SendResponseOverSerial(response);
        }
    }
    else
    {
        if (switch2PressedPreviously == true)
        {      
            responsesEnum response = RESPONSE_SWITCH2_RELEASED;
            SendResponseOverSerial(response);
        }
        switch2PressedPreviously = false;
    }    
    
    RestartTimer(TIMER_SWITCH_SCAN);
}

// Does the specific behavior for switch 1 being pressed
void DoSwitch1PressedBehavior(void)
{
    if (attributeTableInvalid == true) // Error catching
    {
        return; // Don't do anything if no attribute table is loaded
    }
    
    uint24_t switch1flashAddress;
    uint24_t switch2flashAddress;
    
    // When switch 1 is pressed, change both switches to the addresses in the
    // switch1PressAddress and switch2PressAddress for switch 1, respectively
    uint24_t attributeSize = GetCurrentSwitchAttributeSize();
    
    if (switch1ImageAttributes.switch1PressAddress == 0x00) // Don't do anything if the press address is 0
    {
        switch1flashAddress = (switch1ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }
    else
    {
        switch1flashAddress = (switch1ImageAttributes.switch1PressAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;   
    }    
    
    if (switch1ImageAttributes.switch2PressAddress == 0x00) // Don't do anything if the press address is 0
    {
        switch2flashAddress = (switch2ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }
    else
    {
        switch2flashAddress = (switch1ImageAttributes.switch2PressAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;   
    }    
    
    ReadImageAttribute(switch1flashAddress, &switch1ImageAttributes);
    ReadImageAttribute(switch2flashAddress, &switch2ImageAttributes);
    
    LoadSwitch1Image(switch1ImageAttributes.currentAddress);    
    LoadSwitch2Image(switch2ImageAttributes.currentAddress);    
    
    CheckIfSwitch1LoopTimerNeedsStarting();
    CheckIfSwitch2LoopTimerNeedsStarting();
    
    CheckIfSwitch1BacklightTimerNeedsStarting();
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

// Does the specific behavior for switch 2 being pressed
void DoSwitch2PressedBehavior(void)
{
    if (attributeTableInvalid == true) // Error catching
    {
        return; // Don't do anything if no attribute table is loaded
    }
     
    uint24_t switch1flashAddress;
    uint24_t switch2flashAddress;
    
    // When switch 2 is pressed, change both switches to the addresses in the
    // switch1PressAddress and switch2PressAddress for switch 2, respectively
    uint24_t attributeSize = GetCurrentSwitchAttributeSize();
    
    if (switch2ImageAttributes.switch2PressAddress == 0x00) // Don't do anything if the press address is 0
    {
        switch2flashAddress = (switch2ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }
    else
    {
        switch2flashAddress = (switch2ImageAttributes.switch2PressAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }    
    
    if (switch2ImageAttributes.switch1PressAddress == 0x00) // Don't do anything if the press address is 0
    {
        switch1flashAddress = (switch1ImageAttributes.currentAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }
    else
    {
        switch1flashAddress = (switch2ImageAttributes.switch1PressAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
    }    
    
    ReadImageAttribute(switch1flashAddress, &switch1ImageAttributes);
    ReadImageAttribute(switch2flashAddress, &switch2ImageAttributes);
    
    LoadSwitch1Image(switch1ImageAttributes.currentAddress);
    LoadSwitch2Image(switch2ImageAttributes.currentAddress);
    
    CheckIfSwitch1LoopTimerNeedsStarting();
    CheckIfSwitch2LoopTimerNeedsStarting();
    
    CheckIfSwitch1BacklightTimerNeedsStarting();
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

// Based on attributes, sets timers for switch behaviors (changing images, changing
// backlight color, Loading new attributes, etc.)
void CheckSwitchBehavior(void)
{
    uint24_t attributeSize;
    uint24_t switch1flashAddress;      
    uint24_t switch2flashAddress;         
    
    if (CheckIfTimerExpired(TIMER_SWITCH1_LOOP) == true) // This defaults to false if the timer isn't running
    {
        if (switch1ImageAttributes.loopCurrentAddress == switch1ImageAttributes.loopEndAddress) // If we are at the end of the loop
        {
            StopTimer(TIMER_SWITCH1_LOOP);
            
            attributeSize = GetCurrentSwitchAttributeSize();
            // We check the other switch first because we may be about to change what we're reading
            if (switch1ImageAttributes.switch2TimerExpiredJumpAddress == 0x0) // A zero means stay at the same address
            {
                // Don't do anything for switch 2, let it keep doing it's thing
            }
            else
            {
                switch2flashAddress = (switch1ImageAttributes.switch2TimerExpiredJumpAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
                ReadImageAttribute(switch2flashAddress, &switch2ImageAttributes);
                LoadSwitch2Image(switch2ImageAttributes.currentAddress);
                CheckIfSwitch2LoopTimerNeedsStarting();
                CheckIfSwitch2BacklightTimerNeedsStarting();
                switch2ImageAttributes.loopCurrentAddress = switch2ImageAttributes.currentAddress; // Need to re-set the loop address
            }       
            
            if (switch1ImageAttributes.switch1TimerExpiredJumpAddress == 0x0) // A zero means stay at the same address
            {
                switch1ImageAttributes.loopCurrentAddress = switch1ImageAttributes.currentAddress;
                LoadSwitch1Image(switch1ImageAttributes.loopCurrentAddress);
                CheckIfSwitch1LoopTimerNeedsStarting();
                LoopSwitch1BacklightColor();                  
            }
            else
            {
                switch1flashAddress = (switch1ImageAttributes.switch1TimerExpiredJumpAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
                ReadImageAttribute(switch1flashAddress, &switch1ImageAttributes);
                LoadSwitch1Image(switch1ImageAttributes.currentAddress);
                CheckIfSwitch1LoopTimerNeedsStarting();
                CheckIfSwitch1BacklightTimerNeedsStarting();
                switch1ImageAttributes.loopCurrentAddress = switch1ImageAttributes.currentAddress; // Need to re-set the loop address
            }                                
        }
        else // If we're not at the end address increment the counter, load the new image, and re-start the timer
        {
            switch1ImageAttributes.loopCurrentAddress++;
            LoadSwitch1Image(switch1ImageAttributes.loopCurrentAddress);                         
            LoopSwitch1BacklightColor();                  
            RestartTimer(TIMER_SWITCH1_LOOP);            
        }
        
        responsesEnum response = RESPONSE_SWITCH1_TIMER_EXPIRED;
        SendResponseOverSerial(response);
    }
    
    if (CheckIfTimerExpired(TIMER_SWITCH2_LOOP) == true) // This defaults to false if the timer isn't running
    {
        if (switch2ImageAttributes.loopCurrentAddress == switch2ImageAttributes.loopEndAddress)
        {
            StopTimer(TIMER_SWITCH2_LOOP);
            
            attributeSize = GetCurrentSwitchAttributeSize();
            // We check the other switch first because we may be about to change what we're reading
            if (switch2ImageAttributes.switch1TimerExpiredJumpAddress == 0x0) // A zero means stay at the same address
            {
                // Don't do anything for switch 1, let it keep doing it's thing
            }
            else
            {
                switch1flashAddress = (switch2ImageAttributes.switch1TimerExpiredJumpAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
                ReadImageAttribute(switch1flashAddress, &switch1ImageAttributes);
                LoadSwitch1Image(switch1ImageAttributes.currentAddress);
                CheckIfSwitch1LoopTimerNeedsStarting();
                CheckIfSwitch1BacklightTimerNeedsStarting();
                switch1ImageAttributes.loopCurrentAddress = switch1ImageAttributes.currentAddress; // Need to re-set the loop address
            }
            
            if (switch2ImageAttributes.switch2TimerExpiredJumpAddress == 0x0) // A zero means stay at the same address
            {
                switch2ImageAttributes.loopCurrentAddress = switch2ImageAttributes.currentAddress;
                LoadSwitch2Image(switch2ImageAttributes.loopCurrentAddress);
                CheckIfSwitch2LoopTimerNeedsStarting();
                LoopSwitch2BacklightColor();             
            }
            else
            {
                switch2flashAddress = (switch2ImageAttributes.switch2TimerExpiredJumpAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS;
                ReadImageAttribute(switch2flashAddress, &switch2ImageAttributes);
                LoadSwitch2Image(switch2ImageAttributes.currentAddress);
                CheckIfSwitch2LoopTimerNeedsStarting();
                CheckIfSwitch2BacklightTimerNeedsStarting();
                switch2ImageAttributes.loopCurrentAddress = switch2ImageAttributes.currentAddress; // Need to re-set the loop address
            }                   
        }
        else // If we're not at the end address increment the counter, load the new image, and re-start the timer
        {
            switch2ImageAttributes.loopCurrentAddress++;
            LoadSwitch2Image(switch2ImageAttributes.loopCurrentAddress);                       
            LoopSwitch2BacklightColor();             
            RestartTimer(TIMER_SWITCH2_LOOP);            
        }
        
        responsesEnum response = RESPONSE_SWITCH2_TIMER_EXPIRED;
        SendResponseOverSerial(response);
    }
    
    if (CheckIfTimerExpired(TIMER_SWITCH1_BACKLIGHT) == true) // This defaults to false if the timer isn't running
    {
        StopTimer(TIMER_SWITCH1_BACKLIGHT);
        
        if (switch1ImageAttributes.currentBacklightColor == switch1ImageAttributes.backlightColorState1)
        {
            switch1ImageAttributes.currentBacklightColor = switch1ImageAttributes.backlightColorState2;            
        }
        else
        {
            switch1ImageAttributes.currentBacklightColor = switch1ImageAttributes.backlightColorState1;      
        }        
        ChangeSwitchBacklight();
        StartTimer(TIMER_SWITCH1_BACKLIGHT, BACKLIGHT_COLOR_TIME_ON);
    }
    
    if (CheckIfTimerExpired(TIMER_SWITCH2_BACKLIGHT) == true) // This defaults to false if the timer isn't running
    {
        StopTimer(TIMER_SWITCH2_BACKLIGHT);
        
        if (switch2ImageAttributes.currentBacklightColor == switch2ImageAttributes.backlightColorState1)
        {
            switch2ImageAttributes.currentBacklightColor = switch2ImageAttributes.backlightColorState2;            
        }
        else
        {
            switch2ImageAttributes.currentBacklightColor = switch2ImageAttributes.backlightColorState1;          
        }        
        ChangeSwitchBacklight();
        StartTimer(TIMER_SWITCH2_BACKLIGHT, BACKLIGHT_COLOR_TIME_ON);
    }        
}

// If the timer1 attribute isn't 0, there is a loop and need to start a timer to cycle through images
void CheckIfSwitch1LoopTimerNeedsStarting(void)
{
    if (attributeTableInvalid == true)
    {
        return; // Error catching
    }
    
    if (switch1ImageAttributes.timer1 != 0)
    {
        unsigned int timeToShowImagesInMs;
        if (switch1ImageAttributes.timer2 == 0)
        {
            timeToShowImagesInMs = (unsigned int) (switch1ImageAttributes.timer1 * 0x100); // A 0 in timer 2 equals 256
        }    
        else
        {
            timeToShowImagesInMs = (unsigned int) (switch1ImageAttributes.timer1 * switch1ImageAttributes.timer2); // Multiply the timers together for the duration
        }
        StartTimer(TIMER_SWITCH1_LOOP, timeToShowImagesInMs);
        switch1ImageAttributes.loopCurrentAddress = switch1ImageAttributes.currentAddress; // Need to re-set the loop address
    }
    else
    {
        StopTimer(TIMER_SWITCH1_LOOP);
    }
}

// If the timer1 attribute isn't 0, there is a loop and need to start a timer to cycle through images
void CheckIfSwitch2LoopTimerNeedsStarting(void)
{
    if (attributeTableInvalid == true)
    {
        return; // Error catching
    }
    
    if (switch2ImageAttributes.timer1 != 0)
    {
        unsigned int timeToShowImagesInMs;
        if (switch2ImageAttributes.timer2 == 0)
        {
            timeToShowImagesInMs = (unsigned int) (switch2ImageAttributes.timer1 * 0x100); // A 0 in timer 2 equals 256
        }    
        else
        {
            timeToShowImagesInMs = (unsigned int) (switch2ImageAttributes.timer1 * switch2ImageAttributes.timer2); // Multiply the timers together for the duration
        }
        StartTimer(TIMER_SWITCH2_LOOP, timeToShowImagesInMs);
        switch2ImageAttributes.loopCurrentAddress = switch2ImageAttributes.currentAddress; // Need to re-set the loop address
    }
    else
    {
        StopTimer(TIMER_SWITCH2_LOOP);
    }
}

// Sets the backlight based on attributes values, and starts the timer
void CheckIfSwitch1BacklightTimerNeedsStarting(void)
{
    if (attributeTableInvalid == true)
    {
        return; // Error catching
    }
    
    if (switch1ImageAttributes.backlightColorState1 == 0 &&
        switch1ImageAttributes.backlightColorState2 == 0 ) // If both are zero, always on
    {
        StopTimer(TIMER_SWITCH1_BACKLIGHT);
        switch1ImageAttributes.currentBacklightColor = SWITCH_COLOR_WHITE;
        ChangeSwitchBacklight();        
    }
    else
    {
        switch1ImageAttributes.currentBacklightColor = switch1ImageAttributes.backlightColorState1;
        ChangeSwitchBacklight(); 
        StartTimer(TIMER_SWITCH1_BACKLIGHT, BACKLIGHT_COLOR_TIME_ON);
    }
}

// Sets the backlight based on attributes values, and starts the timer
void CheckIfSwitch2BacklightTimerNeedsStarting(void)
{
    if (attributeTableInvalid == true)
    {
        return; // Error catching
    }
    
    if (switch2ImageAttributes.backlightColorState1 == 0 &&
        switch2ImageAttributes.backlightColorState2 == 0) // If both are zero, always on
    {
        StopTimer(TIMER_SWITCH2_BACKLIGHT);
        switch2ImageAttributes.currentBacklightColor = SWITCH_COLOR_WHITE;
        ChangeSwitchBacklight();        
    }
    else
    {
        switch2ImageAttributes.currentBacklightColor = switch2ImageAttributes.backlightColorState1;
        ChangeSwitchBacklight(); 
        StartTimer(TIMER_SWITCH2_BACKLIGHT, BACKLIGHT_COLOR_TIME_ON);
    }
}

// Refreshes the images on both switches.
void RefreshSwitchImage(void)
{          
    if (currentImageRefreshLine == 0) // We have to enable first line marker if we're back at the top
    {
        EnableFirstLineMarker();   
    }       
    
    for (signed char  i = 9; i >= 0; i--)
    {
       EUSART2_Write(switchImageBuffer[currentImageRefreshLine][i]);
    }
    
    while (EUSART2_is_tx_done() == false) // Wait for the transmit to finish
    {        
    }
    
    EnableSwitchLatchPulse();   
    DisableSwitchLatchPulse(); // After the data is sent we have to toggle the latch pin to load the image
    
    if (currentImageRefreshLine == 0)
    {
        DisableFirstLineMarker(); // Need to disable after latch pulse has been sent
    }
    
    currentImageRefreshLine++;
    if (currentImageRefreshLine > 23) // Only 24 lines, so roll over if we reach that
    {
       currentImageRefreshLine = 0;
    }    
}

// Manually changes the images to the ones specified in the parameters
void SetSwitchImages(uint24_t switch1Address, uint24_t switch2Address)
{
    uint24_t flashAddress;
    uint24_t attributeSize;
    
    if (attributeTableInvalid == false)
    {
        attributeSize = GetCurrentSwitchAttributeSize();
        flashAddress = (uint24_t) ((switch1Address * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS); // We define the flash attributes to be in a specific part of memory
    
        ReadImageAttribute(flashAddress, &switch1ImageAttributes); // Loads the attributes into the struct
    
        flashAddress = (uint24_t) ((switch2Address * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS);
        ReadImageAttribute(flashAddress, &switch2ImageAttributes); // Loads the attributes into the struct   
    }
    else // If the attribute table is invalid load the addresses sent without the attributes
    {
        switch1ImageAttributes.currentAddress = switch1Address;
        switch2ImageAttributes.currentAddress = switch2Address;
    }       
        
    LoadSwitch1Image(switch1ImageAttributes.currentAddress);  // Loads the image on to the switch
    LoadSwitch2Image(switch2ImageAttributes.currentAddress);
    
    CheckIfSwitch1LoopTimerNeedsStarting();
    CheckIfSwitch2LoopTimerNeedsStarting();
    
    CheckIfSwitch1BacklightTimerNeedsStarting();
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

// Sends a response to the host that the switch 1 image changed
void SendSwitch1ImageChangedNotification(uint24_t imageAddress)
{
    char addressHigh    = (imageAddress & 0xFF00) >> 8;
    char addressLow     = (imageAddress & 0x00FF);
    char convertedAsciiBuffer[2];
    
    SendResponseOverSerial(RESPONSE_SWITCH1_CHANGED_IMAGE);    
    
    ConvertAsciiToAsciiHex(addressHigh,convertedAsciiBuffer);
    SendResponseOverSerial(convertedAsciiBuffer[0]);
    SendResponseOverSerial(convertedAsciiBuffer[1]);
    
    ConvertAsciiToAsciiHex(addressLow,convertedAsciiBuffer);
    SendResponseOverSerial(convertedAsciiBuffer[0]);
    SendResponseOverSerial(convertedAsciiBuffer[1]);    
}

// Sends a response to the host that the switch 2 image changed
void SendSwitch2ImageChangedNotification(uint24_t imageAddress)
{
    char addressHigh    = (imageAddress & 0xFF00) >> 8;
    char addressLow     = (imageAddress & 0x00FF);
    char convertedAsciiBuffer[2];
    
    SendResponseOverSerial(RESPONSE_SWITCH2_CHANGED_IMAGE);    
    
    ConvertAsciiToAsciiHex(addressHigh,convertedAsciiBuffer);
    SendResponseOverSerial(convertedAsciiBuffer[0]);
    SendResponseOverSerial(convertedAsciiBuffer[1]);
    
    ConvertAsciiToAsciiHex(addressLow,convertedAsciiBuffer);
    SendResponseOverSerial(convertedAsciiBuffer[0]);
    SendResponseOverSerial(convertedAsciiBuffer[1]);    
}


// Manually sets both switch 1 backlight colors
void SetSwitch1Backlights(unsigned char color1, unsigned char color2)
{        
    switch1ImageAttributes.backlightColorState1 = color1;
    switch1ImageAttributes.backlightColorState2 = color2;
    
    CheckIfSwitch1BacklightTimerNeedsStarting();
}

// Manually sets both switch 2 backlight colors
void SetSwitch2Backlights(unsigned char color1, unsigned char color2)
{       
    switch2ImageAttributes.backlightColorState1 = color1;
    switch2ImageAttributes.backlightColorState2 = color2;
    
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

// Manually sets brightness for both switches
void SetSwitchBrightness(unsigned char brightness)
{
    // Testing has shown ideal brightness to be approximately 0x280 (640 decimal for a 10 bit timer)
    // Testing has shown usable range to be approximately 512-896, and we want 640 in the middle
    unsigned int pwmValue = 0x200; 
    unsigned int stepValue = 42; // We want the ideal brightness to be in the middle, and this value gets us there
    unsigned int multiplier = (unsigned int)(brightness & 0x7); // Limit the user choice to 7
    
    pwmValue += stepValue * multiplier; // Add the step value multiplied by the user choice
    
    PWM3_LoadDutyValue(pwmValue);    
}

// Changes the backlight color to be the next one in the loop
void LoopSwitch1BacklightColor(void)
{
    unsigned char loopColorBuffer[2];
    // When looping, the backlight color follows the loop address
    ReadBacklightColors(switch1ImageAttributes.loopCurrentAddress,loopColorBuffer);
    switch1ImageAttributes.backlightColorState1 = loopColorBuffer[0];
    switch1ImageAttributes.backlightColorState2 = loopColorBuffer[1];
    switch1ImageAttributes.currentBacklightColor = switch1ImageAttributes.backlightColorState1;
    CheckIfSwitch1BacklightTimerNeedsStarting();
}

// Changes the backlight color to be the next one in the loop
void LoopSwitch2BacklightColor(void)
{
    unsigned char loopColorBuffer[2];
     // When looping, the backlight color follows the loop address
    ReadBacklightColors(switch2ImageAttributes.loopCurrentAddress,loopColorBuffer);
    switch2ImageAttributes.backlightColorState1 = loopColorBuffer[0];
    switch2ImageAttributes.backlightColorState2 = loopColorBuffer[1];
    switch2ImageAttributes.currentBacklightColor = switch2ImageAttributes.backlightColorState1;
    CheckIfSwitch2BacklightTimerNeedsStarting();
}

