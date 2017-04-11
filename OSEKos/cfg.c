/****************���ļ����Զ����ɵ�,�����޸� !****************************/




/************************* ���ò��� ***********************************/

#include "osprop.h"
#include "osapi.h"
#include "cfg.h"
/************************* �������� ***********************************/
#define TASK_STACK_SIZE		120 		//ջ��С����
#define	MESSAGE_BUF_SIZE	30			//��Ϣ�����С����

OSBYTE	taskStack[CONFIG_OSEK_TASK_NUMBER][TASK_STACK_SIZE]; //�����ջ����
OSBYTE	messageBuf[OCC_NMSGS][MESSAGE_BUF_SIZE];			 //��Ϣ���嶨��
OSBYTE	messageQueue[OCC_NMSGS][MESSAGE_BUF_SIZE];			 //��Ϣ���ж���


/************************* ���岿�� ***********************************/
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

/* �ж϶����� */
//�ж����������б�
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

//�ж���ں��������б�
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



/* ��������� */
//��չ����ջ�ռ䶨��

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


/* ������������ */

//����ϵͳ�δ�ʱ�ӵ���ֵ
//#define OS_TMR_CFG_TICKS_PER_SEC 100    

//COUNTER�������ñ�
T_OSEK_COUNTER_ConfigTable osekConfig_CounterTable[OCC_NCTRS] = 
{
	{
		32767,	// ��������������ֵ
		1,
		1
	},
};



/* ���������� */
//ALARM�������ñ�
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




/* ��Ϣ������ */
#if defined (OCC_LOCALMESSAGESONLY)

//��Ϣ����������
string		osekMsg_Msg1Object;
uint8		osekMsg_Msg4Object;


//��Ϣ���ñ�
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

//��Ϣ���󿽱��Ķ���

#endif  /* OCC_LOCALMESSAGESONLY */


