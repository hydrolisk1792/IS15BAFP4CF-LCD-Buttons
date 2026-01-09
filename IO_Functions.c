/*
 * File:   IO_Functions.c
 * Author: rmcnamee
 *
 * Created on December 7, 2017, 8:53 AM
 */

#include "mcc_generated_files/pin_manager.h"
#include "IO_Functions.h"
#include "mcc_generated_files/tmr2.h"

// Provides any setup needed for IO
void SetupIo(void)
{    
    EnableLedOutput(); // Default the LEDs to always be enabled
}

// Sets CTS low, allowing the MCP2200 to send all buffered responses to the host
void SetCtsLowForSerialSend(void)
{
    USB_CTS_SetLow();
}

// Sets CTS high, so the MCP2200 will not send any responses to the host
void SetCtsHighForSerialSendComplete(void)
{
    USB_CTS_SetHigh();
}

// Active low. Enables the Flash memory chip select for SPI
void EnableFlashChipSelect(void)
{
    FLASH_CS_SetLow();
}

// Active low. Disables the Flash memory chip select for SPI
void DisableFlashChipSelect(void)
{
    FLASH_CS_SetHigh();
}

// Active low. Disables write protect on the flash memory
void DisableFlashWriteProtect(void)
{
    FLASH_WP_SetLow();
}

// Active low. Enables write protect on the flash memory
void EnableFlashWriteProtect(void)
{
    FLASH_WP_SetHigh();
}

// Enables power to the switches
void EnablePowerToSwitches(void)
{
    TMR2_Start(); // Power to switches controlled by PWM
}

// Disables power to the switches
void DisablePowerToSwitches(void)
{
    TMR2_Stop(); // Power to switches controlled by PWM
}

// Active low. Checks if switch 1 has been pressed
// Returns true if it has been pressed, false otherwise
bool CheckIfSwitch1Pressed(void)
{
    if (SWITCH1_OUTPUT_GetValue() == 0)
    {
        return true;
    }
    
    return false;
}

// Active low. Checks if switch 2 has been pressed.
// Returns true if it has been pressed, false otherwise
bool CheckIfSwitch2Pressed(void)
{
    if (SWITCH2_OUTPUT_GetValue() == 0)
    {
        return true;
    }
    
    return false;
}

// Tells the switch the line about to be sent is the first line
void EnableFirstLineMarker(void)
{
    SWITCH_FIRST_LINE_MARKER_SetHigh();
}

// Tells the switch the line just sent was the first line
void DisableFirstLineMarker(void)
{
    SWITCH_FIRST_LINE_MARKER_SetLow();
}

// Pulse the IO to tell the switch that data for the next line is ready to be loaded
void EnableSwitchLatchPulse(void)
{
    SWITCH_LATCH_PULSE_SetHigh();
}

// Pulse the IO to tell the switch that data for the next line is ready to be loaded
void DisableSwitchLatchPulse(void)
{
    SWITCH_LATCH_PULSE_SetLow();
}

// Sets the switch clock line high to manually create a clock
void SetSwitchSerialClockHigh(void)
{
    SWITCH_SERIAL_CLOCK_SetHigh();
}

// Sets the switch clock line low to manually create a clock
void SetSwitchSerialClockLow(void)
{
    SWITCH_SERIAL_CLOCK_SetLow();
}

// Sets the switch data line high
void SetSwitchSerialDataHigh(void)
{
    SWITCH_SERIAL_OUTPUT_SetHigh();
}

// Sets the switch data line low
void SetSwitchSerialDataLow(void)
{
    SWITCH_SERIAL_OUTPUT_SetLow();
}

// Sets the LED clock line high to manually create a clock
void SetLedSerialClockHigh(void)
{
    LED_SERIAL_CLOCK_SetHigh();
}

// Sets the LED clock line low to manually create a clock
void SetLedSerialClockLow(void)
{
    LED_SERIAL_CLOCK_SetLow();
}

// Sets the LED data high
void SetLedSerialDataHigh(void)
{
    LED_SERIAL_DATA_SetHigh();
}

// Sets the LED data low
void SetLedSerialDataLow(void)
{
    LED_SERIAL_DATA_SetLow();
}

// Pulse the IO to tell the LED driver chip that new states have been sent and to load them
void SetLedLatchPulseHigh(void)
{
    LED_LATCH_PULSE_SetHigh();
}

// Pulse the IO to tell the LED driver chip that new states have been sent and to load them
void SetLedLatchPulseLow(void)
{
    LED_LATCH_PULSE_SetLow();
}

// Active Low. Enables the LED output
void EnableLedOutput(void)
{
    LED_OUTPUT_ENABLE_SetLow();
}

// Active low. Disables the LED output
void DisableLedOutput(void)
{
    LED_OUTPUT_ENABLE_SetHigh();
}