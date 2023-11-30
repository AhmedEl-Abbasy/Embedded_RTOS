/******************************************************************************
 * Module:
 *
 * File Name: keypad.h
 *
 * Created on: Nov 30, 2023
 *
 * Description: Header file for keypad driver in operating systems
 *
 * Author: Ahmed El-Abbasy
 *******************************************************************************/
#ifndef KEYPAD_H
#define KEYPAD_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#ifndef F_CPU
#define F_CPU	16000000UL

#endif
//#include <util/delay.h>

#include "dio.h"
#include "std_types.h"
#include "keypad_cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void keypad_vidInit(void);
u8 keypad_u8GetKey(void);

u32 Result_FromKeypad(u8 keypad_Value_0);
 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: keypad.h
 *********************************************************************************************************************/