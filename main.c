 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

/**
 * Transfers data to a MAX7219/MAX7221 register.
 * 
 * @param address The register to load data into
 * @param value   Value to store in the register
 */
void max72xx_Write(uint8_t address, uint8_t value) {

  // Ensure LOAD/CS is LOW
    IO_PC3_SetLow();

  // Send the register address
  SPI0_ByteWrite(address);

  // Send the value
  while( !SPI0_IsTxReady() );
  SPI0_ByteWrite(value);

  while( !SPI0_IsTxReady() );
  
  // Tell chip to load in data
    IO_PC3_SetHigh();
}

int main(void)
{
    SYSTEM_Initialize();
    
    SPI0_Open(0);

  // Run test
  // All LED segments should light up
  max72xx_Write(0x0F, 0x01);
  
  // and then all LED segments should turn off
  max72xx_Write(0x0F, 0x00);
  
  // Enable BCD code B for almost all digits
  max72xx_Write(0x09, 0xF7);
  
  // Use lowest intensity
  max72xx_Write(0x0B, 0x07);
  
  
  // Turn on chip
//  max72xx_Write(0x0C, 0x01);
    
    while(1)
    {
        uint8_t B1 = 0;
        for( uint8_t B8 = 0; B8 < 10; B8++ ) {
            for( uint8_t B7 = 0; B7 < 10; B7++ ) {
                for( uint8_t B6 = 0; B6 < 10; B6++ ) {
                    for( uint8_t B5 = 0; B5 < 10; B5++ ) {
                        
                            for( uint8_t B3 = 0; B3 < 10; B3++ ) {
                                for( uint8_t B2 = 0; B2 < 10; B2++ ) {
                                    for( uint8_t B1 = 0; B1 < 10; B1++ ) {
                                        // Write digits
                                        if( B8 )
                                            max72xx_Write(8, B8);
                                        else
                                            max72xx_Write(8, 0xF);
                                        
                                        if( B7 || B8)
                                            max72xx_Write(7, B7);
                                        else
                                            max72xx_Write(7, 0xF);
                                            
                                        if( B6 || B7 || B8)
                                            max72xx_Write(6, B6);
                                        else
                                            max72xx_Write(6, 0xF);
                                        
                                        max72xx_Write(5, B5);
                                        
                                        max72xx_Write(4, 0x80);
                                        
                                        max72xx_Write(3, B3);
                                        max72xx_Write(2, B2);
                                        max72xx_Write(1, B1);
                                        
                                        DELAY_microseconds(963);
                                    }
                                }
                            }
                        
                    }
                }
            }
        }
    }    
}