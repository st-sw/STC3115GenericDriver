/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : stc3115_Battery.h
* Author             : AMS - IMS application
* Version            : V01
* Date               : 30 July 2014
* Description        : Application/Battery description
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __STC3115_I2C_H
#define __STC3115_I2C_H

#define STC3115_SLAVE_ADDRESS_7BIT 0x70
#define STC3115_SLAVE_ADDRESS_8BIT_WRITE 0xE0
#define STC3115_SLAVE_ADDRESS_8BIT_READ  0xE1

int I2C_Write(int NumberOfBytes, int RegAddress , unsigned char *TxBuffer);
int I2C_Read (int NumberOfBytes, int RegAddress , unsigned char *RxBuffer);

#endif

/**** END OF FILE ****/
