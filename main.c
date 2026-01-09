/*
 * NKK Switches S0205 36x24 Main.c file
 * v1.9.57
 * This software has a few assumptions. First, all non-commands should be sent
 * using ASCII hex. IE if the user wants to load image 001, they would send the 
 * load image command (28) followed by: 0x30 0x30 0x30 0x31 (four ASCII zeroes and
 * and ASCII 1). Second, all addressing should be sent in 2 bytes. IE address one
 * is actually 00 01 (then converted to ASCII hex). Third, the backlight color timer is a
 * set value that alternates between color state 1 and 2 when the timer expires. This
 * was purely for demonstration and the user should implement as desired
 * 
 * The Microchip Code Configurator (MCC) was used to easily generate the pin outs,
 * and we just interface to their generated files. A few of the modules were changed
 * to accommodate our code. Timer 0 was set up for 500 uSec interrupt intervals.
 * 
 * The switches are refershed with images approximately every 500 uSec. The Timer 0
 * interrupt calls RefreshSwitchImage(), which sends all the data currently in the
 * refresh buffer to the switches
 */

#include "main.h"
#include "mcc_generated_files/mcc.h"
#include "Communication_Handler.h"
#include "Setup_Program.h"
#include "Flash_Functions.h"
#include "Switch_Functions.h"

// Gets the version of software in ASCII hex
void GetSoftwareVersion(unsigned int* version)
{
    version[0] = 0x31; // Major version 1
    version[1] = 0x39; // Minor version 8
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    __delay_ms(50); // We put in a delay to allow all peripherals (switches, memory, etc.) to boot up
    SetupProgram();        
    
    while (1)
    {                           
        HandleSerialCommunications();        
        ScanSwitchesForPress();
        CheckSwitchBehavior();        
    }
}

// The data from the host arrives in a hex value, so we need
// to convert to an ASCII value for creating a nibble (half a byte)
    unsigned char ConvertAsciiHexToAscii(unsigned char data)
    {
        unsigned char result;
        
        if (data >= 0x30 && data <=  0x3F) // If the ASCII value is 0-9 (a number)
        {
            result = (unsigned char) (data - 0x30);
        }
        else if (data >= 0x41 && data <= 0x46) // Or if the ASCII value is A-F
        {
            result = (unsigned char) (data - 0x37);
        }
        else if (data >= 0x61 && data <= 0x66) // Or if the ASCII value is a-f
        {
            result = (unsigned char) (data - 0x57);
        }
        else
        {
            return RESPONSE_UNSUCCESSFUL;
        }
        
        return result;
    }
    
    // Puts the controller name in ASCII hex in the provided buffer
    void GetControllerName(char* controllerName)
    {
        // The name of this demonstration board is S02G1
        controllerName[0] = 0x53; // S in ASCII hex
        controllerName[1] = 0x30; // 0 in ASCII hex
        controllerName[2] = 0x32; // 2 in ASCII hex
        controllerName[3] = 0x30; // 0 in ASCII hex
        controllerName[4] = 0x35; // 5 in ASCII hex
    }
    
    // Gets the current switch type. This is needed for parsing serial
    // commands from the host. If coding for a different switch, change
    // the code here
    unsigned char GetCurrentSwitchCode(void)
    {
        return SWITCH_TYPE_36x24; // Change this if coding for a different switch
    }
    
    // Gets the current switch total byte size. This is needed for parsing serial
    // commands from the host. If coding for a different switch, change
    // the code here
    unsigned int GetCurrentSwitchTotalSize(void)
    {
        // The 36x24 switch gets 120 bytes, 36x24/8 = 108 bytes, padded with zeroes into 5 bytes per line
        // to fit windows bitmap scheme
        return 120; // Change this if coding for a different switch        
    }
    
    // Gets the current switch attribute byte size. This is needed for parsing serial
    // commands from the host. If coding for a different switch, change
    // the code here
    unsigned char GetCurrentSwitchAttributeSize(void)
    {
        return 16; // The attribute block for 36x24 is 16 bytes
    }
    
    // To send data out over serial, convert the ascii value to two bytes
    // of hex values for ascii to ensure no commands are being sent
    bool ConvertAsciiToAsciiHex(unsigned char data, unsigned char* convertedData)
    {
        unsigned char dataNibble[2];
        
        dataNibble[0] = (unsigned char) (data & 0xF0) >> 4; // put each nibble in the buffer
        dataNibble[1] = (unsigned char) data & 0x0F;
        
        for (unsigned char i = 0; i < 2; i++) // Convert both nibbles
        {
            if (dataNibble[i] < 0xA) // If the ASCII value is 0-9
            {
                convertedData[i] = (unsigned char) (dataNibble[i] + 0x30);
            }
            else if (dataNibble[i] >= 0xA) // Or if the ASCII value is A-F
            {
                convertedData[i] = (unsigned char) (dataNibble[i] + 0x37);
            }     
            else
            {
                return false; // Otherwise this fails
            }   
        }
        
        return true; // Return true if successful
    }
/**
 End of File
*/