/*******************************************************************************
 *  FILE DESCRIPTION
 *  ----------------------------------------------------------------------------
 * Module:
 *
 * File Name: LCD_Task.c
 *
 * Created on:  Nov 30, 2023
 *
 * Description: Source file for LCD Task in operating systems
 *
 * Author: Ahmed El-Abbasy
 *
 *******************************************************************************/
/*******************************************************************************
 *                      Includes                                               *
 *******************************************************************************/
#include "Smart_Home.h"
/*******************************************************************************
 *                      Local Data                                             *
 *******************************************************************************/

/*******************************************************************************
 *                      Global Data                                            *
 *******************************************************************************/
LCD_mode_t LCD_mode= LCD_init_mode;
u8 LCD_displayChar = '0';
char* LCD_displayStr;
u32 LCD_displayNum =0;
u8 LCD_setcmd	=0;
LCD_GoTo_t LCD_GoTo = GoTo_Row1;
boolean LCD_Semaphore = FALSE;
 /*******************************************************************************
 *                      ISR's Definitions                                      *
 *******************************************************************************/

/*******************************************************************************
 *                      Private Functions Prototypes                           *
 *******************************************************************************/

/*******************************************************************************
 *                      Private Functions Definitions                          *
 *******************************************************************************/


/*******************************************************************************
 *                      Global Functions Definitions                           *
 *******************************************************************************/

void LCD_Task(void * pvparam)
{
	 portTickType Freq = 10;
	 portTickType Start = xTaskGetTickCount();
	while(1)
	{
		switch(LCD_mode)
		{
		case LCD_init_mode:
		{
			lcd_vidInit();
			LCD_mode = LCD_IDE_mode;
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_displayChar_mode:
		{
			LCD_mode = LCD_IDE_mode;
			lcd_vidDisplyChar(LCD_displayChar);
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_displayStr_mode:
		{
			LCD_mode = LCD_IDE_mode;
			lcd_vidDisplyStr((u8*)LCD_displayStr);
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_displayNum_mode:
		{
			LCD_mode = LCD_IDE_mode;
			lcd_vidDisplyNumber(LCD_displayNum);
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_setcmd_mode:
		{
			LCD_mode = LCD_IDE_mode;
			lcd_vidSendCmd(LCD_setcmd);
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_GoTo_mode:
		{
			LCD_mode = LCD_IDE_mode;
			lcd_vidGotoRowColumn(LCD_GoTo,0);
			LCD_Semaphore =TRUE;
		}
		break;
		case LCD_IDE_mode:
		{
			;
		}
		break;
		}
		vTaskDelayUntil(&Start,Freq);
	}

}
/*******************************************************************************
 *                      End of File: LCD_Task.c                                        *
 *******************************************************************************/

