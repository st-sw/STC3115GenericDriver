/********************************************************************************
* File Name          : STC3115 basic Example
* Author             : AMS - IMS application
* Version            : V1.00
* Date               : 30 July 2014
* Description        : Application/Battery description
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#include "stc3115_Driver.h"
#include <stdio.h>

#define GASGAUGE_PERIOD 4000

int main1(void) 
{
	int i=0;
	STC3115_ConfigData_TypeDef STC3115_ConfigData; 
	STC3115_BatteryData_TypeDef STC3115_BatteryData; 

	/* Initialize I2C and GPIO */
	//GPIO_Init();
	//I2C_Init();

	/* Initialize Gas Gauge */ 
	GasGauge_Initialization(&STC3115_ConfigData, &STC3115_BatteryData); 

	/* Read and print Gas Gauge values */ 
	while(1)
	{ 
		/* Update Gas Gauge driver */ 
		if(i == GASGAUGE_PERIOD)
		{ 
			GasGauge_Task(&STC3115_ConfigData, &STC3115_BatteryData); 
			printf("Vbat: %i mV, I=%i mA SoC=%i, C=%i, P=%i A=%i , CC=%d\r\n", 
				STC3115_BatteryData.Voltage, 
				STC3115_BatteryData.Current, 
				STC3115_BatteryData.SOC, 
				STC3115_BatteryData.ChargeValue, 
				STC3115_BatteryData.Presence, 
				STC3115_BatteryData.StatusWord >> 13, 
				STC3115_BatteryData.ConvCounter); 
			i=0; 
		} 
		i++; 
	} 

	return 0; 
}

