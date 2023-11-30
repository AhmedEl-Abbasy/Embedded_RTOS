/******************************************************************************
 * Module:
 *
 * File Name: Smart_Home.h
 *
 * Created on: Nov 30, 2023
 *
 * Description: Header File for the Smart Home project
 *
 * Author: Ahmed El-Abbasy
 *******************************************************************************/
#ifndef APPLICATIONS_SMART_HOME_H_
#define APPLICATIONS_SMART_HOME_H_

/*******************************************************************************
 *                      Includes                                               *
 *******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include "led.h"

/*******************************************************************************
 *                      Global Constant Macros                                 *
 *******************************************************************************/
#define  LCD_Task_pr 			3
#define Keypad_Task_pr			2
#define APP_Task_pr 			1
/*******************************************************************************
 *                      Global Constant Macros                                 *
 *******************************************************************************/


/*******************************************************************************
 *                      Global Function Macros                                 *
 *******************************************************************************/


/*******************************************************************************
 *                      Global Data Types and Structures                       *
 *******************************************************************************/
typedef enum {
	LCD_init_mode,
	LCD_IDE_mode,
	LCD_displayChar_mode,
	LCD_displayStr_mode,
	LCD_displayNum_mode,
	LCD_setcmd_mode,
	LCD_GoTo_mode
}LCD_mode_t;

typedef enum {
	GoTo_Row1,
	GoTo_Row2,
	GoTo_Row3,
	GoTo_Row4
}LCD_GoTo_t;

typedef enum{
	keypad_init_mode,
	keypad_GetValue_mode,
	keypad_IDE_mode
}keypad_mode_t;

typedef enum {
	app_init_state,
	app_enter_pass_state,
	app_correct_pass_state,
	app_wrong_pass_state,
	app_start_operations_state,
	app_operations_state,
	app_stop_state

}app_state_t;
/*******************************************************************************
 *                      Global Data Prototypes                                 *
 *******************************************************************************/
extern LCD_mode_t LCD_mode;
extern u8 LCD_displayChar;
extern char* LCD_displayStr;
extern u32 LCD_displayNum;
extern u8 LCD_setcmd	;
extern LCD_GoTo_t LCD_GoTo ;
extern boolean LCD_Semaphore ;

extern keypad_mode_t keypad_mode;
extern u32 keypad_Result;
extern u8 Keypad_state;


/*******************************************************************************
 *                      Global Function Prototypes                             *
 *******************************************************************************/

void LCD_Task(void * pvparam);
void Keypad_Task(void * pvparam);
void APP_Task(void * pvparam);

/*******************************************************************************
 *                      End of File: Smart_Home.h                                       *
 *******************************************************************************/

#endif /* APPLICATIONS_SMART_HOME_H_ */
