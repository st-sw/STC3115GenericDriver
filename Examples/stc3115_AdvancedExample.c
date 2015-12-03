/********************************************************************************
* File Name          : STC3115 Advanced Main Example
* Author             : ST-GG
* Version            : V1.02
* Date               : 2015/12/01
* Description        : Init example for Gas Gauge / Fuel Gauge / Battery monitoring
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

static int GasGaugeTimerFinished(void);
static void Delay_ms(unsigned int value);
void ChangeLowPowerMode(void);


#define TIMER_LIMIT 0x5000 //arbitrary value to modify


int main(void)
{
	STC3115_ConfigData_TypeDef STC3115_ConfigData; 
	STC3115_BatteryData_TypeDef STC3115_BatteryData; 

	int status;
	volatile char GasGauge_HardwareShutDown = 0; //Optional: set to 1 when the user power down the hardware, and no need to monitor the battery
	volatile char GasGauge_UnknowError = 0; //Optional: set to 1 by the application when unknow gas gauge error occurs
	volatile char GasGauge_ChangeLowPowerMode = 0; //Optional: set to 1 by the application when need to decrease the gas gauge power consumption (ie. switch to voltage mode only monitoring)
	unsigned int CounterValue;
	int i;

	printf("STC3115 fuel gauge driver init ...\n");

GasGauge_Restart:

	//----------------------------------------------------------------------
	//Check I2C is working and Fuel gauge device connected
	status = STC3115_CheckI2cDeviceId();
	if (status != 0) //error
	{
		if(status == -1)
		{
			printf("STC3115: I2C error\n");
#ifdef DEBUG
			//wait to simulate the whole application restart
			while( GasGaugeTimerFinished() != 1);
			goto GasGauge_Restart;
#endif
		}
		else if(status == -2)
			printf("STC3115: Wrong device detected\n");
		else
			printf("STC3115: Unknown Hardware error\n");

		return -1; //return on error
	}


	//----------------------------------------------------------------------
	//Check Gasgauge is powered up & ready, and first measurement (V, I) is done (ie wait CounterValue is 3 or more)

	for(i=0; i<20; i++)
	{
		CounterValue = STC3115_GetRunningCounter();
		if(CounterValue >= 3) //ok, device ready
		{
			break; //exit loop
		}
		else
		{
			//wait
			Delay_ms(100);
		}
	}

	if(CounterValue < 3)
	{
		printf("STC3115: Error power up.\n");
		goto GasGauge_Restart;
	}

	//----------------------------------------------------------------------
	//Call STC3115 driver init&start function
	status = GasGauge_Initialization(&STC3115_ConfigData, &STC3115_BatteryData);
	if(status!=0 && status!=-2)
	{
		printf("STC3115: Error in GasGauge_Initialization\n");
		return -1; //return on error
	}


#ifdef DEBUG
	//----------------------------------------------------------------------
	//Check Gasgauge is running (also checked in GasGauge_Task)

	for(i=0; i<20; i++)
	{
		CounterValue = STC3115_GetRunningCounter();

		if(CounterValue > 3) //Gas gauge COUNTER stays at value '3' after power up or Soft Reset, if not running
		{
			break; //exit loop
		}
		else
		{
			//wait
			Delay_ms(100);
		}
	}

	if(CounterValue <= 3) 
	{
		printf("STC3115: Error, GasGauge not running. Check your hardware.\n");
		goto GasGauge_Restart;
	}
#endif

	//----------------------------------------------------------------------
	while(1) //main infinite loop
	{
		if(GasGauge_HardwareShutDown == 1) //Completely shutdown the platform and the Gas gauge. (not recommended, it is better ot let the Gas Gauge running, connected to battery)
		{
			GasGauge_HardwareShutDown = 0;
			status = GasGauge_Stop(); //stop the Gas gauge but keep its RAM content
			if(status != 0) printf("STC3115: Error in GasGauge_Stop\n");

#ifdef DEBUG
			//wait to simulate the application is powered off for a couple of time
			while( GasGaugeTimerFinished() != 1);
			goto GasGauge_Restart;
#endif
			return 0;
		}
		else if(GasGauge_UnknowError == 1)
		{
			GasGauge_UnknowError = 0;
			status = GasGauge_Reset(); //Reset the Gasgauge without disconnecting the battery
			if(status != 0) printf("STC3115: Error in GasGauge_Reset\n");

			goto GasGauge_Restart;
		}
		else //normal case
		{
			if(GasGaugeTimerFinished() == 1) //every 5s
			{
				if(GasGauge_ChangeLowPowerMode == 1) //switch between Voltage mode and Mixed mode
				{
					ChangeLowPowerMode();
					GasGauge_ChangeLowPowerMode = 0;
				}

				//Call task function
				status = GasGauge_Task(&STC3115_ConfigData, &STC3115_BatteryData); /* process gas gauge algorithm, returns results */

				if (status > 0) //OK, new data available
				{
					printf("Battery: SoC=%i %%, Vbat= %i mV, I=%i mA, Cap=%i mAh, T= %i °C, Pres=%i ALM=%i , CCounter=%d, Time=%d s \r\n", 
						STC3115_BatteryData.SOC * 0.1,
						STC3115_BatteryData.Voltage, 
						STC3115_BatteryData.Current, 
						STC3115_BatteryData.ChargeValue,
						STC3115_BatteryData.Temperature,
						STC3115_BatteryData.Presence, 
						STC3115_BatteryData.StatusWord >> 13, 
						STC3115_BatteryData.ConvCounter, 
						STC3115_BatteryData.ConvCounter * 0.5 //elapsed time since gas gauge started
						);
				}
				else if(status == 0) //only previous SOC, OCV and voltage are valid 
				{
					printf("Battery: Previous_SoC=%i, Vbat=%i mV, OCV=%i mV, T=%i °C \r\n", 
						STC3115_BatteryData.SOC * 0.1,
						STC3115_BatteryData.Voltage,
						STC3115_BatteryData.OCV,
						STC3115_BatteryData.Temperature);
				}
				else if(status == -1) //error occured
				{
					if(STC3115_BatteryData.Presence == 0)
					{    /*Battery disconnection has been detected			*/
						printf("STC3115 Error: Battery disconnected, or BATD pin level is over 1.61, or Vcc is below 2.7V \r\n");
					}
					else
					{
						printf("STC3115: I2C failure \r\n");
					}
				}
			} // END Timer finished
			else
			{
				//Do other Tasks here ...
			}
		} //END normal case
	}//END loop

	return 0;
}


void ChangeLowPowerMode(void)
{
	static int mode = 0;
	int status;

	if(mode == 0)
	{
		mode = !mode;
		status = STC3115_SetPowerSavingMode();
		if(status != 0) printf("STC3115: Error in SetPowerSavingMode\n");
	}
	else
	{
		mode = !mode;
		status = STC3115_StopPowerSavingMode();
		if(status != 0) printf("STC3115: Error in StopPowerSavingMode\n");
	}
}


static int GasGaugeTimerFinished(void)
{
	//dummy implementation. Better use a Hardware Timer.

	static unsigned int i = 1;

	i--;
	if( i == 0)
	{
		i = TIMER_LIMIT;
		return 1;
	}
	else
	{
		return 0;
	}
}


static void Delay_ms(unsigned int value) 
{
	//quick and dirty delay function implementation

	unsigned int i,j;
	volatile int dummy = 0;

	for(i=0; i<value; i++)
	{
		for(j=0; j<2000; j++) //pseudo 1ms
		{
			// waste function, volatile makes sure it is not being optimized out by compiler
			dummy++;
		}
	}
}

