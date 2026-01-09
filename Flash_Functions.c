/*
 * File:   Flash_Functions.c
 * Author: rmcnamee
 *
 * Created on December 8, 2017, 11:09 AM
 */

#include "Flash_Functions.h"
#include "mcc_generated_files/spi1.h"
#include "IO_Functions.h"

// Per SST25VF080B datasheet, this byte signals if the memory is busy with an operation
#define FLASH_BUSY_BIT 0x01

void SendFlashAddress(uint24_t flashAddress);
void Erase4kFlashPage(uint24_t flashAddress);
void Erase32kFlashPage(uint24_t flashAddress);
void Erase64kFlashPage(uint24_t flashAddress);

// Provides the setup needed for correct flash memory operation
void SetupFlash(void)
{
    DisableFlashWriteProtect();
    DisableFlashChipSelect();
    DisableMemoryProtection();
    return;
}

// Reads the status register from the memory, and returns the status byte
uint8_t  ReadStatusRegister(void)
{
    EnableFlashChipSelect();
    
    uint8_t dummyResponse;
    uint8_t statusByte;
    
    flashCommandsEnum command = FLASH_READ_STATUS_REGISTER;
    
    dummyResponse = SPI1_Exchange8bit(command);        
    
    statusByte = SPI1_Exchange8bit(0xFF);    
        
    DisableFlashChipSelect(); // Per datasheet, drive chip select high after evey command/response           
    
    return statusByte;
}

// Reads the status register of the memory, and checks if the memory is busy
// with an operation. Returns true if the memory is busy, false otherwise
bool CheckIfFlashBusy(void)
{
    uint8_t status = ReadStatusRegister();
    uint8_t busyBit = (uint8_t) (status & FLASH_BUSY_BIT);
    if (busyBit != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// BLOCKING. Continuously polls the memory until it is not busy
void WaitUntilFlashNotBusy(void)
{
    while (CheckIfFlashBusy() == true);
    return;
}

// Sends the write enable command to the memory
void SendWriteEnableCommand(void)
{
    EnableFlashChipSelect();
    flashCommandsEnum command = FLASH_WRITE_ENABLE;
    SPI1_Exchange8bit(command);     
    DisableFlashChipSelect(); // Per datasheet, drive chip select high after evey command/response 
}

// Sends the write disable command to the memory
void SendWriteDisableCommand(void)
{
    EnableFlashChipSelect();
    flashCommandsEnum command = FLASH_WRITE_DISABLE;
    SPI1_Exchange8bit(command);     
    DisableFlashChipSelect(); // Per datasheet, drive chip select high after evey command/response 
}

// Sends the auto increment address command to the memory
void SendAutoIncrementAddressCommand(uint24_t flashAddress)
{
    EnableFlashChipSelect();
    flashCommandsEnum command = FLASH_AUTO_INCREMENT_ADDRESS_MODE;
    SPI1_Exchange8bit(command);             
    
    SendFlashAddress(flashAddress);
}

// DOES NOT CHIP ENABLE. Sends the specified flash address to the memory
void SendFlashAddress(uint24_t flashAddress)
{
    unsigned char highAddressByte = (flashAddress >> 16) & 0xFF;
    unsigned char midAddressByte = (flashAddress >> 8) & 0xFF;
    unsigned char lowAddressByte = (flashAddress >> 0) & 0xFF;
    
    SPI1_Exchange8bit(highAddressByte);
    SPI1_Exchange8bit(midAddressByte);
    SPI1_Exchange8bit(lowAddressByte);  
}

// Puts the flash chip in Auto Increment Address mode at the specified address,
// then sends the specified word. AUTO INCREMENT ADDRESS MODE STAYS ENABLED
// UNTIL FinishImageWriteToFlash IS CALLED
void StartImageWriteToFlash(uint24_t flashAddress, unsigned char* dataWord)
{
    WaitUntilFlashNotBusy();
            
    SendWriteEnableCommand();
    DisableFlashWriteProtect();                   
    SendAutoIncrementAddressCommand(flashAddress);     
    
    SPI1_Exchange8bit(dataWord[0]);
    SPI1_Exchange8bit(dataWord[1]);
        
    DisableFlashChipSelect();            
    WaitUntilFlashNotBusy();    
}

// AUTO INCREMENT ADDRESS MODE MUST BE ENABLED (by calling StartImageWriteToFlash).
// Writes the specified word to the next continuous address
void ContinueImageWriteToFlash(unsigned char* dataWord)
{
    WaitUntilFlashNotBusy();
    EnableFlashChipSelect();
    
    flashCommandsEnum command = FLASH_AUTO_INCREMENT_ADDRESS_MODE;    
    SPI1_Exchange8bit(command);
    SPI1_Exchange8bit(dataWord[0]);
    SPI1_Exchange8bit(dataWord[1]);
    
    DisableFlashChipSelect();            
    WaitUntilFlashNotBusy();    
}

// Disables Auto Increment Address mode in the flash memory. Needs to be called
// if StartImageWriteToFlash was called previously and data needs to be sent
// to a different memory location
void FinishImageWriteToFlash(void)
{    
    WaitUntilFlashNotBusy();
    EnableFlashChipSelect();
    
    flashCommandsEnum command = FLASH_WRITE_DISABLE;  
    SPI1_Exchange8bit(command); // From datasheet on correct AAI implementation
    
    DisableFlashChipSelect();            
    EnableFlashWriteProtect();   
}

// Writes a single byte to the specified address
void WriteByteToFlash(uint24_t flashAddress, unsigned char data)
{
    WaitUntilFlashNotBusy();
    
    SendWriteEnableCommand();
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_PROGRAM_SINGLE_BYTE;
    
    EnableFlashChipSelect();    
    
    SPI1_Exchange8bit(command);   
    
    SendFlashAddress(flashAddress);
    
    SPI1_Exchange8bit(data);
    
    DisableFlashChipSelect();                    
}

// Erases a 4k page in the memory
void Erase4kFlashPage(uint24_t flashAddress)
{
    WaitUntilFlashNotBusy();
    
    SendWriteEnableCommand();
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_ERASE_4K_PAGE;
    SPI1_Exchange8bit(command);  
    
    SendFlashAddress(flashAddress);  
    
    DisableFlashChipSelect();                
}

// Erases a 32k page in the memory
void Erase32kFlashPage(uint24_t flashAddress)
{
    WaitUntilFlashNotBusy();
    
    SendWriteEnableCommand();
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_ERASE_32K_PAGE;
    SPI1_Exchange8bit(command);  
    
    SendFlashAddress(flashAddress);  
    
    DisableFlashChipSelect();                
}

// Erases a 64k page in the memory
void Erase64kFlashPage(uint24_t flashAddress)
{
    WaitUntilFlashNotBusy();
    
    SendWriteEnableCommand();
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_ERASE_64K_PAGE;
    SPI1_Exchange8bit(command);  
    
    SendFlashAddress(flashAddress);  
    
    DisableFlashChipSelect();                
}

// Erases the entire flash memory chip
void EraseAllFlashMemory(void)
{
    WaitUntilFlashNotBusy();
    
    SendWriteEnableCommand();
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_ERASE_FULL_CHIP;
    SPI1_Exchange8bit(command);      
    
    WaitUntilFlashNotBusy();
    
    DisableFlashChipSelect();    
}

// Reads from flash memory at the specified address, the puts the data in the array given
void ReadFlashMemory(uint24_t flashAddress, unsigned char* dataBuffer, unsigned int numberOfBytesToRead)
{
    WaitUntilFlashNotBusy();
    
    EnableFlashChipSelect();    
    
    flashCommandsEnum command = FLASH_READ;
    SPI1_Exchange8bit(command);   
    
    SendFlashAddress(flashAddress);  
    
    for (unsigned int i = 0; i < numberOfBytesToRead; i++)
    {
        dataBuffer[i] = SPI1_Exchange8bit(0xFF);
    }
    
    DisableFlashChipSelect();
    
    return;    
}

// Disables memory protection on the flash chip. NEED TO DO THIS FIRST to be able
// to write any data to the chip
void DisableMemoryProtection(void)
{
    WaitUntilFlashNotBusy();
    SendWriteEnableCommand();    
    
    EnableFlashChipSelect();  
    flashCommandsEnum command = FLASH_ENABLE_WRITE_STATUS_REGISTER;
    SPI1_Exchange8bit(command);      
    
    DisableFlashChipSelect();                
    EnableFlashChipSelect(); 
    
    command = FLASH_WRITE_STATUS_REGISTER;    
    SPI1_Exchange8bit(command);  
    SPI1_Exchange8bit(FLASH_DISABLE_MEMORY_PROTECTION);  // Disables all memory protection on the flash chip
    
    DisableFlashChipSelect();            
}

// Erases the section of memory containing all of the flash attributes
void EraseAllFlashAttributes(void)
{
    for (uint24_t address = FLASH_ATTRIBUTE_START_ADDRESS; address < 0xFFFFF; address += 0xFFFF)
    {
        Erase64kFlashPage(address);   
    }    
}

// Erases the section of memory containing all of the images
void EraseAllFlashImages(void)
{
     for (uint24_t address = FLASH_IMAGE_START_ADDRESS; address < 0x7FFFF; address += 0xFFFF)
    {
        Erase64kFlashPage(address);   
    }    
}