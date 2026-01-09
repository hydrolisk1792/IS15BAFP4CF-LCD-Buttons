/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F46K40
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set USB_CTS aliases
#define USB_CTS_TRIS               TRISAbits.TRISA0
#define USB_CTS_LAT                LATAbits.LATA0
#define USB_CTS_PORT               PORTAbits.RA0
#define USB_CTS_WPU                WPUAbits.WPUA0
#define USB_CTS_OD                ODCONAbits.ODCA0
#define USB_CTS_ANS                ANSELAbits.ANSELA0
#define USB_CTS_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define USB_CTS_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define USB_CTS_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define USB_CTS_GetValue()           PORTAbits.RA0
#define USB_CTS_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define USB_CTS_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define USB_CTS_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define USB_CTS_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define USB_CTS_SetPushPull()    do { ODCONAbits.ODCA0 = 0; } while(0)
#define USB_CTS_SetOpenDrain()   do { ODCONAbits.ODCA0 = 1; } while(0)
#define USB_CTS_SetAnalogMode()  do { ANSELAbits.ANSELA0 = 1; } while(0)
#define USB_CTS_SetDigitalMode() do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set USB_CFG_STATUS aliases
#define USB_CFG_STATUS_TRIS               TRISAbits.TRISA1
#define USB_CFG_STATUS_LAT                LATAbits.LATA1
#define USB_CFG_STATUS_PORT               PORTAbits.RA1
#define USB_CFG_STATUS_WPU                WPUAbits.WPUA1
#define USB_CFG_STATUS_OD                ODCONAbits.ODCA1
#define USB_CFG_STATUS_ANS                ANSELAbits.ANSELA1
#define USB_CFG_STATUS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define USB_CFG_STATUS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define USB_CFG_STATUS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define USB_CFG_STATUS_GetValue()           PORTAbits.RA1
#define USB_CFG_STATUS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define USB_CFG_STATUS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define USB_CFG_STATUS_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define USB_CFG_STATUS_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define USB_CFG_STATUS_SetPushPull()    do { ODCONAbits.ODCA1 = 0; } while(0)
#define USB_CFG_STATUS_SetOpenDrain()   do { ODCONAbits.ODCA1 = 1; } while(0)
#define USB_CFG_STATUS_SetAnalogMode()  do { ANSELAbits.ANSELA1 = 1; } while(0)
#define USB_CFG_STATUS_SetDigitalMode() do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set USB_SUSPEND_STATUS aliases
#define USB_SUSPEND_STATUS_TRIS               TRISAbits.TRISA2
#define USB_SUSPEND_STATUS_LAT                LATAbits.LATA2
#define USB_SUSPEND_STATUS_PORT               PORTAbits.RA2
#define USB_SUSPEND_STATUS_WPU                WPUAbits.WPUA2
#define USB_SUSPEND_STATUS_OD                ODCONAbits.ODCA2
#define USB_SUSPEND_STATUS_ANS                ANSELAbits.ANSELA2
#define USB_SUSPEND_STATUS_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define USB_SUSPEND_STATUS_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define USB_SUSPEND_STATUS_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define USB_SUSPEND_STATUS_GetValue()           PORTAbits.RA2
#define USB_SUSPEND_STATUS_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define USB_SUSPEND_STATUS_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define USB_SUSPEND_STATUS_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define USB_SUSPEND_STATUS_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define USB_SUSPEND_STATUS_SetPushPull()    do { ODCONAbits.ODCA2 = 0; } while(0)
#define USB_SUSPEND_STATUS_SetOpenDrain()   do { ODCONAbits.ODCA2 = 1; } while(0)
#define USB_SUSPEND_STATUS_SetAnalogMode()  do { ANSELAbits.ANSELA2 = 1; } while(0)
#define USB_SUSPEND_STATUS_SetDigitalMode() do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()    do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()   do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()   do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()         PORTAbits.RA5
#define RA5_SetDigitalInput()   do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()  do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()     do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()   do { WPUAbits.WPUA5 = 0; } while(0)
#define RA5_SetAnalogMode() do { ANSELAbits.ANSELA5 = 1; } while(0)
#define RA5_SetDigitalMode()do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set LED_SERIAL_CLOCK aliases
#define LED_SERIAL_CLOCK_TRIS               TRISAbits.TRISA6
#define LED_SERIAL_CLOCK_LAT                LATAbits.LATA6
#define LED_SERIAL_CLOCK_PORT               PORTAbits.RA6
#define LED_SERIAL_CLOCK_WPU                WPUAbits.WPUA6
#define LED_SERIAL_CLOCK_OD                ODCONAbits.ODCA6
#define LED_SERIAL_CLOCK_ANS                ANSELAbits.ANSELA6
#define LED_SERIAL_CLOCK_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED_SERIAL_CLOCK_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED_SERIAL_CLOCK_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED_SERIAL_CLOCK_GetValue()           PORTAbits.RA6
#define LED_SERIAL_CLOCK_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED_SERIAL_CLOCK_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define LED_SERIAL_CLOCK_SetPullup()      do { WPUAbits.WPUA6 = 1; } while(0)
#define LED_SERIAL_CLOCK_ResetPullup()    do { WPUAbits.WPUA6 = 0; } while(0)
#define LED_SERIAL_CLOCK_SetPushPull()    do { ODCONAbits.ODCA6 = 0; } while(0)
#define LED_SERIAL_CLOCK_SetOpenDrain()   do { ODCONAbits.ODCA6 = 1; } while(0)
#define LED_SERIAL_CLOCK_SetAnalogMode()  do { ANSELAbits.ANSELA6 = 1; } while(0)
#define LED_SERIAL_CLOCK_SetDigitalMode() do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set LED_LATCH_PULSE aliases
#define LED_LATCH_PULSE_TRIS               TRISAbits.TRISA7
#define LED_LATCH_PULSE_LAT                LATAbits.LATA7
#define LED_LATCH_PULSE_PORT               PORTAbits.RA7
#define LED_LATCH_PULSE_WPU                WPUAbits.WPUA7
#define LED_LATCH_PULSE_OD                ODCONAbits.ODCA7
#define LED_LATCH_PULSE_ANS                ANSELAbits.ANSELA7
#define LED_LATCH_PULSE_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_LATCH_PULSE_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_LATCH_PULSE_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_LATCH_PULSE_GetValue()           PORTAbits.RA7
#define LED_LATCH_PULSE_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_LATCH_PULSE_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define LED_LATCH_PULSE_SetPullup()      do { WPUAbits.WPUA7 = 1; } while(0)
#define LED_LATCH_PULSE_ResetPullup()    do { WPUAbits.WPUA7 = 0; } while(0)
#define LED_LATCH_PULSE_SetPushPull()    do { ODCONAbits.ODCA7 = 0; } while(0)
#define LED_LATCH_PULSE_SetOpenDrain()   do { ODCONAbits.ODCA7 = 1; } while(0)
#define LED_LATCH_PULSE_SetAnalogMode()  do { ANSELAbits.ANSELA7 = 1; } while(0)
#define LED_LATCH_PULSE_SetDigitalMode() do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set FLASH_SDO aliases
#define FLASH_SDO_TRIS               TRISBbits.TRISB0
#define FLASH_SDO_LAT                LATBbits.LATB0
#define FLASH_SDO_PORT               PORTBbits.RB0
#define FLASH_SDO_WPU                WPUBbits.WPUB0
#define FLASH_SDO_OD                ODCONBbits.ODCB0
#define FLASH_SDO_ANS                ANSELBbits.ANSELB0
#define FLASH_SDO_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define FLASH_SDO_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define FLASH_SDO_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define FLASH_SDO_GetValue()           PORTBbits.RB0
#define FLASH_SDO_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define FLASH_SDO_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define FLASH_SDO_SetPullup()      do { WPUBbits.WPUB0 = 1; } while(0)
#define FLASH_SDO_ResetPullup()    do { WPUBbits.WPUB0 = 0; } while(0)
#define FLASH_SDO_SetPushPull()    do { ODCONBbits.ODCB0 = 0; } while(0)
#define FLASH_SDO_SetOpenDrain()   do { ODCONBbits.ODCB0 = 1; } while(0)
#define FLASH_SDO_SetAnalogMode()  do { ANSELBbits.ANSELB0 = 1; } while(0)
#define FLASH_SDO_SetDigitalMode() do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set FLASH_SCK1 aliases
#define FLASH_SCK1_TRIS               TRISBbits.TRISB1
#define FLASH_SCK1_LAT                LATBbits.LATB1
#define FLASH_SCK1_PORT               PORTBbits.RB1
#define FLASH_SCK1_WPU                WPUBbits.WPUB1
#define FLASH_SCK1_OD                ODCONBbits.ODCB1
#define FLASH_SCK1_ANS                ANSELBbits.ANSELB1
#define FLASH_SCK1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define FLASH_SCK1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define FLASH_SCK1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define FLASH_SCK1_GetValue()           PORTBbits.RB1
#define FLASH_SCK1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define FLASH_SCK1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define FLASH_SCK1_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define FLASH_SCK1_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define FLASH_SCK1_SetPushPull()    do { ODCONBbits.ODCB1 = 0; } while(0)
#define FLASH_SCK1_SetOpenDrain()   do { ODCONBbits.ODCB1 = 1; } while(0)
#define FLASH_SCK1_SetAnalogMode()  do { ANSELBbits.ANSELB1 = 1; } while(0)
#define FLASH_SCK1_SetDigitalMode() do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set FLASH_WP aliases
#define FLASH_WP_TRIS               TRISBbits.TRISB2
#define FLASH_WP_LAT                LATBbits.LATB2
#define FLASH_WP_PORT               PORTBbits.RB2
#define FLASH_WP_WPU                WPUBbits.WPUB2
#define FLASH_WP_OD                ODCONBbits.ODCB2
#define FLASH_WP_ANS                ANSELBbits.ANSELB2
#define FLASH_WP_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define FLASH_WP_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define FLASH_WP_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define FLASH_WP_GetValue()           PORTBbits.RB2
#define FLASH_WP_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define FLASH_WP_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define FLASH_WP_SetPullup()      do { WPUBbits.WPUB2 = 1; } while(0)
#define FLASH_WP_ResetPullup()    do { WPUBbits.WPUB2 = 0; } while(0)
#define FLASH_WP_SetPushPull()    do { ODCONBbits.ODCB2 = 0; } while(0)
#define FLASH_WP_SetOpenDrain()   do { ODCONBbits.ODCB2 = 1; } while(0)
#define FLASH_WP_SetAnalogMode()  do { ANSELBbits.ANSELB2 = 1; } while(0)
#define FLASH_WP_SetDigitalMode() do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set FLASH_SDI aliases
#define FLASH_SDI_TRIS               TRISBbits.TRISB3
#define FLASH_SDI_LAT                LATBbits.LATB3
#define FLASH_SDI_PORT               PORTBbits.RB3
#define FLASH_SDI_WPU                WPUBbits.WPUB3
#define FLASH_SDI_OD                ODCONBbits.ODCB3
#define FLASH_SDI_ANS                ANSELBbits.ANSELB3
#define FLASH_SDI_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define FLASH_SDI_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define FLASH_SDI_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define FLASH_SDI_GetValue()           PORTBbits.RB3
#define FLASH_SDI_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define FLASH_SDI_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define FLASH_SDI_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define FLASH_SDI_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)
#define FLASH_SDI_SetPushPull()    do { ODCONBbits.ODCB3 = 0; } while(0)
#define FLASH_SDI_SetOpenDrain()   do { ODCONBbits.ODCB3 = 1; } while(0)
#define FLASH_SDI_SetAnalogMode()  do { ANSELBbits.ANSELB3 = 1; } while(0)
#define FLASH_SDI_SetDigitalMode() do { ANSELBbits.ANSELB3 = 0; } while(0)

//// get/set RB4 procedures
//#define RB4_SetHigh()    do { LATBbits.LATB4 = 1; } while(0)
//#define RB4_SetLow()   do { LATBbits.LATB4 = 0; } while(0)
//#define RB4_Toggle()   do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
//#define RB4_GetValue()         PORTBbits.RB4
//#define RB4_SetDigitalInput()   do { TRISBbits.TRISB4 = 1; } while(0)
//#define RB4_SetDigitalOutput()  do { TRISBbits.TRISB4 = 0; } while(0)
//#define RB4_SetPullup()     do { WPUBbits.WPUB4 = 1; } while(0)
//#define RB4_ResetPullup()   do { WPUBbits.WPUB4 = 0; } while(0)
//#define RB4_SetAnalogMode() do { ANSELBbits.ANSELB4 = 1; } while(0)
//#define RB4_SetDigitalMode()do { ANSELBbits.ANSELB4 = 0; } while(0)

//// get/set RB5 procedures
//#define RB5_SetHigh()    do { LATBbits.LATB5 = 1; } while(0)
//#define RB5_SetLow()   do { LATBbits.LATB5 = 0; } while(0)
//#define RB5_Toggle()   do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
//#define RB5_GetValue()         PORTBbits.RB5
//#define RB5_SetDigitalInput()   do { TRISBbits.TRISB5 = 1; } while(0)
//#define RB5_SetDigitalOutput()  do { TRISBbits.TRISB5 = 0; } while(0)
//#define RB5_SetPullup()     do { WPUBbits.WPUB5 = 1; } while(0)
//#define RB5_ResetPullup()   do { WPUBbits.WPUB5 = 0; } while(0)
//#define RB5_SetAnalogMode() do { ANSELBbits.ANSELB5 = 1; } while(0)
//#define RB5_SetDigitalMode()do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set LED_SERIAL_DATA aliases
#define LED_SERIAL_DATA_TRIS               TRISCbits.TRISC0
#define LED_SERIAL_DATA_LAT                LATCbits.LATC0
#define LED_SERIAL_DATA_PORT               PORTCbits.RC0
#define LED_SERIAL_DATA_WPU                WPUCbits.WPUC0
#define LED_SERIAL_DATA_OD                ODCONCbits.ODCC0
#define LED_SERIAL_DATA_ANS                ANSELCbits.ANSELC0
#define LED_SERIAL_DATA_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED_SERIAL_DATA_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED_SERIAL_DATA_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED_SERIAL_DATA_GetValue()           PORTCbits.RC0
#define LED_SERIAL_DATA_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED_SERIAL_DATA_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED_SERIAL_DATA_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define LED_SERIAL_DATA_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define LED_SERIAL_DATA_SetPushPull()    do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED_SERIAL_DATA_SetOpenDrain()   do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED_SERIAL_DATA_SetAnalogMode()  do { ANSELCbits.ANSELC0 = 1; } while(0)
#define LED_SERIAL_DATA_SetDigitalMode() do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set SWITCH1_OUTPUT aliases
#define SWITCH1_OUTPUT_TRIS               TRISCbits.TRISC1
#define SWITCH1_OUTPUT_LAT                LATCbits.LATC1
#define SWITCH1_OUTPUT_PORT               PORTCbits.RC1
#define SWITCH1_OUTPUT_WPU                WPUCbits.WPUC1
#define SWITCH1_OUTPUT_OD                ODCONCbits.ODCC1
#define SWITCH1_OUTPUT_ANS                ANSELCbits.ANSELC1
#define SWITCH1_OUTPUT_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SWITCH1_OUTPUT_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SWITCH1_OUTPUT_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SWITCH1_OUTPUT_GetValue()           PORTCbits.RC1
#define SWITCH1_OUTPUT_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SWITCH1_OUTPUT_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SWITCH1_OUTPUT_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define SWITCH1_OUTPUT_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define SWITCH1_OUTPUT_SetPushPull()    do { ODCONCbits.ODCC1 = 0; } while(0)
#define SWITCH1_OUTPUT_SetOpenDrain()   do { ODCONCbits.ODCC1 = 1; } while(0)
#define SWITCH1_OUTPUT_SetAnalogMode()  do { ANSELCbits.ANSELC1 = 1; } while(0)
#define SWITCH1_OUTPUT_SetDigitalMode() do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN2 aliases
#define AUXILIARY_INPUT_PIN2_TRIS               TRISCbits.TRISC2
#define AUXILIARY_INPUT_PIN2_LAT                LATCbits.LATC2
#define AUXILIARY_INPUT_PIN2_PORT               PORTCbits.RC2
#define AUXILIARY_INPUT_PIN2_WPU                WPUCbits.WPUC2
#define AUXILIARY_INPUT_PIN2_OD                ODCONCbits.ODCC2
#define AUXILIARY_INPUT_PIN2_ANS                ANSELCbits.ANSELC2
#define AUXILIARY_INPUT_PIN2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define AUXILIARY_INPUT_PIN2_GetValue()           PORTCbits.RC2
#define AUXILIARY_INPUT_PIN2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN2_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN2_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN2_SetPushPull()    do { ODCONCbits.ODCC2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN2_SetOpenDrain()   do { ODCONCbits.ODCC2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN2_SetAnalogMode()  do { ANSELCbits.ANSELC2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN2_SetDigitalMode() do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN3 aliases
#define AUXILIARY_INPUT_PIN3_TRIS               TRISCbits.TRISC3
#define AUXILIARY_INPUT_PIN3_LAT                LATCbits.LATC3
#define AUXILIARY_INPUT_PIN3_PORT               PORTCbits.RC3
#define AUXILIARY_INPUT_PIN3_WPU                WPUCbits.WPUC3
#define AUXILIARY_INPUT_PIN3_OD                ODCONCbits.ODCC3
#define AUXILIARY_INPUT_PIN3_ANS                ANSELCbits.ANSELC3
#define AUXILIARY_INPUT_PIN3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define AUXILIARY_INPUT_PIN3_GetValue()           PORTCbits.RC3
#define AUXILIARY_INPUT_PIN3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN3_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN3_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN3_SetPushPull()    do { ODCONCbits.ODCC3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN3_SetOpenDrain()   do { ODCONCbits.ODCC3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN3_SetAnalogMode()  do { ANSELCbits.ANSELC3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN3_SetDigitalMode() do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN8 aliases
#define AUXILIARY_INPUT_PIN8_TRIS               TRISCbits.TRISC4
#define AUXILIARY_INPUT_PIN8_LAT                LATCbits.LATC4
#define AUXILIARY_INPUT_PIN8_PORT               PORTCbits.RC4
#define AUXILIARY_INPUT_PIN8_WPU                WPUCbits.WPUC4
#define AUXILIARY_INPUT_PIN8_OD                ODCONCbits.ODCC4
#define AUXILIARY_INPUT_PIN8_ANS                ANSELCbits.ANSELC4
#define AUXILIARY_INPUT_PIN8_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define AUXILIARY_INPUT_PIN8_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define AUXILIARY_INPUT_PIN8_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define AUXILIARY_INPUT_PIN8_GetValue()           PORTCbits.RC4
#define AUXILIARY_INPUT_PIN8_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define AUXILIARY_INPUT_PIN8_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define AUXILIARY_INPUT_PIN8_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define AUXILIARY_INPUT_PIN8_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define AUXILIARY_INPUT_PIN8_SetPushPull()    do { ODCONCbits.ODCC4 = 0; } while(0)
#define AUXILIARY_INPUT_PIN8_SetOpenDrain()   do { ODCONCbits.ODCC4 = 1; } while(0)
#define AUXILIARY_INPUT_PIN8_SetAnalogMode()  do { ANSELCbits.ANSELC4 = 1; } while(0)
#define AUXILIARY_INPUT_PIN8_SetDigitalMode() do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set SWITCH_LATCH_PULSE aliases
#define SWITCH_LATCH_PULSE_TRIS               TRISCbits.TRISC5
#define SWITCH_LATCH_PULSE_LAT                LATCbits.LATC5
#define SWITCH_LATCH_PULSE_PORT               PORTCbits.RC5
#define SWITCH_LATCH_PULSE_WPU                WPUCbits.WPUC5
#define SWITCH_LATCH_PULSE_OD                ODCONCbits.ODCC5
#define SWITCH_LATCH_PULSE_ANS                ANSELCbits.ANSELC5
#define SWITCH_LATCH_PULSE_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SWITCH_LATCH_PULSE_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SWITCH_LATCH_PULSE_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SWITCH_LATCH_PULSE_GetValue()           PORTCbits.RC5
#define SWITCH_LATCH_PULSE_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SWITCH_LATCH_PULSE_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SWITCH_LATCH_PULSE_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define SWITCH_LATCH_PULSE_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)
#define SWITCH_LATCH_PULSE_SetPushPull()    do { ODCONCbits.ODCC5 = 0; } while(0)
#define SWITCH_LATCH_PULSE_SetOpenDrain()   do { ODCONCbits.ODCC5 = 1; } while(0)
#define SWITCH_LATCH_PULSE_SetAnalogMode()  do { ANSELCbits.ANSELC5 = 1; } while(0)
#define SWITCH_LATCH_PULSE_SetDigitalMode() do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set SWITCH_FIRST_LINE_MARKER aliases
#define SWITCH_FIRST_LINE_MARKER_TRIS               TRISCbits.TRISC6
#define SWITCH_FIRST_LINE_MARKER_LAT                LATCbits.LATC6
#define SWITCH_FIRST_LINE_MARKER_PORT               PORTCbits.RC6
#define SWITCH_FIRST_LINE_MARKER_WPU                WPUCbits.WPUC6
#define SWITCH_FIRST_LINE_MARKER_OD                ODCONCbits.ODCC6
#define SWITCH_FIRST_LINE_MARKER_ANS                ANSELCbits.ANSELC6
#define SWITCH_FIRST_LINE_MARKER_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SWITCH_FIRST_LINE_MARKER_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SWITCH_FIRST_LINE_MARKER_GetValue()           PORTCbits.RC6
#define SWITCH_FIRST_LINE_MARKER_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetPullup()      do { WPUCbits.WPUC6 = 1; } while(0)
#define SWITCH_FIRST_LINE_MARKER_ResetPullup()    do { WPUCbits.WPUC6 = 0; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetPushPull()    do { ODCONCbits.ODCC6 = 0; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetOpenDrain()   do { ODCONCbits.ODCC6 = 1; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetAnalogMode()  do { ANSELCbits.ANSELC6 = 1; } while(0)
#define SWITCH_FIRST_LINE_MARKER_SetDigitalMode() do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN4 aliases
#define AUXILIARY_INPUT_PIN4_TRIS               TRISDbits.TRISD0
#define AUXILIARY_INPUT_PIN4_LAT                LATDbits.LATD0
#define AUXILIARY_INPUT_PIN4_PORT               PORTDbits.RD0
#define AUXILIARY_INPUT_PIN4_WPU                WPUDbits.WPUD0
#define AUXILIARY_INPUT_PIN4_OD                ODCONDbits.ODCD0
#define AUXILIARY_INPUT_PIN4_ANS                ANSELDbits.ANSELD0
#define AUXILIARY_INPUT_PIN4_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define AUXILIARY_INPUT_PIN4_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define AUXILIARY_INPUT_PIN4_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define AUXILIARY_INPUT_PIN4_GetValue()           PORTDbits.RD0
#define AUXILIARY_INPUT_PIN4_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define AUXILIARY_INPUT_PIN4_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define AUXILIARY_INPUT_PIN4_SetPullup()      do { WPUDbits.WPUD0 = 1; } while(0)
#define AUXILIARY_INPUT_PIN4_ResetPullup()    do { WPUDbits.WPUD0 = 0; } while(0)
#define AUXILIARY_INPUT_PIN4_SetPushPull()    do { ODCONDbits.ODCD0 = 0; } while(0)
#define AUXILIARY_INPUT_PIN4_SetOpenDrain()   do { ODCONDbits.ODCD0 = 1; } while(0)
#define AUXILIARY_INPUT_PIN4_SetAnalogMode()  do { ANSELDbits.ANSELD0 = 1; } while(0)
#define AUXILIARY_INPUT_PIN4_SetDigitalMode() do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN5 aliases
#define AUXILIARY_INPUT_PIN5_TRIS               TRISDbits.TRISD1
#define AUXILIARY_INPUT_PIN5_LAT                LATDbits.LATD1
#define AUXILIARY_INPUT_PIN5_PORT               PORTDbits.RD1
#define AUXILIARY_INPUT_PIN5_WPU                WPUDbits.WPUD1
#define AUXILIARY_INPUT_PIN5_OD                ODCONDbits.ODCD1
#define AUXILIARY_INPUT_PIN5_ANS                ANSELDbits.ANSELD1
#define AUXILIARY_INPUT_PIN5_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define AUXILIARY_INPUT_PIN5_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define AUXILIARY_INPUT_PIN5_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define AUXILIARY_INPUT_PIN5_GetValue()           PORTDbits.RD1
#define AUXILIARY_INPUT_PIN5_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define AUXILIARY_INPUT_PIN5_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define AUXILIARY_INPUT_PIN5_SetPullup()      do { WPUDbits.WPUD1 = 1; } while(0)
#define AUXILIARY_INPUT_PIN5_ResetPullup()    do { WPUDbits.WPUD1 = 0; } while(0)
#define AUXILIARY_INPUT_PIN5_SetPushPull()    do { ODCONDbits.ODCD1 = 0; } while(0)
#define AUXILIARY_INPUT_PIN5_SetOpenDrain()   do { ODCONDbits.ODCD1 = 1; } while(0)
#define AUXILIARY_INPUT_PIN5_SetAnalogMode()  do { ANSELDbits.ANSELD1 = 1; } while(0)
#define AUXILIARY_INPUT_PIN5_SetDigitalMode() do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN6 aliases
#define AUXILIARY_INPUT_PIN6_TRIS               TRISDbits.TRISD2
#define AUXILIARY_INPUT_PIN6_LAT                LATDbits.LATD2
#define AUXILIARY_INPUT_PIN6_PORT               PORTDbits.RD2
#define AUXILIARY_INPUT_PIN6_WPU                WPUDbits.WPUD2
#define AUXILIARY_INPUT_PIN6_OD                ODCONDbits.ODCD2
#define AUXILIARY_INPUT_PIN6_ANS                ANSELDbits.ANSELD2
#define AUXILIARY_INPUT_PIN6_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN6_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN6_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define AUXILIARY_INPUT_PIN6_GetValue()           PORTDbits.RD2
#define AUXILIARY_INPUT_PIN6_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN6_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN6_SetPullup()      do { WPUDbits.WPUD2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN6_ResetPullup()    do { WPUDbits.WPUD2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN6_SetPushPull()    do { ODCONDbits.ODCD2 = 0; } while(0)
#define AUXILIARY_INPUT_PIN6_SetOpenDrain()   do { ODCONDbits.ODCD2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN6_SetAnalogMode()  do { ANSELDbits.ANSELD2 = 1; } while(0)
#define AUXILIARY_INPUT_PIN6_SetDigitalMode() do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set AUXILIARY_INPUT_PIN7 aliases
#define AUXILIARY_INPUT_PIN7_TRIS               TRISDbits.TRISD3
#define AUXILIARY_INPUT_PIN7_LAT                LATDbits.LATD3
#define AUXILIARY_INPUT_PIN7_PORT               PORTDbits.RD3
#define AUXILIARY_INPUT_PIN7_WPU                WPUDbits.WPUD3
#define AUXILIARY_INPUT_PIN7_OD                ODCONDbits.ODCD3
#define AUXILIARY_INPUT_PIN7_ANS                ANSELDbits.ANSELD3
#define AUXILIARY_INPUT_PIN7_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN7_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN7_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define AUXILIARY_INPUT_PIN7_GetValue()           PORTDbits.RD3
#define AUXILIARY_INPUT_PIN7_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN7_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN7_SetPullup()      do { WPUDbits.WPUD3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN7_ResetPullup()    do { WPUDbits.WPUD3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN7_SetPushPull()    do { ODCONDbits.ODCD3 = 0; } while(0)
#define AUXILIARY_INPUT_PIN7_SetOpenDrain()   do { ODCONDbits.ODCD3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN7_SetAnalogMode()  do { ANSELDbits.ANSELD3 = 1; } while(0)
#define AUXILIARY_INPUT_PIN7_SetDigitalMode() do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set SWITCH_SERIAL_CLOCK aliases
#define SWITCH_SERIAL_CLOCK_TRIS               TRISDbits.TRISD4
#define SWITCH_SERIAL_CLOCK_LAT                LATDbits.LATD4
#define SWITCH_SERIAL_CLOCK_PORT               PORTDbits.RD4
#define SWITCH_SERIAL_CLOCK_WPU                WPUDbits.WPUD4
#define SWITCH_SERIAL_CLOCK_OD                ODCONDbits.ODCD4
#define SWITCH_SERIAL_CLOCK_ANS                ANSELDbits.ANSELD4
#define SWITCH_SERIAL_CLOCK_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define SWITCH_SERIAL_CLOCK_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define SWITCH_SERIAL_CLOCK_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define SWITCH_SERIAL_CLOCK_GetValue()           PORTDbits.RD4
#define SWITCH_SERIAL_CLOCK_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define SWITCH_SERIAL_CLOCK_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define SWITCH_SERIAL_CLOCK_SetPullup()      do { WPUDbits.WPUD4 = 1; } while(0)
#define SWITCH_SERIAL_CLOCK_ResetPullup()    do { WPUDbits.WPUD4 = 0; } while(0)
#define SWITCH_SERIAL_CLOCK_SetPushPull()    do { ODCONDbits.ODCD4 = 0; } while(0)
#define SWITCH_SERIAL_CLOCK_SetOpenDrain()   do { ODCONDbits.ODCD4 = 1; } while(0)
#define SWITCH_SERIAL_CLOCK_SetAnalogMode()  do { ANSELDbits.ANSELD4 = 1; } while(0)
#define SWITCH_SERIAL_CLOCK_SetDigitalMode() do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set SWITCH_SERIAL_OUTPUT aliases
#define SWITCH_SERIAL_OUTPUT_TRIS               TRISDbits.TRISD5
#define SWITCH_SERIAL_OUTPUT_LAT                LATDbits.LATD5
#define SWITCH_SERIAL_OUTPUT_PORT               PORTDbits.RD5
#define SWITCH_SERIAL_OUTPUT_WPU                WPUDbits.WPUD5
#define SWITCH_SERIAL_OUTPUT_OD                ODCONDbits.ODCD5
#define SWITCH_SERIAL_OUTPUT_ANS                ANSELDbits.ANSELD5
#define SWITCH_SERIAL_OUTPUT_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define SWITCH_SERIAL_OUTPUT_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define SWITCH_SERIAL_OUTPUT_GetValue()           PORTDbits.RD5
#define SWITCH_SERIAL_OUTPUT_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetPullup()      do { WPUDbits.WPUD5 = 1; } while(0)
#define SWITCH_SERIAL_OUTPUT_ResetPullup()    do { WPUDbits.WPUD5 = 0; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetPushPull()    do { ODCONDbits.ODCD5 = 0; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetOpenDrain()   do { ODCONDbits.ODCD5 = 1; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetAnalogMode()  do { ANSELDbits.ANSELD5 = 1; } while(0)
#define SWITCH_SERIAL_OUTPUT_SetDigitalMode() do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set SWITCH2_OUTPUT aliases
#define SWITCH2_OUTPUT_TRIS               TRISDbits.TRISD6
#define SWITCH2_OUTPUT_LAT                LATDbits.LATD6
#define SWITCH2_OUTPUT_PORT               PORTDbits.RD6
#define SWITCH2_OUTPUT_WPU                WPUDbits.WPUD6
#define SWITCH2_OUTPUT_OD                ODCONDbits.ODCD6
#define SWITCH2_OUTPUT_ANS                ANSELDbits.ANSELD6
#define SWITCH2_OUTPUT_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define SWITCH2_OUTPUT_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define SWITCH2_OUTPUT_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define SWITCH2_OUTPUT_GetValue()           PORTDbits.RD6
#define SWITCH2_OUTPUT_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define SWITCH2_OUTPUT_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define SWITCH2_OUTPUT_SetPullup()      do { WPUDbits.WPUD6 = 1; } while(0)
#define SWITCH2_OUTPUT_ResetPullup()    do { WPUDbits.WPUD6 = 0; } while(0)
#define SWITCH2_OUTPUT_SetPushPull()    do { ODCONDbits.ODCD6 = 0; } while(0)
#define SWITCH2_OUTPUT_SetOpenDrain()   do { ODCONDbits.ODCD6 = 1; } while(0)
#define SWITCH2_OUTPUT_SetAnalogMode()  do { ANSELDbits.ANSELD6 = 1; } while(0)
#define SWITCH2_OUTPUT_SetDigitalMode() do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set FLASH_CS aliases
#define FLASH_CS_TRIS               TRISDbits.TRISD7
#define FLASH_CS_LAT                LATDbits.LATD7
#define FLASH_CS_PORT               PORTDbits.RD7
#define FLASH_CS_WPU                WPUDbits.WPUD7
#define FLASH_CS_OD                ODCONDbits.ODCD7
#define FLASH_CS_ANS                ANSELDbits.ANSELD7
#define FLASH_CS_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define FLASH_CS_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define FLASH_CS_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define FLASH_CS_GetValue()           PORTDbits.RD7
#define FLASH_CS_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define FLASH_CS_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define FLASH_CS_SetPullup()      do { WPUDbits.WPUD7 = 1; } while(0)
#define FLASH_CS_ResetPullup()    do { WPUDbits.WPUD7 = 0; } while(0)
#define FLASH_CS_SetPushPull()    do { ODCONDbits.ODCD7 = 0; } while(0)
#define FLASH_CS_SetOpenDrain()   do { ODCONDbits.ODCD7 = 1; } while(0)
#define FLASH_CS_SetAnalogMode()  do { ANSELDbits.ANSELD7 = 1; } while(0)
#define FLASH_CS_SetDigitalMode() do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set LED_OUTPUT_ENABLE aliases
#define LED_OUTPUT_ENABLE_TRIS               TRISEbits.TRISE0
#define LED_OUTPUT_ENABLE_LAT                LATEbits.LATE0
#define LED_OUTPUT_ENABLE_PORT               PORTEbits.RE0
#define LED_OUTPUT_ENABLE_WPU                WPUEbits.WPUE0
#define LED_OUTPUT_ENABLE_OD                ODCONEbits.ODCE0
#define LED_OUTPUT_ENABLE_ANS                ANSELEbits.ANSELE0
#define LED_OUTPUT_ENABLE_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_OUTPUT_ENABLE_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_OUTPUT_ENABLE_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_OUTPUT_ENABLE_GetValue()           PORTEbits.RE0
#define LED_OUTPUT_ENABLE_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_OUTPUT_ENABLE_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_OUTPUT_ENABLE_SetPullup()      do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_OUTPUT_ENABLE_ResetPullup()    do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_OUTPUT_ENABLE_SetPushPull()    do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_OUTPUT_ENABLE_SetOpenDrain()   do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_OUTPUT_ENABLE_SetAnalogMode()  do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_OUTPUT_ENABLE_SetDigitalMode() do { ANSELEbits.ANSELE0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/