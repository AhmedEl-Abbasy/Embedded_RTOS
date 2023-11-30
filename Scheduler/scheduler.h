/******************************************************************************
 * Module:
 *
 * File Name: scheduler.h
 *
 * Created on: Nov 24, 2023
 *
 * Description: Header File for the Scheduler
 *
 * Author: Ahmed El-Abbasy
 *******************************************************************************/
#ifndef APP_SCHEDULERF_SCHEDULER_H_
#define APP_SCHEDULERF_SCHEDULER_H_
/*******************************************************************************
 *                      Includes                                               *
 *******************************************************************************/
#include "timer0.h"


/*******************************************************************************
 *                      Global Constant Macros                                 *
 *******************************************************************************/


/*******************************************************************************
 *                      Global Function Macros                                 *
 *******************************************************************************/

/*******************************************************************************
 *                      Global Data Types and Structures                       *
 *******************************************************************************/

typedef enum{
	wait,
	ready,
	running
}statetask_t;

typedef struct{
	void(*task)(void);
	u16 periodicity_t;
	u8 first_delay;
	statetask_t statetask;
	u8 periority;
}task_t;

/*******************************************************************************
 *                      Global Data Prototypes                                 *
 *******************************************************************************/

/*******************************************************************************
 *                      Global Function Prototypes                             *
 *******************************************************************************/

void sch_init();
void sch_createTask(u8 First_Delay,u8 periority_task,u16 numper, void (*fPtr)(void));
void sch_8start();
void sch_Handler();
void sch_suspend_task(void (*fPtr)(void));
void sch_resume_task(void (*fPtr)(void));
void sch_delete_task(void (*fPtr)(void));

void detect_time(void);


#endif /* APP_SCHEDULERF_SCHEDULER_H_ */
/*******************************************************************************
 *                      End of File: scheduler.h                                        *
 *******************************************************************************/
