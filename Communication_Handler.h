/*
 * File:   Communication_Handler.h
 * Author: rmcnamee
 *
 * Created on December 7, 2017, 8:47 AM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#include "main.h"

// We define 4 characters after the erase memory command to verify it wasn't an accident
#define ERASE_MEMORY_VERIFICATION_1 0x55
#define ERASE_MEMORY_VERIFICATION_2 0xAA
#define ERASE_MEMORY_VERIFICATION_3 0x52
#define ERASE_MEMORY_VERIFICATION_4 0x52

#define CHANGE_BRIGHTNESS_VERIFICATION 0x4F

#define VERSATILE_SUBCOMMAND1_STOP 0x51
#define VERSATILE_SUBCOMMAND2_STOP 0x5A
#define VERSATILE_SUBCOMMAND1_VERSION 0x52
#define VERSATILE_SUBCOMMAND2_VERSION 0x58

/**
   @Param
    none
   @Returns
    none
   @Description
    Checks the serial buffer and handles any commands from the host
   @Example
    HandleSerialCommunications();
 */
void HandleSerialCommunications(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets up the default values for variables
   @Example
    SetupCommunications();
 */
void SetupCommunications(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the data received flag
   @Example
    SetDataReceivedFlag();
 */
void SetDataReceivedFlag(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Clears the data received flag
   @Example
    ClearDataReceivedFlag();
 */
void ClearDataReceivedFlag(void);

/**
   @Param
    The data to add to the serial buffer
   @Returns
    none
   @Description
    Adds a byte to the command handler serial buffer and sets the data received flag.
 * The serial buffer created by microchip is only 8 bytes, so we define our own larger
 * one to prevent data overflow/loss
   @Example
    AddByteToSerialBuffer(0x9B);
 */
void AddByteToSerialBuffer(unsigned char data);

// A list of all possible commands this device will respond to
typedef enum
{
    COMMAND_ACKNOWLEDGE                 = 0x01,
    COMMAND_ERASE_MEMORY                = 0x21,
    COMMAND_RESET                       = 0x24,
    COMMAND_VERSATILE                   = 0x26,
    COMMAND_CHANGE_BRIGHTNESS           = 0x27,
    COMMAND_LOAD_IMAGE                  = 0x28,
    COMMAND_READ_BACK_IMAGE             = 0x29,
    COMMAND_LOAD_ATTRIBUTE_BLOCK        = 0x2A,
    COMMAND_READ_BACK_ATTRIBUTE_BLOCK   = 0x2B,
    COMMAND_CHANGE_BACKLIGHT            = 0x2C,
    COMMAND_MANUALLY_SET_IMAGES         = 0x2D,
    COMMAND_TEST                        = 0x2F
}commandsEnum;

// A list of all possible responses this device will send
typedef enum
{
    RESPONSE_SETUP_COMPLETE         = 0x11,
    RESPONSE_READY                  = 0x61,
    RESPONSE_NOT_ENOUGH_DATA        = 0x6C,
    RESPONSE_UNSUCCESSFUL           = 0x6E,
    RESPONSE_SUCCESSFUL             = 0x79,
    RESPONSE_SWITCH1_PRESSED        = 0x81,
    RESPONSE_SWITCH2_PRESSED        = 0x82,
    RESPONSE_SWITCH1_TIMER_EXPIRED  = 0x83,
    RESPONSE_SWITCH2_TIMER_EXPIRED  = 0x84,            
    RESPONSE_SWITCH1_RELEASED       = 0xC1,
    RESPONSE_SWITCH2_RELEASED       = 0xC2,
    RESPONSE_SWITCH1_CHANGED_IMAGE  = 0xFF,
    RESPONSE_SWITCH2_CHANGED_IMAGE  = 0xFE,
}responsesEnum;

// A list of all smart switch codes (only one used in this software)
typedef enum
{
    SWITCH_TYPE_36x24       = 0x51,
    SWITCH_TYPE_64x32       = 0x52,
    SWITCH_TYPE_64x48_OLED  = 0x53,
    SWITCH_TYPE_52x36_OLED  = 0x54,
    SWITCH_TYPE_OLED_ROCKER = 0x55,
    SWITCH_TYPE_96x64_OLED  = 0x56
            
}switchTypeEnum;

/**
   @Param
    The response to send over serial
   @Returns
    none
   @Description
    Allows other modules to send responses over serial. IE when a button is pressed
 * or released, and timer expiration
   @Example
    SendResponseOverSerial(RESPONSE_READY);
 */
void SendResponseOverSerial(responsesEnum response);

/**
   @Param
    The response to send over serial
   @Returns
    none
   @Description
    Adds a byte to the buffer to send to the host (sent during timer 0 interrupt)
   @Example
    SendSerialByte(0x6E);
 */
void SendSerialByte(unsigned char byte);

/**
   @Param
    Called by the timer 0 interrupt to send a byte to the host
   @Returns
    none
   @Description
    Reads from the Tx Buffer and sends a byte to the host
   @Example
    ParseSerialTxAndSendByte();
 */
void ParseSerialTxAndSendByte(void);


#endif	/* COMMUNICATION_H */