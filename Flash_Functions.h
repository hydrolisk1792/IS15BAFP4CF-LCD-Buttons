/* 
 * File:   Flash_Functions.h
 * Author: rmcnamee
 *
 * Created on December 8, 2017, 11:29 AM
 */

#ifndef FLASH_FUNCTIONS_H
#define	FLASH_FUNCTIONS_H

#include "main.h"

#define FLASH_IMAGE_START_ADDRESS       0x00000
#define FLASH_ATTRIBUTE_START_ADDRESS   0x80000

#define FLASH_ATTRIBUTE_NOT_PROGRAMMED_BYTE 0xFF

#include <stdint.h>

/**
   @Param
    none
   @Returns
    none
   @Description
    Performs any setup needed to start using the flash memory
   @Example
    SetupFlash();
 */
void SetupFlash(void);

/**
   @Param
 * flashAddress - The address in flash memory to read from
 * dataBuffer - An array to load the read data in
 * numberOfBytesToRead - The number of bytes to read from flash memory
   @Returns
    none
   @Description
    Reads from flash memory at the specified address, the puts the data in the array given
   @Example
    ReadFlashMemory(0x0001, unsigned char buffer[8], 8);
 */
void ReadFlashMemory(uint24_t flashAddress, unsigned char* dataBuffer, unsigned int numberOfBytesToRead);

/**
   @Param
 * flashAddress - The address in flash memory to write to
 * data - The data to write to flash
   @Returns
    none
   @Description
    Writes a byte to the flash memory at the specified address
   @Example
    WriteByteToFlash(0x0001, 0xB7);
 */
void WriteByteToFlash(uint24_t flashAddress, unsigned char data);

/**
   @Param
    none
   @Returns
    none
   @Description
    Disables memory protection on the flash chip. NEED TO DO THIS to be able
 * to write any data to the chip
   @Example
    DisableMemoryProtection();
 */
void DisableMemoryProtection(void);

/**
   @Param
 * flashAddress - The address in flash memory to write to
 * dataWord - An length 2 array containing the data word to write to memory
   @Returns
    none
   @Description
    Puts the flash chip in Auto Increment Address mode at the specified address,
 * then sends the specified word
   @Example
    StartImageWriteToFlash(0x80001, dataWord);
 */
void StartImageWriteToFlash(uint24_t flashAddress, unsigned char* dataWord);

/**
   @Param
 * flashAddress - The address in flash memory to write to
 * dataWord - An length 2 array containing the data word to write to memory
   @Returns
    none
   @Description
    The flash chip must already be in Auto Increment Address mode 
 * (by calling StartImageWriteToFlash). Sends the specified data word to the
 * next continuous address in the flash memory
   @Example
    ContinueImageWriteToFlash(dataWord);
 */
void ContinueImageWriteToFlash(unsigned char* dataWord);

/**
   @Param
    none
   @Returns
    none
   @Description
    Disables Auto Increment Address mode in the flash memory. Needs to be called
 * if StartImageWriteToFlash was called previously and data needs to be sent
 * to a different memory location
   @Example
    FinishImageWriteToFlash();
 */
void FinishImageWriteToFlash(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Erases the entire flash memory
   @Example
    EraseAllFlashMemory();
 */
void EraseAllFlashMemory(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Erases the section of memory containing all of the flash attributes
   @Example
    EraseAllFlashAttributes();
 */
void EraseAllFlashAttributes(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Erases the section of memory containing all of the images
   @Example
    EraseAllFlashImages();
 */
void EraseAllFlashImages(void);

// The value that disables the memory protection for the chip.
// Send after disabling write protection, enabling writing to the status register, and then following the FLASH_WRITE_STATUS_REGISTER command
#define FLASH_DISABLE_MEMORY_PROTECTION 0x02



// SST25VF080B-50 SPI Commands
typedef enum
{    
    FLASH_READ = 0x03,
    FLASH_HIGH_SPEED_READ = 0x0B,
    FLASH_ERASE_4K_PAGE = 0x20,
    FLASH_ERASE_32K_PAGE = 0x52,
    FLASH_ERASE_64K_PAGE = 0xD8,
    FLASH_ERASE_FULL_CHIP = 0xC7,
    FLASH_PROGRAM_SINGLE_BYTE = 0x02,
    FLASH_AUTO_INCREMENT_ADDRESS_MODE = 0xAD,
    FLASH_READ_STATUS_REGISTER = 0x05,
    FLASH_ENABLE_WRITE_STATUS_REGISTER = 0x50,
    FLASH_WRITE_STATUS_REGISTER = 0x01,
    FLASH_WRITE_ENABLE = 0x06,
    FLASH_WRITE_DISABLE = 0x04,
    FLASH_READ_ID = 0x90,
    FLASH_JEDEC_ID_READ = 0x9F,
    FLASH_ENABLE_SO = 0x70,
    FLASH_DISABLE_SO = 0x80
}flashCommandsEnum;

#endif	/* FLASH_FUNCTIONS_H */

