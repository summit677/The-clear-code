/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekTask.h,v $
 * Revision 1.0  2008/03/05 9:12:00
 * �����ļ�
*/

/**
 * @file 	osekTask.h
 * @brief
 *	<li> ���ܣ�����������ص����ݽṹ���꣬�Լ�������ص������� </li>
 * @author
 * @date 	2008-03-05
 * <p>���ţ�
 */

/**
 * \defgroup  Task ����
 * �������ģ��,��Ҫʵ������Ĺ���
 */
/**@{*/
/** @name �������ģ��*/
//@{


#ifndef _OSEK_TASK_H
#define _OSEK_TASK_H

#include "osapi.h"
/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

//  ��������ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    ActivateTask������ָ��������
 * @param[in]	taskId�������ID�š�
 * @returns		E_OK���ɹ�����
 * @returns    	E_OS_LIMIT������״̬���Ի��߳�������󼤻����
 * @returns     [E_OS_ID����Ч������ID]
 */
StatusType ActivateTask( TaskType taskId );

/**
 * @brief
 *    TerminateTask��������ǰ����, ��ȷ������ǲ��᷵�صġ�
 * @param[in]	��
 * @returns		[E_OS_RESOURCE��������Դû���ͷţ�]
 * @returns		[E_OS_CALLEVEL�����ж��е����˸ù��ܡ�]
 *
 */
StatusType TerminateTask( void );

/**
 * @brief
 *    ChainTask��������ǰ�����Ҽ���ָ��������
 * @param[in]	taskId����Ҫ���������ID��
 * @returns		E_OS_LIMIT����Ҫ���������״̬���ԣ����߳�������󼤻������
 * @returns     [E_OS_RESOURCE��������Դû���ͷţ�]
 * @returns		[E_OS_CALLEVEL�����ж��е��ô˺�����]
 * @returns		[E_OS_ID����Ҫ���������ID�Ų��Ϸ���]
 *
 */
StatusType ChainTask( TaskType taskId );

/**
 * @brief
 *    Schedule���ص��ȣ���Ҫ����������������CPU�������������ȼ��������С�
 * @param[in]	�ޡ�
 * @returns		E_OK���ɹ���
 * @returns     [E_OS_RESOURCE: ������Դ��������������Դ���ж���Դ��û���ͷţ�]
 * @returns     [E_OS_CALLEVEL: ���ж��е��õĴ˺�����]
 *
 */
StatusType Schedule( void );

/**
 * @brief
 *    GetTaskID����ȡ��ǰ�����ID�š�
 * @param[in]	taskId����������ID�ı���������
 * @returns		E_OK: �ɹ���ȡ������״̬��
 *
 */
StatusType GetTaskID( TaskRefType taskId );

/**
 * @brief
 *    GetTaskState����ȡָ�������״̬��״̬����RUNNING��WAITING��READY��SUSPENDED�ȡ�
 * @param[in]	taskId������ID�ţ�
 * @param[in]	state������״̬���������ã����ڱ������������״̬��
 * @returns 	E_OK: �ɹ���ȡ������״̬��
 * @returns     [E_OS_ID������ID����Ч��]
 *
 */
StatusType GetTaskState ( TaskType taskId, TaskStateRefType state );

// �ڲ�����
void osekTask_Dispatch( void );
void osekTask_TerminateDispatch( void );
void osekTask_WaitTask( void );
void osekTask_ChangeRunningTaskPriority( OSPRIOTYPE newPri );
void osekTask_Initialize( void );


/**************************** ���岿�� *********************************/

#define OSEK_TASK_CallTaskEntry()  (*(osekTask_RunningTask->taskControlBlock->configTable.entry))()

#define OSEK_TASK_INVALID_ID CONFIG_OSEK_TASK_NUMBER	// ��Ч������ID
#define OSEK_TASK_ID2PRI(id) (CONFIG_OSEK_TASK_PRIORITY_NUMBER - (id) - 1)	// ������IDת��Ϊ���ȼ��ĺ꣬��ϵͳΪBCC1��ECC1ʱ��Ҫ����������������ȼ�


/// �������ԣ���ϵͳ����ʱ��������
#define OSEK_TASK_ACTIVE     ( (OSBYTE)0x08 )
/// �������ԣ�����ռ����
#define OSEK_TASK_NONPREEMPT ( (OSBYTE)0x40 )
/// �������ԣ���չ����
#define OSEK_TASK_EXTENDED   ( (OSBYTE)0x80 )


/// ����״̬������״̬
#define RUNNING              ((TaskStateType)0)
/// ����״̬���ȴ�״̬
#define WAITING              ((TaskStateType)1)
/// ����״̬������״̬
#define READY                ((TaskStateType)2)
/// ����״̬������״̬
#define SUSPENDED            ((TaskStateType)3)

#define OSEK_TASK_FIRST_RUN ((TaskStateType)4)      // �����һ������

#define OSEK_TASK_STATE_MASK (((TaskStateType)3))   // ����״̬����

#define OSEK_TASK_GETTOPOFSTACK(addr, size)  ((addr) + ((size)-0x20))	// ��ȡջ��λ��

#define OSEK_TASK_NEED_DISPATCH      ((StatusType)0xFF)	// ��Ҫִ�е���


/// ��������ýṹ
typedef struct T_OSEK_TASK_ConfigTable_Struct
{

	/// �������
	T_OSEK_TASK_Entry entry;
	/// �����ID(0-255)����BCC1��ECC1ʱ��ϵͳ���֧��64�����񣬲�����������ȼ���ID�����
	TaskType taskId;

// Ӧ��ģʽ����1����ʾϵͳ���ж��ģʽ
#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
	/// �Ƿ�Ҫϵͳ�Զ���������ÿ��λ��ʾһ��ģʽ�������Ҫ�ڸ�ģʽ���������򽫸ñ����Ķ�Ӧλ��λ����������Ӧ��ģʽ����1ʱ����Ч��
	OSDWORD autoStart;
#endif

	/// ������������ԣ��Ƿ�����ʱ���������Ƿ�����չ�����Ƿ��Ƿ���ռ����
	OSBYTE property;

// ��չ�����ջ����
#if defined(CONFIG_OSEK_SYSTEM_ET)
	/// ��չ�����ջ��������������չ����ʱ�����ԲŴ��ڣ�
	OSBYTEPTR stackTop;
	/// ��չ�����ջ�ף�����������չ����ʱ�����ԲŴ��ڣ�
	OSBYTEPTR stackBottom;
#endif

// ��ʹ���ڲ���Դʱ
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
	/// ʹ���ڲ���Դʱ��������ȼ������������ڲ���Դʱ�����ԲŴ��ڣ�
	OSPRIOTYPE inresPriority;
#endif

// ����һ�����ȼ����ж������ʱ
#if defined(CONFIG_OSEK_SYSTEM_EP)
	/// ��������ȼ�������һ�����ȼ����ж������ʱ�����ԲŴ��ڣ�
	OSPRIOTYPE basePriority;
	/// �����������󼤻����������һ�����ȼ����ж������ʱ�����ԲŴ��ڣ�
	OSBYTE maxActive;
#endif

}T_OSEK_TASK_ConfigTable_Struct;


/// ����Ŀ��ƽṹ
typedef struct T_OSEK_TASK_ControlBlock_Struct
{

	/// ����״̬��Ϣ������0-1λ��ʾ����״̬��0�����У�1���ȴ���2��������3�����𣩣�λ2��ʾ�����ǵ�һ������
	TaskStateType status;

// ����һ�����ȼ����ж������ʱ
#if defined(CONFIG_OSEK_SYSTEM_EP)
	/// ����ĵ�ǰ�������������һ�����ȼ����ж������ʱ�����ԲŴ��ڣ�
	OSBYTE curActiveNum;
#endif

	/// ����ĵ�ǰ���ȼ���
	OSPRIOTYPE curPriority;
    /// ��������ñ�
    T_OSEK_TASK_ConfigTable configTable;

// ��ʹ����չ����ʱ
#if defined(CONFIG_OSEK_SYSTEM_ET)
	/// ����Ҫ�ȴ����¼������32���¼�������������չ����ʱ�����ԲŴ��ڣ�
	EventMaskType waitEvent;
	/// �������õ��¼������32���¼�������������չ����ʱ�����ԲŴ��ڣ�
	EventMaskType setEvent;
#endif

	/// ���������ģ����ϵͳ��ֻ�л���������û�����������ĵ�
	T_OSEK_TARGET_TaskContext      *context;

// ��ʹ������Դ
#if defined(CONFIG_OSEK_RESOURCE)
	/// ����ʹ�õ���Դ����������������Դʱ�����ԲŴ��ڣ�
	ResourceType resourceList;
#endif

}T_OSEK_TASK_ControlBlock_Struct;

// �����ھ����������Ŷӵľ�����ṹ
typedef struct T_OSEK_TASK_ReadyBlock_Struct
{
	struct T_OSEK_TASK_ReadyBlock_Struct   *nextTask;			// ��һ������������ڵ�
	T_OSEK_TASK_ControlBlock_Struct *taskControlBlock; // ָ���Ӧ������ƿ��ָ��
}T_OSEK_TASK_ReadyBlock_Struct;

// ����������б�ṹ
typedef struct
{

	T_OSEK_TASK_ReadyBlock_Struct *readyTaskHead; // ����������е�ͷָ��
	T_OSEK_TASK_ReadyBlock_Struct *readyTaskTail; // ����������е�βָ��

}T_OSEK_TASK_ReadyTaskTableItem;


// ���������������
extern T_OSEK_TASK_ReadyTaskTableItem osekTask_ReadyTaskTable[];

// ������ƿ������
extern T_OSEK_TASK_ControlBlock_Struct osekTask_TaskTable[];

/// ����������Ϣ������
extern const T_OSEK_TASK_ConfigTable_Struct osekConfig_TaskTable[];

// ��ǰ��������ָ������
extern T_OSEK_TASK_ReadyBlock_Struct *osekTask_RunningTask;

// ��������������
extern T_OSEK_TASK_ReadyBlock_Struct osekTask_ReadyBlock[];
// ϵͳ���о�����������
extern T_OSEK_TASK_ReadyBlock_Struct *osekTask_FreeReadyBlock;

// �жϷ�������е��Ա�־
extern OSDWORD osekTask_IsrTriggeredTaskSwitchNecessary;


// ���ȼ�λͼ
// Ӳ��ʵ�ֵ����ȼ�λͼ
#if defined(CONFIG_OSEK_TARGET_HARDBITMAP)
extern OSDWORD osekTask_PriorityBitMap1;

// Ӳ��֧����չ���ȼ�
#if defined(CONFIG_OSEK_TASK_EXTPRIORS)
extern OSDWORD osekTask_PriorityBitMap2;

// �������ȼ�λͼ��ָ�����ȼ��ľ�����־
#define OSEK_TASK_SetPriorityBitMap(pri)  \
( (pri < 32) ? \
(osekTask_PriorityBitMap1 |= ( ((OSDWORD)0x00000001)<< (pri) )) :  \
(osekTask_PriorityBitMap2 |= ( ((OSDWORD)0x00000001)<< ((pri)-32) )) )

// ������ȼ�λͼ��ָ�����ȼ��ľ�����־
#define OSEK_TASK_ClearPriorityMap(pri) \
{ \
	if( osekTask_ReadyTaskTable[(pri)].readyTaskHead == NULLPTR ) \
	{ \
		 (pri < 32) ? \
		(osekTask_PriorityBitMap1 &= ~( ((OSDWORD)0x00000001)<< (pri) )) :  \
		(osekTask_PriorityBitMap2 &= ~( ((OSDWORD)0x00000001)<< ((pri)-32) )); \
	} \
}

// ��ȡ������ȼ�
#if defined(CONFIG_OSEK_TARGET_PPC)
static inline  OSDWORD GetHighestPriority( OSDWORD scheduler_vector1, OSDWORD scheduler_vector2 )
{
    OSDWORD result;
    asm volatile("cntlzw %0,%1":"=r"((result)):"r"((scheduler_vector2)));

    if( result < 32 )
    {
    	result =  63 - result;
    }
    else
    {
    	asm volatile("cntlzw %0,%1":"=r"((result)):"r"((scheduler_vector1)));
    	result = 31 - result;

    }

    return result;
}
#endif


#define OSEK_TASK_GetHighestPriority() GetHighestPriority( osekTask_PriorityBitMap1, osekTask_PriorityBitMap2 )


// Ӳ����֧����չ���ȼ�
#else /* #if defined(CONFIG_OSEK_TASK_EXTPRIORS) */

// �������ȼ�λͼ��ָ�����ȼ��ľ�����־
#define OSEK_TASK_SetPriorityBitMap(pri) osekTask_PriorityBitMap1 |= ( ((OSDWORD)0x00000001)<< (pri) )

// ������ȼ�λͼ��ָ�����ȼ��ľ�����־
#define OSEK_TASK_ClearPriorityMap(pri)  \
{ \
	if( osekTask_ReadyTaskTable[(pri)].readyTaskHead == NULLPTR ) \
	{ \
		osekTask_PriorityBitMap1 &= ~( ((OSDWORD)0x00000001)<< (pri) ); \
	} \
}

// ��ȡ������ȼ�
#if defined(CONFIG_OSEK_TARGET_PPC)
static inline OSDWORD GetHighestPriority( OSDWORD scheduler_vector )
{
    OSDWORD result;
    asm volatile("cntlzw %0,%1":"=r"((result)):"r"((scheduler_vector)));
    return ( 31 - result);
}
#endif


#define OSEK_TASK_GetHighestPriority() GetHighestPriority(osekTask_PriorityBitMap1)

#endif /* else defined(CONFIG_OSEK_TASK_EXTPRIORS) */

#endif /* #if defined(CONFIG_OSEK_TARGET_HARDBITMAP)  */


// ������������������
extern OSDWORD osekTask_SchedulerLockLevel;


// ���ʵ�ֵ����ȼ�λͼ
#if defined(CONFIG_OSEK_TARGET_SOFTBITMAP)
// ���ȼ�λͼ����
extern OSBYTE osekTask_PriorityBitMap[( (OSBYTE) (CONFIG_OSEK_TASK_PRIORITY_NUMBER) ) >> 3];
// �����ȼ�λͼ����
extern OSBYTE osekTask_PriorityBitMapMajor;
// ���ȼ�������
extern OSBYTE osekTask_PriorityIndexTable[256];

// �������ȼ�λͼ��ָ�����ȼ��ľ�����־
#define OSEK_TASK_SetPriorityBitMap(pri)  do {  \
	osekTask_PriorityBitMap[(pri)>>3] |= (1<<((pri)&7)) ; \
	osekTask_PriorityBitMapMajor |= (1 << ((pri)>>3)); \
}while(0)


// ������ȼ�λͼ��ָ�����ȼ��ľ�����־
#pragma INLINE
static  void ClearPriorityMap( OSPRIOTYPE pri)
{
	if( osekTask_ReadyTaskTable[(pri)].readyTaskHead == NULLPTR )
	{
		OSPRIOTYPE index = ((pri)>>3) ;
		osekTask_PriorityBitMap[index] &= (~(1<<((pri)&7))) ;
		if( osekTask_PriorityBitMap[index] == 0 )
		{
			osekTask_PriorityBitMapMajor &= (~(1 << index)) ;
		}
	}
}

#define OSEK_TASK_ClearPriorityMap(pri)  (ClearPriorityMap(pri))


// ��ȡ������ȼ�
#define OSEK_TASK_GetHighestPriority() \
	((osekTask_PriorityIndexTable[osekTask_PriorityBitMapMajor] << 3 )| \
	(osekTask_PriorityIndexTable[osekTask_PriorityBitMap[osekTask_PriorityIndexTable[osekTask_PriorityBitMapMajor]]]))


#endif /* #if defined(CONFIG_OSEK_TARGET_SOFTBITMAP) */


// ��ָ���������������β��
#pragma INLINE
static  void AddTask2ReadyTableAtTail( T_OSEK_TASK_ReadyBlock *readyblockptr)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	// ������ҵ�����β��ʱ��������ԭʼ���ȼ�����������е�
#if defined(CONFIG_OSEK_SYSTEM_EP)
	chain = &osekTask_ReadyTaskTable[readyblockptr->taskControlBlock->configTable.basePriority];
#else
	chain = &osekTask_ReadyTaskTable[OSEK_TASK_ID2PRI(readyblockptr->taskControlBlock->configTable.taskId)];
#endif

	(readyblockptr)->nextTask = NULLPTR ;
	if( chain->readyTaskHead == NULLPTR )
	{
		chain->readyTaskHead = (readyblockptr);
	}
	else
	{
		chain->readyTaskTail->nextTask = (readyblockptr);
	}
	chain->readyTaskTail = (readyblockptr);

}

#define OSEK_TASK_AddTask2ReadyTableAtTail(readyblockptr)  (AddTask2ReadyTableAtTail(readyblockptr))



// ��ָ���������������ͷ��
static  void AddTask2ReadyTableAtHead( T_OSEK_TASK_ReadyBlock *readyblockptr)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	// ������ҵ�����ͷ��ʱ���Ե�ǰ���ȼ�����
	chain = &osekTask_ReadyTaskTable[readyblockptr->taskControlBlock->curPriority];
	(readyblockptr)->nextTask = chain->readyTaskHead ;
	if( chain->readyTaskTail == NULLPTR )
	{
		chain->readyTaskTail = (readyblockptr);
	}
	chain->readyTaskHead = (readyblockptr);

}

#define OSEK_TASK_AddTask2ReadyTableAtHead(readyblockptr)  (AddTask2ReadyTableAtHead(readyblockptr))

// �ھ��������м���һ���µľ�����
static  StatusType AddaReadyBlock( T_OSEK_TASK_ControlBlock *tcbPtr )
{
	T_OSEK_TASK_ReadyBlock *readyBlock;

	if(osekTask_FreeReadyBlock!=NULLPTR)
	{
		readyBlock = osekTask_FreeReadyBlock;
		osekTask_FreeReadyBlock = osekTask_FreeReadyBlock->nextTask;

		readyBlock->taskControlBlock = tcbPtr;

		// �������¾���ʱ��������ԭʼ���ȼ�����������е�
#if defined(CONFIG_OSEK_SYSTEM_EP)
		OSEK_TASK_SetPriorityBitMap(tcbPtr->configTable.basePriority);
#else
		OSEK_TASK_SetPriorityBitMap(OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId));
#endif
		OSEK_TASK_AddTask2ReadyTableAtTail(readyBlock);

		return E_OK;
	}
	else
	{
		return E_OS_LIMIT;//���ǵ������񼤻������꣬����ϵͳû�п���readyBlock�ˡ�ͨ�����ù��߱�֤�����������������Ӧ���֡�
	}

}

#define OSEK_TASK_AddaReadyBlock(tcbPtr)  (AddaReadyBlock(tcbPtr))

// �ͷ�һ��������ؿ�����
static  void ReleaseReadyBlock( T_OSEK_TASK_ReadyBlock *readyBlock )
{

	readyBlock->nextTask = osekTask_FreeReadyBlock;
	osekTask_FreeReadyBlock = readyBlock;

}

#define OSEK_TASK_ReleaseReadyBlock(readyBlock)  (ReleaseReadyBlock(readyBlock))

// �Ӿ��������Ƴ�ָ�����ȼ���һ������
static  void MoveTaskFromReadyTable(OSPRIOTYPE pri)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	chain = &osekTask_ReadyTaskTable[(pri)];
	chain->readyTaskHead = chain->readyTaskHead->nextTask;  // �ٶ��������ѱ�֤��chain->readyTaskHead����Ч��
	if(chain->readyTaskHead == NULLPTR )
	{
		chain->readyTaskTail = NULLPTR;
	}
}
#pragma NO_INLINE
#define OSEK_TASK_MoveTaskFromReadyTable(pri)  (MoveTaskFromReadyTable(pri))

// ��ȡָ�����ȼ��ϵĵ�һ����������
#define OSEK_TASK_GetReadyTask(pri) (osekTask_ReadyTaskTable[(pri)].readyTaskHead)


// �ڲ���������������ƿ�ָ����Ϊ���������
StatusType osekTask_ActiveTask(T_OSEK_TASK_ControlBlock *tcbPtr);
StatusType osekTask_WakeTask(T_OSEK_TASK_ControlBlock *tcbPtr);

#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
