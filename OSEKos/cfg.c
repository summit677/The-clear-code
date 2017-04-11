/****************本文件是自动生成的,请勿修改 !****************************/




/************************* 引用部分 ***********************************/

#include "osprop.h"
#include "osapi.h"
#include "cfg.h"
/************************* 声明部分 ***********************************/
#define TASK_STACK_SIZE		120 		//栈大小定义
#define	MESSAGE_BUF_SIZE	30			//消息缓冲大小定义

OSBYTE	taskStack[CONFIG_OSEK_TASK_NUMBER][TASK_STACK_SIZE]; //任务堆栈定义
OSBYTE	messageBuf[OCC_NMSGS][MESSAGE_BUF_SIZE];			 //消息缓冲定义
OSBYTE	messageQueue[OCC_NMSGS][MESSAGE_BUF_SIZE];			 //消息队列定义


/************************* 定义部分 ***********************************/
#ifndef Ir_RealTimInt

ISR(Ir_RealTimInt)
{
	 CounterTrigger(SysCounter);
}
#endif
#pragma CODE_SEG DEFAULT

StatusType MessageInit()
{

}

/* 中断对象定义 */
//中断类型配置列表
OSBYTE	osekConfig_InterruptTypeTable[OCC_ISRLEVELNUM] = 
{
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
};

//中断入口函数配置列表
T_OSEK_TASK_Entry	osekConfig_InterruptEntryTable[OCC_ISRLEVELNUM] = 
{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		(T_OSEK_TASK_Entry)Ir_RealTimInt,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
};



/* 任务对象定义 */
//扩展任务栈空间定义

const		T_OSEK_TASK_ConfigTable_Struct		osekConfig_TaskTable[OCC_NTSKS]=	
{
	{
		(T_OSEK_TASK_Entry)FuncTaskError,  TaskError,
		0 | OSEK_TASK_ACTIVE | OSEK_TASK_EXTENDED | OSEK_TASK_NONPREEMPT,
		&taskStack[TaskError][TASK_STACK_SIZE-1], //?????
		&taskStack[TaskError][0]				  //?????
	},			/*TaskError	*/
	{
		(T_OSEK_TASK_Entry)FuncTask1,  Task1,
		0 | OSEK_TASK_ACTIVE | OSEK_TASK_EXTENDED | OSEK_TASK_NONPREEMPT,
		&taskStack[Task1][TASK_STACK_SIZE-1], //?????
		&taskStack[Task1][0]				  //?????
	},			/*Task1	*/
	{
		(T_OSEK_TASK_Entry)FuncTask2,  Task2,
		0 | OSEK_TASK_ACTIVE | OSEK_TASK_EXTENDED | OSEK_TASK_NONPREEMPT,
		&taskStack[Task2][TASK_STACK_SIZE-1], //?????
		&taskStack[Task2][0]				  //?????
	},			/*Task2	*/
	{
		(T_OSEK_TASK_Entry)FuncTask3,  Task3,
		0 | OSEK_TASK_ACTIVE | OSEK_TASK_EXTENDED | OSEK_TASK_NONPREEMPT,
		&taskStack[Task3][TASK_STACK_SIZE-1], //?????
		&taskStack[Task3][0]				  //?????
	},			/*Task3	*/
	{
		0, OSEK_TASK_IDLE_ID,
		OSEK_TASK_ACTIVE,
	},			/* NULLTASK */
};


/* 计数器对象定义 */

//定义系统滴答时钟的数值
//#define OS_TMR_CFG_TICKS_PER_SEC 100    

//COUNTER对象配置表
T_OSEK_COUNTER_ConfigTable osekConfig_CounterTable[OCC_NCTRS] = 
{
	{
		32767,	// 允许计数器的最大值
		1,
		1
	},
};



/* 报警对象定义 */
//ALARM对象配置表
T_OSEK_ALARM_ConfigTable osekConfig_AlarmTable[OCC_NALMS] = 
{
	{
		Task1,
#if (defined(OCC_ECC1) || defined(OCC_ECC2)) && defined(OCC_ALMSETEVENT)
		0,
#endif
		SysCounter,
	},
};




/* 消息对象定义 */
#if defined (OCC_LOCALMESSAGESONLY)

//消息对象名定义
string		osekMsg_Msg1Object;
uint8		osekMsg_Msg4Object;


//消息配置表
const	T_OSEK_MESSAGE_ConfigTable	osekConfig_MsgTable[OCC_NMSGS]=
{
	{
		0,
		&osekMsg_Msg1Object,
		sizeof(string),
		#if defined(OCC_SIGACTIVTASK) || defined(OCC_SIGEVENT)
		Task1,
		#endif
		#if defined(OCC_SIGEVENT)
		0,
		#endif
		#if defined(OCC_SIGCALLBACK)
		0,
		#endif
		#if defined(OCC_SIGFLAG)
		OSEK_COM_NO_FLAG,
		#endif
		#if OCC_NQUEMSGS > 0
		0,
		0,
		#endif
	},
	{
		1,
		&osekMsg_Msg4Object,
		sizeof(uint8),
		#if defined(OCC_SIGACTIVTASK) || defined(OCC_SIGEVENT)
		Task2,
		#endif
		#if defined(OCC_SIGEVENT)
		0,
		#endif
		#if defined(OCC_SIGCALLBACK)
		0,
		#endif
		#if defined(OCC_SIGFLAG)
		OSEK_COM_NO_FLAG,
		#endif
		#if OCC_NQUEMSGS > 0
		0,
		0,
		#endif
	},
};

//消息对象拷贝的定义

#endif  /* OCC_LOCALMESSAGESONLY */


