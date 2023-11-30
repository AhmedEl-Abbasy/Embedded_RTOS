/*******************************************************************************
 *  FILE DESCRIPTION
 *  ----------------------------------------------------------------------------
 * Module:
 *
 * File Name: keypad.c
 *
 * Created on:  Nov 30, 2023
 *
 * Description: Source file for keypad driver in operating systems
 *
 * Author: Ahmed El-Abbasy
 *
 *******************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "keypad.h"



/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 keys_value[4][4]=
{
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'F','0','E','D'}
};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void keypad_vidInit(void)        
* \Description     : keypad HW initialization                                
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                                                                         
* \Return value:   : None                               
*******************************************************************************/
void keypad_vidInit(void)
{
	/*	ROW channel direction -> output	*/
	dio_vidConfigChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,OUTPUT);
	dio_vidConfigChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,OUTPUT);
	dio_vidConfigChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,OUTPUT);
	dio_vidConfigChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,OUTPUT);
	
	/*	COLUMN channel direction -> input	*/
	dio_vidConfigChannel(KEYPAD_COL1_PORT,KEYPAD_COL1_CHANNEL,INPUT);
	dio_vidConfigChannel(KEYPAD_COL2_PORT,KEYPAD_COL2_CHANNEL,INPUT);
	dio_vidConfigChannel(KEYPAD_COL3_PORT,KEYPAD_COL3_CHANNEL,INPUT);
	dio_vidConfigChannel(KEYPAD_COL4_PORT,KEYPAD_COL4_CHANNEL,INPUT);
	
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_LOW);
}


boolean keypad_bolIsPressed(void)
{
	if (
		!dio_dioLevelReadChannel(KEYPAD_COL1_PORT,KEYPAD_COL1_CHANNEL)||
		!dio_dioLevelReadChannel(KEYPAD_COL2_PORT,KEYPAD_COL2_CHANNEL)||
		!dio_dioLevelReadChannel(KEYPAD_COL3_PORT,KEYPAD_COL3_CHANNEL)||
		!dio_dioLevelReadChannel(KEYPAD_COL4_PORT,KEYPAD_COL4_CHANNEL)
		)
		{
		  return TRUE;
		}
		else
		{
		  return FALSE;
		}
}
u8 keypad_GetCol(void)
{
	u8 loc_col = 0;
	if (STD_LOW == dio_dioLevelReadChannel(KEYPAD_COL1_PORT,KEYPAD_COL1_CHANNEL))
	{
		loc_col = 1;
	}
	else if (STD_LOW == dio_dioLevelReadChannel(KEYPAD_COL2_PORT,KEYPAD_COL2_CHANNEL))
	{
	 loc_col = 2;
	}
	else if (STD_LOW == dio_dioLevelReadChannel(KEYPAD_COL3_PORT,KEYPAD_COL3_CHANNEL))
	{
	 loc_col = 3;
	}
	else if (STD_LOW == dio_dioLevelReadChannel(KEYPAD_COL4_PORT,KEYPAD_COL4_CHANNEL))
	{
	 loc_col = 4;
	}
	else
	{
		/*	do nothing	*/
	}
	return loc_col;
}

u8 keypad_GetRow(u8 col)
{
	u8 loc_row =0;
	
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_HIGH);
	if (keypad_GetCol() == col)
	{
		loc_row = 1;	
	}
	//_delay_ms(5);
	
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_HIGH);
	if (keypad_GetCol() == col)
	{
		loc_row = 2;	
	}
	//_delay_ms(5);
	
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_HIGH);
	if (keypad_GetCol() == col)
	{
		loc_row = 3;	
	}
	//_delay_ms(5);
	
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_HIGH);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_LOW);
	if (keypad_GetCol() == col)
	{
		loc_row = 4;	
	}
	//_delay_ms(5);
	dio_vidWriteChannel(KEYPAD_ROW1_PORT,KEYPAD_ROW1_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW2_PORT,KEYPAD_ROW2_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW3_PORT,KEYPAD_ROW3_CHANNEL,STD_LOW);
	dio_vidWriteChannel(KEYPAD_ROW4_PORT,KEYPAD_ROW4_CHANNEL,STD_LOW);
	return loc_row;
}
/*	it shall be called periodically	*/
u8 keypad_u8GetKey(void)
{
	u8 loc_row = 0;
	u8 loc_col = 0;
	u8 return_value = 0xFF;
	
	if (TRUE == keypad_bolIsPressed())
	{
		loc_col = keypad_GetCol();
		loc_row = keypad_GetRow(loc_col);
		vTaskDelay(50);	/*	press time in real time	*/
		//_delay_ms(20);	/*	press time for simulation	*/
		return_value = keys_value[loc_row-1][loc_col-1];
	}
	return return_value;
}


///**help Fun**/

u32 Result_FromKeypad(u8 keypad_Value_0)
{
	u8 number =0;
	static u32 Ret_Value_1 =0;
	u32 value_ret =0;
	if((keypad_Value_0 == '1')  ||(keypad_Value_0 == '2')||
			(keypad_Value_0 == '3') ||(keypad_Value_0 == '4')||
			(keypad_Value_0 == '5') ||(keypad_Value_0 == '6')||
			(keypad_Value_0 == '7') ||(keypad_Value_0 == '8')||
			(keypad_Value_0 == '9') ||(keypad_Value_0 == '0'))
	{

		number = keypad_Value_0 - 48;
		Ret_Value_1 = Ret_Value_1 * 10;
		Ret_Value_1 = Ret_Value_1 +number;
		number =0;
		value_ret = Ret_Value_1;
	}
	else if(keypad_Value_0 == '=')
	{
		value_ret = Ret_Value_1;
		Ret_Value_1 =0;

	}
	return value_ret ;
}


/**********************************************************************************************************************
 *  END OF FILE: keypad.c
 *********************************************************************************************************************/
