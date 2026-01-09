/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F46K40
        Driver Version    :  1.02
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

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"



void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATE = 0x00;    
    LATD = 0x00;    
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    /**
    TRISx registers
    */    
    TRISE = 0x06;
    TRISA = 0x1E;
    TRISB = 0xE8;
    TRISC = 0x9E;
    TRISD = 0x7F;

    /**
    ANSELx registers
    */   
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;
    ANSELA = 0x00;

    /**
    WPUx registers
    */ 
    WPUD = 0x4F;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x1E;

    /**
    ODx registers
    */   
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;
    
    /**
    SLRCONx registers
    */   
    SLRCONA = 0x00;
    SLRCONB = 0x00;
    SLRCONC = 0x00;
    SLRCOND = 0x00;
    SLRCONE = 0x00;

   
    
    
    bool state = (unsigned char)GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RB1PPS = 0x0F;   //RB1->MSSP1:SCK1;
    RD5PPS = 0x0C;   //RD5->EUSART2:DT2;
    RB0PPS = 0x10;   //RB0->MSSP1:SDO1;
    RD4PPS = 0x0B;   //RD4->EUSART2:CK2;
    RA5PPS = 0x07;   //RA5->PWM3:PWM3;
    RB4PPS = 0x09;   //RB4->EUSART1:TX1;
    RX1PPSbits.RXPPS = 0x0D;   //RB5->EUSART1:RX1;
    SSP1CLKPPSbits.SSPCLKPPS = 0x09;   //RB1->MSSP1:SCK1;
    TX2PPSbits.TXPPS = 0x1C;   //RD4->EUSART2:CK2;
    RX2PPSbits.RXPPS = 0x1D;   //RD5->EUSART2:DT2;
    SSP1DATPPSbits.SSPDATPPS = 0x0B;   //RB3->MSSP1:SDI1;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
}       

void PIN_MANAGER_IOC(void)
{   

}

/**
 End of File
*/