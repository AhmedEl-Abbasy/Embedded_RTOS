/*******************************************************************************
 *  FILE DESCRIPTION
 *  ----------------------------------------------------------------------------
 * Module:
 *
 * File Name: Keypad_Task.c
 *
 * Created on:  Nov 30, 2023
 *
 * Description: Source file for Keypad in operating systems
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
static u8 keypad_Value_0 = 0xFF ;
static u32 keypad_Value_1 = 0 ;
/*******************************************************************************
 *                      Global Data                                            *
 *******************************************************************************/
keypad_mode_t keypad_mode=keypad_init_mode;
u32 keypad_Result =0 ;
u8 Keypad_state = 0;

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
void Keypad_Task(void * pvparam)
{
	portTickType Freq = 10;
	portTickType Start = xTaskGetTickCount();
	while(1)
	{
		u8 keypad_local_value= 0;
		switch(keypad_mode)
		{
		case keypad_init_mode:
		{
			keypad_vidInit();
			keypad_mode =keypad_IDE_mode;
		}
		break;
		case keypad_GetValue_mode:
		{
			keypad_mode =keypad_IDE_mode;
			keypad_Result = keypad_Value_1;
		}
		break;
		case keypad_IDE_mode:
		{
			keypad_local_value =keypad_u8GetKey();
			if(keypad_local_value !=0xff)
			{
				keypad_Value_0 = keypad_local_value;
				if((keypad_Value_0 == '1')  ||(keypad_Value_0 == '2')||
						(keypad_Value_0 == '3')  ||(keypad_Value_0 == '4')||
						(keypad_Value_0 == '5')  ||(keypad_Value_0 == '6')||
						(keypad_Value_0 == '7')  ||(keypad_Value_0 == '8')||
						(keypad_Value_0 == '9')  ||(keypad_Value_0 == '0'))
				{
					Result_FromKeypad(keypad_Value_0);
				}
				else if(keypad_Value_0 == 'E')
				{
					keypad_Value_1 =Result_FromKeypad('=');
					Keypad_state++;
				}
			}
		}
		break;
		}
		vTaskDelayUntil(&Start,Freq);
	}
}
/*******************************************************************************
 *                      End of File: Keypad_Task.c                                        *
 *******************************************************************************/

