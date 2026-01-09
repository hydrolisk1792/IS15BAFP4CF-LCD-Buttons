/* 
 * File:   Switch_Functions.h
 * Author: rmcnamee
 *
 * Created on December 13, 2017, 10:28 AM
 */

#ifndef SWITCH_FUNCTIONS_H
#define	SWITCH_FUNCTIONS_H

#include "main.h"

#define SWITCH_COLOR_WHITE 0xFF 
#define SWITCH_CONTRAST_IDEAL 0x03

#define SWITCH_MAX_IMAGES 0x7FF

/**
   @Param
    none
   @Returns
    none
   @Description
    Provides any setup the switches need before use
   @Example
    SetupSwitches();
 */
void SetupSwitches(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Scans both switches for being pressed, and does whatever behavior the attribute
 * specifies if the switch was pressed
   @Example
    ScanSwitchesForPress();
 */
void ScanSwitchesForPress(void);

/**
   @Param
    none
   @Returns
    none
   @Description
 Based on attributes, sets timers for switch behaviors (changing images, changing
 * backlight color, Loading new attributes, etc.)
 * 
   @Example
    CheckSwitchBehavior();
 */
void CheckSwitchBehavior(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Refreshes the current image on both switches
 * 
   @Example
    RefreshSwitchImage();
 */
void RefreshSwitchImage(void);

/**
   @Param
 * switch1Address - The address (0001,0002) of switch 1 in the attribute table
 * switch2Address - The address (0001,0002) of switch 2 in the attribute table
   @Returns
    none
   @Description
    Manually changes the image on both of the switches
 * 
   @Example
    SetSwitchImages(0x0001,0x0002);
 */
void SetSwitchImages(uint24_t switch1Address, uint24_t switch2Address);


/**
   @Param
 * color1 - The first color of switch 1 to cycle between
 * color2 - The second color for switch 1 to cycle between
   @Returns
    none
   @Description
    Manually changes the backlight colors of switch 1
 * 
   @Example
    SetSwitch1Backlights(0x3F,0x2B);
 */
void SetSwitch1Backlights(unsigned char color1, unsigned char color2);

/**
   @Param
 * color1 - The first color of switch 2 to cycle between
 * color2 - The second color for switch 2 to cycle between
   @Returns
    none
   @Description
    Manually changes the backlight colors of switch 2
 * 
   @Example
    SetSwitch2Backlights(0x3F,0x2B);
 */
void SetSwitch2Backlights(unsigned char color1, unsigned char color2);

/**
   @Param
 * brightness - The brightness value to set the switch to
   @Returns
    none
   @Description
    Manually changes the brightness switch 1
 * 
   @Example
    SetSwitch1Brightness(0xFF);
 */
void SetSwitchBrightness(unsigned char brightness);

// A description of every byte of the attribute block
typedef enum
{
    ATTRIBUTE_CURRENT_ADDRESS_HIGH = 0x00, // The current location
    ATTRIBUTE_CURRENT_ADDRESS_LOW,
    ATTRIBUTE_LOOP_END_ADDRESS_HIGH, // If looping, the last number of the loop (003, 0004, etc.)
    ATTRIBUTE_LOOP_END_ADDRESS_LOW,
    ATTRIBUTE_TIMER1, // Time between images of a loop, if high byte is 0 it's not a loop
    ATTRIBUTE_TIMER2,
    ATTRIBUTE_SW1_PRESS_ADDRESS_HIGH, // Address to jump to if switch 1 is pressed
    ATTRIBUTE_SW1_PRESS_ADDRESS_LOW,
    ATTRIBUTE_SW2_PRESS_ADDRESS_HIGH, // Address to jump to if switch 2 is pressed
    ATTRIBUTE_SW2_PRESS_ADDRESS_LOW,
    ATTRIBUTE_SW1_TIMER_EXPIRED_JUMP_ADDRESS_HIGH, // Address to jump to after a loop completes
    ATTRIBUTE_SW1_TIMER_EXPIRED_JUMP_ADDRESS_LOW,
    ATTRIBUTE_SW2_TIMER_EXPIRED_JUMP_ADDRESS_HIGH, // Address to jump to after a loop completes
    ATTRIBUTE_SW2_TIMER_EXPIRED_JUMP_ADDRESS_LOW,
    ATTRIBUTE_BACKLIGHT_COLOR_STATE1, // The initial color, bits are RRGGBB11
    ATTRIBUTE_BACKLIGHT_COLOR_STATE2 // The second color to change to after the timer expires
            
}attributeByteDescriptionsEnum;

typedef enum
{
    SETUP_SETUP_ADDRESS_HIGH = 0x00,
    SETUP_SETUP_ADDRESS_LOW,
    SETUP_SWITCH2_START_ADDRESS_HIGH,
    SETUP_SWITCH2_START_ADDRESS_LOW,
    SETUP_CONTRAST,
    SETUP_RESERVED1,
    SETUP_RESERVED2,
    SETUP_RESERVED3,
    SETUP_RESERVED4,
    SETUP_RESERVED5,
    SETUP_RESERVED6,
    SETUP_RESERVED7,
    SETUP_RESERVED8,
    SETUP_RESERVED9,
    SETUP_RESERVED10,
    SETUP_RESERVED11
}setupByteDescriptionsEnum;

// A struct to contain the current switch settings based on the loaded attribute
typedef struct
{
    uint24_t currentAddress;
    uint24_t loopEndAddress;
    uint24_t loopCurrentAddress;
    unsigned char timer1;
    unsigned char timer2;
    uint24_t switch1PressAddress;
    uint24_t switch2PressAddress;
    uint24_t switch1TimerExpiredJumpAddress;
    uint24_t switch2TimerExpiredJumpAddress;
    unsigned char backlightColorState1;
    unsigned char backlightColorState2;
    unsigned char currentBacklightColor;
}imageAttributeStruct;

typedef enum
{
    ATTRIBUTE_BLUE_ENABLED1 = 0x04,
    ATTRIBUTE_BLUE_ENABLED2 = 0x08,
    ATTRIBUTE_GREEN_ENABLED1 = 0x10,
    ATTRIBUTE_GREEN_ENABLED2 = 0x20,
    ATTRIBUTE_RED_ENABLED1 = 0x40,
    ATTRIBUTE_RED_ENABLED2 = 0x80            
}ledColorBitEnum;

typedef enum
{
    LED_SWITCH1_BLUE_ENABLED = 0x00,
    LED_SWITCH1_RED_ENABLED,
    LED_SWITCH1_GREEN_ENABLED,
    LED_NOT_USED1,
    LED_SWITCH2_BLUE_ENABLED,
    LED_SWITCH2_RED_ENABLED,
    LED_SWITCH2_GREEN_ENABLED,
    NOT_USED2            
}ledDriverOutputEnum;

#endif	/* SWITCH_FUNCTIONS_H */

