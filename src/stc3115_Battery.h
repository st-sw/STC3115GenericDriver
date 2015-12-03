/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : stc3115_Battery.h
* Author             : AMS - IMS application
* Version            : V00
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
#ifndef __Battery_H
#define __Battery_H


/* ******************************************************************************** */
/*        INTERNAL PARAMETERS                                                       */
/*   TO BE ADJUSTED ACCORDING TO BATTERY AND APPLCICATION CHARACTERISTICS           */
/* -------------------------------------------------------------------------------- */

/*Battery parameters define  ------------------------------------------------------ */
#define BATT_CAPACITY		1500	/* battery nominal capacity in mAh					*/
#define BATT_RINT			200		/* Internal battery impedance in mOhms, 0 if unknown	*/

#define OCV_OFFSET_TAB	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} // OCVTAB	(Open Circuit Voltage curve, ie when the battery is relaxed (no charge or discharge)
	
/*Application parameters define  -------------------------------------------------- */
#define VMODE 			MIXED_MODE	/* running mode constant, VM_MODE or MIXED_MODE	*/
#define ALM_EN			0			/* Alarm enable constant, set at 1 to enable	*/
#define ALM_SOC			10			/* SOC alarm in % 								*/
#define ALM_VBAT 		3600		/* Voltage alarm in mV							*/
#define RSENSE			10			/* sense resistor (soldered on the board) in mOhms */

#define APP_EOC_CURRENT       75   		/* end charge current in mA                 */
#define APP_CUTOFF_VOLTAGE	  3000   	/* application cut-off voltage in mV      	*/

/* ******************************************************************************** */

#endif

/**** END OF FILE ****/
