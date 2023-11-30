/*******************************************************************************
 *  FILE DESCRIPTION
 *  ----------------------------------------------------------------------------
 * Module:
 *
 * File Name: App1_Task.c
 *
 * Created on:  Nov 30, 2023
 *
 * Description: Source file for Application_1 in the Smart Home project
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
static app_state_t app_state =0;
static u16 ADC_Value_1 = 0 ;
static u8 check_Value =0;
/*******************************************************************************
 *                      Global Data                                            *
 *******************************************************************************/


 /*******************************************************************************
 *                      ISR's Definitions                                      *
 *******************************************************************************/

/*******************************************************************************
 *                      Private Functions Prototypes                           *
 *******************************************************************************/
static void App_LCD_Handler_mod(LCD_mode_t LCD_var);
static void App_init_Fun(void);
static void App_init_Fun(void);
static void App_enter_pass_Fun(void);
static void App_correct_pass_Fun(void);
static void App_wrong_pass_Fun(void);
static void App_start_operations_Fun(void);
static void App_operations_Fun(void);
static void App_stop_Fun(void);
/*******************************************************************************
 *                      Private Functions Definitions                          *
 *******************************************************************************/
static void App_LCD_Handler_mod(LCD_mode_t LCD_var)
{
	while(FALSE == LCD_Semaphore)
	{
		vTaskDelay(100);
	}
	LCD_Semaphore = FALSE;
	LCD_mode = LCD_var;
}
static void App_init_Fun(void)
{
	App_LCD_Handler_mod( LCD_setcmd_mode);
	LCD_setcmd = _LCD_CLEAR;


	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="Enter your Pass ";


	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row2;


	app_state =app_enter_pass_state;
}
static void App_enter_pass_Fun(void)
{
	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row3;

	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="          ";

	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row3;

	keypad_mode = keypad_GetValue_mode;

	App_LCD_Handler_mod(LCD_displayNum_mode);
	LCD_displayNum = keypad_Result;
	keypad_mode = keypad_GetValue_mode;
	if(keypad_Result == 12358)
	{
		app_state =app_correct_pass_state;
	}
	else
	{
		if((Keypad_state!=check_Value) & (Keypad_state <3))
			app_state =app_wrong_pass_state;
		else if(Keypad_state >= 3)
		{
			app_state =app_stop_state;
		}
	}
}
static void App_correct_pass_Fun(void)
{
	App_LCD_Handler_mod( LCD_setcmd_mode);
	LCD_setcmd = _LCD_CLEAR;


	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="Your Password is correct  ";

	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row3;

	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="You are Welcome ";
	app_state = 4;
}
static void App_wrong_pass_Fun(void)
{
	App_LCD_Handler_mod( LCD_setcmd_mode);
	LCD_setcmd = _LCD_CLEAR;

	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row1;

	App_LCD_Handler_mod(LCD_displayNum_mode);
	LCD_displayNum = keypad_Result;

	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row2;

	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="renter your pass- ";

	App_LCD_Handler_mod(LCD_displayNum_mode);
	LCD_displayNum = Keypad_state;

	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row3;

	app_state =app_enter_pass_state;
	check_Value++;
}
static void App_start_operations_Fun(void)
{
	led_init();
	ADC_Initialize();
	ADC_StartConversion(ADC_Channel_1);

	App_LCD_Handler_mod( LCD_setcmd_mode);
	LCD_setcmd = _LCD_CLEAR;

	App_LCD_Handler_mod( LCD_displayStr_mode);
	LCD_displayStr ="Welcome";

	app_state =app_operations_state;
}
static void App_operations_Fun(void)
{
	App_LCD_Handler_mod( LCD_GoTo_mode);
	LCD_GoTo = GoTo_Row2;

	ADC_Value_1 =ADC_GetResult();
	ADC_Value_1 =((ADC_Value_1 * 5.0/1024) - 0.5) * 1000/10+50;
	App_LCD_Handler_mod(LCD_displayNum_mode);
	LCD_displayNum =ADC_Value_1;

	if(ADC_Value_1 >= 100)
	{
		led_on(LED_YELLOW);
	}
	else
	{
		led_off(LED_YELLOW);
	}
}
static void App_stop_Fun(void)
{
	static u8 app_stop_state_flag = 0;
	if(app_stop_state_flag == 0)
	{
		App_LCD_Handler_mod( LCD_setcmd_mode);
		LCD_setcmd = _LCD_CLEAR;

		App_LCD_Handler_mod( LCD_GoTo_mode);
		LCD_GoTo = GoTo_Row1;

		App_LCD_Handler_mod( LCD_displayStr_mode);
		LCD_displayStr ="Your enter wrong password ";

		App_LCD_Handler_mod( LCD_GoTo_mode);
		LCD_GoTo = GoTo_Row3;

		App_LCD_Handler_mod( LCD_displayStr_mode);
		LCD_displayStr ="wait 5 minutes:  ";

	}
	app_stop_state_flag++;
	App_LCD_Handler_mod(LCD_displayNum_mode);
	LCD_displayNum = app_stop_state_flag;
	vTaskDelay(100);
	if(app_stop_state_flag == 5)
	{
		app_state = app_init_state;
		app_stop_state_flag =0;
		Keypad_state = 0;
		check_Value =0;
	}

}

/*******************************************************************************
 *                      Global Functions Definitions                           *
 *******************************************************************************/
void APP_Task(void * pvparam)
{
	portTickType Freq = 90;
	portTickType Start = xTaskGetTickCount();
	while(1)
	{
		switch(app_state)
		{
		case app_init_state:
		{
			App_init_Fun();
		}
		break;
		case app_enter_pass_state:
		{
			App_enter_pass_Fun();
		}
		break;
		case app_correct_pass_state:
		{
			App_correct_pass_Fun();
		}
		break;
		case app_wrong_pass_state:
		{
			App_wrong_pass_Fun();
		}
		break;
		case app_start_operations_state :
		{
			App_start_operations_Fun();
		}
		break;
		case app_operations_state :
		{
			App_operations_Fun();
		}
		break;
		case app_stop_state:
		{
			App_stop_Fun();
		}
		break;
		}
		vTaskDelayUntil(&Start,Freq);
	}
}
/*******************************************************************************
 *                      End of File: App1_Task.c                                        *
 *******************************************************************************/

