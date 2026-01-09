/*
 * File:   Communication_Handler.c
 * Author: rmcnamee
 *
 * Created on December 7, 2017, 8:49 AM
 */

#include "Communication_Handler.h"
#include"mcc_generated_files/eusart1.h"
#include "IO_Functions.h"
#include "Flash_Functions.h"
#include "Switch_Functions.h"
#include "Timer_Functions.h"

#define SERIAL_RX_BUFFER_SIZE 64 // We define our own custom buffer size to prevent serial overflow/data loss
#define SERIAL_TX_BUFFER_SIZE 256 // We define our own custom buffer size to prevent serial overflow/data loss

#define SERIAL_TIMEOUT_TIME 400

volatile bool dataReceivedFlag; // This is set by eusart1.h and cleared when we read from the buffer in ReadByteFromSerialBuffer()
volatile bool dataErrorFlag; // This is set by a number of functions if the data isn't correct (IE pure ASCII and not ASCII in hex form)

void HandleSerialCommand(unsigned int command);
void LoadImageCommandHandler(void);
unsigned char ReadSerialData(void);
unsigned char ReadByteFromSerialBuffer(void);
void EraseMemoryCommandHandler(void);
void LoadAttributeBlockCommandHandler(void);
void TestCommandHandler(void);
void ReadBackImageCommandHandler(void);
void ReadBackAttributeCommandHandler(void);
void ResetCommandHandler(void);
void ManuallySetImagesCommandHandler(void);
void VersatileCommandHandler(void);
void ChangeBrightnessCommandHandler(void);
void ManuallySetBacklightCommandHander(void);

volatile unsigned char serialBufferRx[SERIAL_RX_BUFFER_SIZE]; // Our custom serial buffer to hold received data
volatile unsigned char serialBufferRxHeadIndex; // Incremented when data is received from the buffer
volatile unsigned char serialBufferRxTailIndex; // Incremented when data is read from the buffer

volatile unsigned char serialBufferTx[SERIAL_TX_BUFFER_SIZE]; // Our custom serial buffer to hold received data
volatile unsigned char serialBufferTxHeadIndex; // Incremented when data is received from the buffer
volatile unsigned char serialBufferTxTailIndex; // Incremented when data is read from the buffer
volatile unsigned int serialTxCountRemaining;

// Provides any setup needed for this file to function
void SetupCommunications(void)
{
    // Currently no setup to do
    return;
}

// Adds a byte to the buffer to send to the host (sent during timer 0 interrupt)
void SendSerialByte(unsigned char byte)
{
    while (serialTxCountRemaining >= SERIAL_TX_BUFFER_SIZE); // BLOCKING. Just wait if the buffer is full
    // This should only happen when sending back image data
    serialBufferTx[serialBufferTxHeadIndex++] = byte;    
    if (serialBufferTxHeadIndex >= SERIAL_TX_BUFFER_SIZE)
    {
        serialBufferTxHeadIndex = 0;
    }                
    
    serialTxCountRemaining++;    
}

// Called by the timer 0 interrupt to send a byte to the host
void ParseSerialTxAndSendByte(void)
{
    if (serialTxCountRemaining <= 0)
    {
        return; // Leave if there is nothing to send
    }
    
    EUSART1_Write(serialBufferTx[serialBufferTxTailIndex++]);   
    if (serialBufferTxTailIndex >= SERIAL_TX_BUFFER_SIZE)
    {
        serialBufferTxTailIndex = 0;
    }
    
    serialTxCountRemaining--;
}

// Checks the buffer and handles any commands from the host
void HandleSerialCommunications(void) 
{
    if (dataReceivedFlag != true) // If there is no command, don't do anything
    {
        return;
    }
    
    unsigned char command = ReadByteFromSerialBuffer();
    HandleSerialCommand(command);
        
    return;
}

// Sets the data received flag from the serial interrupt
void SetDataReceivedFlag(void)
{
    dataReceivedFlag = true;
    return;
}

// Clears the data received flag from the serial interrupt, otherwise the 
// read infinite loops until there is a command
void ClearDataReceivedFlag(void)
{
    dataReceivedFlag = false;
    return;
}

// Sets the data received flag from the serial interrupt
void SetDataErrorFlag(void)
{
    dataErrorFlag = true;
    return;
}

// Clears the data received flag from the serial interrupt, otherwise the 
// read infinite loops until there is a command
void ClearDataErrorFlag(void)
{
    dataErrorFlag = false;
    return;
}

//Handles the serial command if it is valid
void HandleSerialCommand(unsigned int command)
{   
    switch (command)
    {
        case COMMAND_ACKNOWLEDGE:
            SendSerialByte(RESPONSE_READY);
            break;
        case COMMAND_ERASE_MEMORY:
            SendSerialByte(RESPONSE_READY);
            StopAllTimers();
            EraseMemoryCommandHandler();
            break;
        case COMMAND_RESET:
            SendSerialByte(RESPONSE_READY);
            ResetCommandHandler();
            break;
        case COMMAND_VERSATILE:
            SendSerialByte(RESPONSE_READY);
            VersatileCommandHandler();            
            break;
        case COMMAND_CHANGE_BRIGHTNESS:
            SendSerialByte(RESPONSE_READY);
            ChangeBrightnessCommandHandler();
            break;
        case COMMAND_LOAD_IMAGE:
            // Erasing the chip before receiving causes a timeout from the program, so have to send
            // the erase chip command manually before loading new images/attributes
            SendSerialByte(RESPONSE_READY);
            StopAllTimers();
            LoadImageCommandHandler();            
            break;
        case COMMAND_READ_BACK_IMAGE:
            SendSerialByte(RESPONSE_READY);
            ReadBackImageCommandHandler();
            break;
        case COMMAND_LOAD_ATTRIBUTE_BLOCK:
            // Erasing the chip before receiving causes a timeout from the program, so have to send
            // the erase chip command manually before loading new images/attributes
            SendSerialByte(RESPONSE_READY);
            StopAllTimers();
            LoadAttributeBlockCommandHandler();
            break;     
        case COMMAND_READ_BACK_ATTRIBUTE_BLOCK:
            SendSerialByte(RESPONSE_READY);
            ReadBackAttributeCommandHandler();
            break;
        case COMMAND_CHANGE_BACKLIGHT:
            SendSerialByte(RESPONSE_READY);
            ManuallySetBacklightCommandHander();
            break;
        case COMMAND_MANUALLY_SET_IMAGES:
            SendSerialByte(RESPONSE_READY);
            ManuallySetImagesCommandHandler();
            break;
        case COMMAND_TEST:
            TestCommandHandler(); // For debugging/testing, add in if needed
            break;
        default:
            //If it is not a command we do not respond at all
            if ((command & 0x20) == 1) // If it is an unrecognized command
            {
                SendSerialByte(RESPONSE_UNSUCCESSFUL);
            }
            break;            
    }    
    return;
}

// Checks the 4 special characters to verify the user intends to erase, then erases the chip
void EraseMemoryCommandHandler(void)
{
    unsigned char response;
 
    response = ReadByteFromSerialBuffer();   
    if (response != ERASE_MEMORY_VERIFICATION_1)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
 
    response = ReadByteFromSerialBuffer();   
    if (response != ERASE_MEMORY_VERIFICATION_2)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
 
    response = ReadByteFromSerialBuffer();   
    if (response != ERASE_MEMORY_VERIFICATION_3)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
 
    response = ReadByteFromSerialBuffer();   
    if (response != ERASE_MEMORY_VERIFICATION_4)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }     
    
    EraseAllFlashMemory();     
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Resets the microcontroller
void ResetCommandHandler(void)
{
    RESET(); // Assembly command to reset the microcontroller
}

// If commanded to stop
void VersatileStopCommand(void)
{
    StopAllTimers();
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// If commanded to send version information
void VersatileVersionCommand(void)
{
    unsigned char switchCode;
    unsigned char controllerName[5];
    unsigned int version[2];
    
    switchCode = GetCurrentSwitchCode();
    GetControllerName(controllerName);
    GetSoftwareVersion(version);
    
    SendSerialByte(switchCode);
    
    for (unsigned char i =0; i < 5; i++)
    {
        SendSerialByte(controllerName[i]);
    }
    
    for (unsigned char j = 0; j < 2; j++)
    {
        SendSerialByte(version[j]);
    }
        
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Does several functions depending on the sub command
void VersatileCommandHandler(void)
{
    unsigned char subCommand1;
    unsigned char subCommand2;
    
    subCommand1 = ReadByteFromSerialBuffer();
    subCommand2 = ReadByteFromSerialBuffer();        
    
    switch (subCommand1)
    {
        default:
            SendSerialByte(RESPONSE_UNSUCCESSFUL); 
            return;
        case VERSATILE_SUBCOMMAND1_STOP:
            if (subCommand2 != VERSATILE_SUBCOMMAND2_STOP)
            {
                SendSerialByte(RESPONSE_UNSUCCESSFUL); 
                return;
            }
            VersatileStopCommand();
            break;
        case VERSATILE_SUBCOMMAND1_VERSION:
            if (subCommand2 != VERSATILE_SUBCOMMAND2_VERSION)
            {
                SendSerialByte(RESPONSE_UNSUCCESSFUL); 
                return;
            }
            VersatileVersionCommand();
            break;            
    }             
}

// Handles the change brightness command
void ChangeBrightnessCommandHandler(void)
{
    unsigned char verification; 
    unsigned char brightness; 
    
    verification = ReadByteFromSerialBuffer(); // Not in ASCII hex
    brightness = ReadSerialData();
    
    if (verification != CHANGE_BRIGHTNESS_VERIFICATION)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }    
    
    SetSwitchBrightness(brightness);
    
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Loads a new attribute block at the specified address
void LoadAttributeBlockCommandHandler(void)
{
    unsigned char switchCode;
    uint24_t attributeAddress;
    uint24_t flashAddress;
    unsigned int flashPacketSize;
    unsigned char dataBuffer[2];
    
    switchCode = ReadByteFromSerialBuffer();
    if (switchCode != GetCurrentSwitchCode()) // If the user is trying to load data for a different switch, don't do anything
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    attributeAddress = (unsigned int) (ReadSerialData() << 8); // Reads the desired address (in the form 0001,0002, etc.)
    attributeAddress |= (unsigned int) ReadSerialData();    
    
    if (attributeAddress > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    uint24_t attributeSize = GetCurrentSwitchAttributeSize();
    
    // We need to translate the 001, 002 addresses sent to a physical location in memory,
    // so we multiply by the total image size and add starting address
    flashAddress = (uint24_t) ((attributeAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS);
    
    flashPacketSize = (unsigned int) (attributeSize >> 1); // We send a word/packet, so divide the total size by 2
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }    
    
    for (unsigned int i = 0; i < flashPacketSize; i++)
    {
        if (i != 0)
        {
            dataBuffer[0] = ReadSerialData();
            dataBuffer[1] = ReadSerialData();
        }
        else // The first 2 bytes are the address which we've already read, so handle differently
        {
            dataBuffer[0] = (attributeAddress >> 8) & 0xFF;
            dataBuffer[1] = attributeAddress & 0xFF;
        }
        

        if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
        {
            ClearDataErrorFlag();
            SendSerialByte(RESPONSE_UNSUCCESSFUL);
            if (i != 0)
            {
             FinishImageWriteToFlash();   
            }            
            return;
        }
        
        if (i == 0) // If this is the first data bits, send the appropriate command to flash
        {
            StartImageWriteToFlash(flashAddress, dataBuffer);
        }
        else
        {
            ContinueImageWriteToFlash(dataBuffer);
        }
    }
    FinishImageWriteToFlash();
    
    SendSerialByte(RESPONSE_SUCCESSFUL);        
}

void ReadBackAttributeCommandHandler(void)
{
    unsigned char switchCode;
    uint24_t attributeAddress;
    uint24_t flashAddress;
    unsigned char dataBuffer[8];
    unsigned char asciiConvertedData[2];
    
    switchCode = ReadByteFromSerialBuffer();   
    if (switchCode != GetCurrentSwitchCode()) // Reads the desired address (in the form 0001,0002, etc.)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    attributeAddress = (unsigned int) (ReadSerialData() << 8); // Changes the 0001,0002 into a flash memory address
    attributeAddress |= (unsigned int) ReadSerialData();   
    
    if (attributeAddress > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    uint24_t attributeSize = GetCurrentSwitchAttributeSize();
    
    // We need to translate the 001, 002 addresses sent to a physical location in memory,
    // so we multiply by the total image size and add starting address
    flashAddress = (uint24_t) ((attributeAddress * attributeSize) + FLASH_ATTRIBUTE_START_ADDRESS);
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    for (unsigned int i = 0; i < attributeSize; i += 8)
    {
        uint24_t address = flashAddress + i;
        ReadFlashMemory(address, dataBuffer, 8);
        for (unsigned int j = 0; j < 8; j++) // Converts the ASCII back into hex value and send over serial
        {
            ConvertAsciiToAsciiHex(dataBuffer[j], asciiConvertedData);
            SendSerialByte(asciiConvertedData[0]);
            SendSerialByte(asciiConvertedData[1]);
        }
    }
    
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Handles the load image command
void LoadImageCommandHandler(void)
{
    unsigned char switchCode;
    uint24_t imageAddress;
    uint24_t flashAddress;
    unsigned int flashPacketSize;
    unsigned char dataBuffer[2];
    
    switchCode = ReadByteFromSerialBuffer();   
    if (switchCode != GetCurrentSwitchCode()) // If the user is trying to load data for a different switch, don't do anything
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    imageAddress = (unsigned int)(ReadSerialData() << 8); // Reads the desired address (in the form 0001,0002, etc.)
    imageAddress |= (unsigned int) ReadSerialData();     
    
    if (imageAddress > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    uint24_t totalImageSize = GetCurrentSwitchTotalSize();
    flashPacketSize = totalImageSize >> 1; // We send a word/packet, so divide the total size by 2
    
    // We need to translate the 001, 002 addresses sent to a physical location in memory,
    // so we multiply by the total image size
    flashAddress = (imageAddress * totalImageSize) + FLASH_IMAGE_START_ADDRESS;    
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    for (unsigned int i = 0; i < flashPacketSize; i++)
    {
        dataBuffer[0] = ReadSerialData();
        dataBuffer[1] = ReadSerialData();

        if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
        {
            ClearDataErrorFlag();
            SendSerialByte(RESPONSE_UNSUCCESSFUL);
            if (i != 0)
            {
             FinishImageWriteToFlash();   
            }            
            return;
        }
        
        if (i == 0) // If this is the first data bits, send the appropriate command to flash
        {
            StartImageWriteToFlash(flashAddress, dataBuffer);
        }
        else
        {
            ContinueImageWriteToFlash(dataBuffer);
        }
    }
    FinishImageWriteToFlash();
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

void ReadBackImageCommandHandler(void)
{
    unsigned char switchCode;
    uint24_t imageAddress;
    uint24_t flashAddress;
    unsigned char dataBuffer[8];
    unsigned char asciiConvertedData[2];
    
    switchCode = ReadByteFromSerialBuffer();   
    if (switchCode != GetCurrentSwitchCode()) // If the user is trying to load data for a different switch, don't do anything
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    imageAddress = (unsigned int)(ReadSerialData() << 8); // Reads the desired address (in the form 0001,0002, etc.)
    imageAddress |= (unsigned int) ReadSerialData();                                                    
    
    if (imageAddress > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    uint24_t totalImageSize = GetCurrentSwitchTotalSize();
    
    // We need to translate the 001, 002 addresses sent to a physical location in memory,
    // so we multiply by the total image size
    flashAddress = (imageAddress * totalImageSize) + FLASH_IMAGE_START_ADDRESS;    
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    for (unsigned int i = 0; i < totalImageSize; i += 8) // Send the packets
    {
        uint24_t address = flashAddress + i;
        ReadFlashMemory(address, dataBuffer, 8);
        for (unsigned int j = 0; j < 8; j++) // Converts the ASCII back into hex value and send over serial
        {
            ConvertAsciiToAsciiHex(dataBuffer[j], asciiConvertedData);
            SendSerialByte(asciiConvertedData[0]);
            SendSerialByte(asciiConvertedData[1]);
        }
    }
    
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

void ManuallySetImagesCommandHandler(void)
{
    unsigned char switchCode;
    uint24_t image1Address;
    uint24_t image2Address;
    
    image1Address = (unsigned int)(ReadSerialData() << 8); // Reads the desired address (in the form 0001,0002, etc.)
    image1Address |= (unsigned int) ReadSerialData();    
    
    image2Address = (unsigned int)(ReadSerialData() << 8); // Reads the desired address (in the form 0001,0002, etc.)
    image2Address |= (unsigned int) ReadSerialData(); 
    
    if (dataErrorFlag == true) // If the data was not hex value ASCII don't keep going
    {
        ClearDataErrorFlag();
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    if (image1Address > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    if (image2Address > SWITCH_MAX_IMAGES)
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL);
        return;
    }
    
    SetSwitchImages(image1Address,image2Address);
    
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Handles the change backlight command
void ManuallySetBacklightCommandHander(void)
{
    unsigned char switch1Color1 = ReadSerialData();
    unsigned char switch1Color2 = ReadSerialData();
    
    unsigned char switch2Color1 = ReadSerialData();
    unsigned char switch2Color2 = ReadSerialData();
    
    if ((switch1Color1 == RESPONSE_UNSUCCESSFUL) || (switch1Color2 == RESPONSE_UNSUCCESSFUL))
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    else if ((switch2Color1 == RESPONSE_UNSUCCESSFUL) || (switch2Color2 == RESPONSE_UNSUCCESSFUL))
    {
        SendSerialByte(RESPONSE_UNSUCCESSFUL); 
        return;
    }
    
    SetSwitch1Backlights(switch1Color1,switch1Color2);
    SetSwitch2Backlights(switch2Color1,switch2Color2);
    
    SendSerialByte(RESPONSE_SUCCESSFUL);
}

// Reads then parses serial data into a byte
unsigned char ReadSerialData(void)
{
    unsigned char dataByte;
    unsigned char result;
    unsigned char asciiConverted;        
  
    dataByte = ReadByteFromSerialBuffer();
    if (dataByte == RESPONSE_UNSUCCESSFUL)
    {
        SetDataErrorFlag();
        return RESPONSE_UNSUCCESSFUL; // Error catching, if not sending in ASCII hex just quit
    }
    asciiConverted = ConvertAsciiHexToAscii(dataByte);
    if (asciiConverted == RESPONSE_UNSUCCESSFUL)
    {
        SetDataErrorFlag();
        return RESPONSE_UNSUCCESSFUL; // Error catching, if not sending in ASCII hex just quit
    }

    result = (unsigned char) (asciiConverted << 4); // The first ascii character is the upper half of a byte

    dataByte = ReadByteFromSerialBuffer();
    if (dataByte == RESPONSE_UNSUCCESSFUL)
    {
        SetDataErrorFlag();
        return RESPONSE_UNSUCCESSFUL; // Error catching, if not sending in ASCII hex just quit
    }
    asciiConverted = ConvertAsciiHexToAscii(dataByte); // Convert back to a normal byte
    if (asciiConverted == RESPONSE_UNSUCCESSFUL)
    {
        SetDataErrorFlag();
        return RESPONSE_UNSUCCESSFUL; // Error catching, if not sending in ASCII hex just quit
    }

    result = result + asciiConverted ; // The second ascii character is the lower half of a byte

    return result;
}

// Called by eusart1.c during the data received interrupt, adds a byte to the serial buffer and sets the flag
void AddByteToSerialBuffer(unsigned char data)
{
    serialBufferRx[serialBufferRxHeadIndex] = data;
    serialBufferRxHeadIndex++;
    if(serialBufferRxHeadIndex >= SERIAL_RX_BUFFER_SIZE)
    {
        serialBufferRxHeadIndex = 0;
    }
        
    SetDataReceivedFlag(); 
}

// Reads from the serial buffer
unsigned char ReadByteFromSerialBuffer(void)
{
    StartTimer(TIMER_SERIAL_TIMEOUT, SERIAL_TIMEOUT_TIME); // This blocks so we start a timer to not get stuck here
    while (dataReceivedFlag != true) // Don't do anything until the next data byte has arrived
    {
        if (CheckIfTimerExpired(TIMER_SERIAL_TIMEOUT) == true)
        {
            return RESPONSE_UNSUCCESSFUL;
        }
    }
    StopTimer(TIMER_SERIAL_TIMEOUT);
    unsigned char result = serialBufferRx[serialBufferRxTailIndex];
    serialBufferRxTailIndex++;
    if(serialBufferRxTailIndex >= SERIAL_RX_BUFFER_SIZE)
    {
        serialBufferRxTailIndex = 0;
    }
    
    if (serialBufferRxTailIndex == serialBufferRxHeadIndex)
    {
        ClearDataReceivedFlag(); // If we are caught up there is not more data to read, so clear flag
    }        
    
    return result;
}

// Sends a response over serial (Used for button presses, timers, etc.). Comment
// out command if not desired
void SendResponseOverSerial(responsesEnum response)
{
    SendSerialByte(response);
}

// Command handler for testing/debugging
void TestCommandHandler(void)
{
    // Add in code for testing if desired
}

