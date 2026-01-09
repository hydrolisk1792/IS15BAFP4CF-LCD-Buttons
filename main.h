/* 
 * File:   main.h
 * Author: rmcnamee
 *
 * Created on December 7, 2017, 10:20 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "mcc_generated_files/mcc.h"

/**
   @Param
    data - the hex value to convert to ascii
   @Returns
    none
   @Description
    Converts ASCII in hex value to ASCII
   @Example
 * unsigned char serialValueReceived = 0x34;
 * unsigned char asciiValue = ConvertAsciiHexToAscii(serialValueReceived);
 * asciiValue will be 0x04, as hex value 0x34 corresponds to ASCII value 4
 */
unsigned char ConvertAsciiHexToAscii(unsigned char data);

/**
   @Param
    none
   @Returns
    The switch code for the currently in use switch
   @Description
    Every NKK switch has a code associated with it to ensure data being sent
 * is for the intended switch. This function returns the switch code for the
 * selected switch
   @Example
 * unsigned char switchCode = GetCurrentSwitchCode();
 */
unsigned char GetCurrentSwitchCode(void);

/**
   @Param
    none
   @Returns
    The number of bytes for a full image in the currently selected switch
   @Description
    Gets the number of bytes for a full image in the currently selected switch.
   @Example
 * unsigned char imageSize = GetCurrentSwitchTotalSize();
 */
unsigned int GetCurrentSwitchTotalSize(void);

/**
   @Param
    none
   @Returns
    The number of bytes for the attribute block in the currently selected switch
   @Description
    Gets the number of bytes for the attribute block in the currently selected switch. 
   @Example
 * unsigned char attributeSize = GetCurrentSwitchAttributeSize();
 */
unsigned char GetCurrentSwitchAttributeSize(void);

/**
   @Param
    none
   @Returns
    True if conversion succeeded, false otherwise
   @Description
    Converts an ASCII value to two bytes of its hex value, one for the upper nibble
 * and one for the lower nibble
   @Example
 * unsigned char valueToSend = 0xB7;
 * unsigned char convertedData[2];
 * bool succeeded = ConvertAsciiToAsciiHex(valueToSend, convertedData);
 * 
 * convertedData[0] will be 0x42, and convertedData[1] will be 0x37 (The hex
 * representations of B and 7, respectively)
 */
bool ConvertAsciiToAsciiHex(unsigned char data, unsigned char* convertedData);

/**
   @Param
    A buffer to put the controller name into
   @Returns
    none
   @Description
    Returns a buffer of the ASCII hex version of the controller name
   @Example
 * unsigned char controllerName[5];
 * GetControllerName(controllerName);
 */
void GetControllerName(char* controllerName);

/**
   @Param
    A buffer to put the software version into
   @Returns
    none
   @Description
    Returns a buffer of the ASCII hex version of the software version
   @Example
 * unsigned int version[2];
 * GetSoftwareVersion(version);
 */
void GetSoftwareVersion(unsigned int* version);

#endif	/* MAIN_H */

