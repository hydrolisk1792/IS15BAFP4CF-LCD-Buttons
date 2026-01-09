/* 
 * File:   IO_Functions.h
 * Author: rmcnamee
 *
 * Created on December 8, 2017, 8:08 AM
 */

#ifndef IO_FUNCTIONS_H
#define	IO_FUNCTIONS_H

#include "main.h"

/**
  @Summary
    Sets the CTS low to allow sending all sent data to the host

  @Description
    This routine tells the MCP2200 chip to send all data in its buffer to
 * the host. There is a maximum of 64 bits in its buffer, so this command
 * should be toggled before reaching that limit  

  @Param
    None
*/
void SetCtsLowForSerialSend(void);

/**
  @Summary
    Sets the CTS high after calling SetCtsLowForSerialSend()

  @Description
    This routine sets the CTS line high, not letting the MCP2200 chip
 * send any data back to the host

  @Param
    None
*/
void SetCtsHighForSerialSendComplete(void);

/**
  @Summary
    Enables the Flash memory chip select for SPI

  @Description
    Enables the Flash memory chip select for SPI (By setting the CS line
 * low)

  @Param
    None
*/
void EnableFlashChipSelect(void);

/**
  @Summary
    Disables the Flash memory chip select for SPI

  @Description
    Disables the Flash memory chip select for SPI (By setting the CS line
 * high)

  @Param
    None
*/
void DisableFlashChipSelect(void);

/**
  @Summary
    Disables the Flash memory chip write protection

  @Description
    Disables the Flash memory chip write protection

  @Param
    None
*/
void DisableFlashWriteProtect(void);

/**
  @Summary
    Enables the Flash memory chip write protection

  @Description
    Enables the Flash memory chip write protection

  @Param
    None
*/
void EnableFlashWriteProtect(void);

/**
  @Summary
    Sets up the default values

  @Description
    Sets up the default values

  @Param
    None
*/
void SetupIo(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Enables power to the switches
   @Example
    EnablePowerToSwitches();
 */
void EnablePowerToSwitches(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Disables power to the switches
   @Example
    DisablePowerToSwitches();
 */
void DisablePowerToSwitches(void);

/**
   @Param
    none
   @Returns
    True if the switch has been pressed, false otherwise
   @Description
    Checks if switch 1 has been pressed
   @Example
    CheckIfSwitch1Pressed();
 */
bool CheckIfSwitch1Pressed(void);

/**
   @Param
    none
   @Returns
    True if the switch has been pressed, false otherwise
   @Description
    Checks if switch 2 has been pressed
   @Example
    CheckIfSwitch2Pressed();
 */
bool CheckIfSwitch2Pressed(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Informs the switches this is the first line of the image
 * This should only be high when the first line of the image is being sent
   @Example
    EnableFirstLineMarker();
 */
void EnableFirstLineMarker(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Informs the switches the line being sent isn't the first line of the image
 * This should only be high when the first line of the image is being sent
   @Example
    DisableFirstLineMarker();
 */
void DisableFirstLineMarker(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Enables the switch latch pulse to load the serialized data onto the screen
   @Example
    EnableSwitchLatchPulse();
 */
void EnableSwitchLatchPulse(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Disables the switch latch pulse, so new serial data can be shifted in to the switch
   @Example
    DisableSwitchLatchPulse();
 */
void DisableSwitchLatchPulse(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the switch serial clock line high
   @Example
    SetSwitchSerialClockHigh();
 */
void SetSwitchSerialClockHigh(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the switch serial clock line low
   @Example
    SetSwitchSerialClockLow();
 */
void SetSwitchSerialClockLow(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the switch serial data line high
   @Example
    SetSwitchSerialDataHigh();
 */
void SetSwitchSerialDataHigh(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the switch serial data line low
   @Example
    SetSwitchSerialDataLow();
 */
void SetSwitchSerialDataLow(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED serial clock line high
   @Example
    SetLedSerialClockHigh();
 */
void SetLedSerialClockHigh(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED serial clock line low
   @Example
    SetLedSerialClockLow();
 */
void SetLedSerialClockLow(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED serial data line high
   @Example
    SetLedSerialDataHigh();
 */
void SetLedSerialDataHigh(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED serial data line low
   @Example
    SetLedSerialDataLow();
 */
void SetLedSerialDataLow(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED latch pulse line high. Pulse the IO to tell the LED driver
 * chip to load the last serial data sent
   @Example
    SetLedLatchPulseHigh();
 */
void SetLedLatchPulseHigh(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sets the LED latch pulse line low. Pulse the IO to tell the LED driver
 * chip to load the last serial data sent
   @Example
    SetLedLatchPulseLow();
 */
void SetLedLatchPulseLow(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Enables the LED output chip
   @Example
    EnableLedOutput();
 */
void EnableLedOutput(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Disables the LED output chip
   @Example
    DisableLedOutput();
 */
void DisableLedOutput(void);


#endif	/* IO_FUNCTIONS_H */

