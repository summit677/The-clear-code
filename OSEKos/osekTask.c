/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekTask.c,v $
 * Revision 1.0  2008/03/05 9:14:00
 * �����ļ���
 */

/*
 * @file 	osekTask.c
 * @brief
 *	<li>���ܣ�ʵ�����������ع��ܡ�</li>
 * @author
 * @date 	2008-03-05
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/
//#include "osekTarget.h"

#include "osprop.h"

#include "osapi.h"
#include <string.h>

/*************************** ǰ���������� ******************************/


/**************************** ���岿�� *********************************/

// ȫ�ֱ���

// ����������е�����ͷ�������飬һ�����ȼ���Ӧһ������ͷ��
T_OSEK_TASK_ReadyTaskTableItem osekTask_ReadyTaskTable[CONFIG_OSEK_TASK_PRIORITY_NUMBER];

// ������ƽṹ���飬ÿ������һ�����ƽṹ��
T_OSEK_TASK_ControlBlock osekTask_TaskTable[CONFIG_OSEK_TASK_NUMBER];

// ��ǰ��������ָ�룬����ָ�����ϵͳ�е�ǰ�������е�������ƽṹ��
T_OSEK_TASK_ReadyBlock *osekTask_RunningTask;

// ������������ʵ�ֶԵ�����������������ֵΪ����ʱ��ʾ����������������ʹ�и����ȼ��������Ҳ���ܹ���ռ��ǰ��������С�
OSDWORD osekTask_SchedulerLockLevel;

// �����ж�2�е��ò���ϵͳAPI��ɸ����ȼ�������������ҵ�ǰ���������ǿ���ռʱ���ñ�����λ��
OSDWORD osekTask_IsrTriggeredTaskSwitchNecessary;

// �����л�ʱ�������ı����������İ��������Ĵ��������ĺ͸���������
#pragma align on
static T_OSEK_TARGET_TaskContext osekTask_ContextTable[CONFIG_OSEK_TASK_NUMBER] ;
#pragma align off

// �����ھ����������Ŷӵľ�����
T_OSEK_TASK_ReadyBlock osekTask_ReadyBlock[CONFIG_OSEK_TASK_TOTAL_ACTIVATE_NUMBER];
// ���о���������ͷָ��
T_OSEK_TASK_ReadyBlock *osekTask_FreeReadyBlock;


#if defined(CONFIG_OSEK_TARGET_HARDBITMAP)
// ��Ӳ����ص����ȼ�λͼʵ��
// ���ȼ�λͼ�е�0-31���ȼ��ı���������ʺ���CPU֧�ַ���λ���ҹ��ܵ������
OSDWORD osekTask_PriorityBitMap1;

#if defined(CONFIG_OSEK_TASK_EXTPRIORS)
// ���ȼ�λͼ�е�32-63���ȼ��ı���
OSDWORD osekTask_PriorityBitMap2;
#endif /* #if defined(CONFIG_OSEK_TASK_EXTPRIORS) */

#endif /* #if defined(CONFIG_OSEK_TARGET_HARDBITMAP) */



#if defined(CONFIG_OSEK_TARGET_SOFTBITMAP)
// ��Ӳ���޹ص����ȼ�λͼʵ��
// ���ȼ�λͼ��8�����ȼ�һ�飬���8�顣
OSBYTE osekTask_PriorityBitMap[( (OSBYTE) (CONFIG_OSEK_TASK_PRIORITY_NUMBER) ) >> 3];

// ���ڱ�ʾĳ�����ȼ����Ƿ���λ��һ��λ��ʾһ���顣
OSBYTE osekTask_PriorityBitMapMajor;

// ���ȼ����������ڿ��ٶ�λ��ǰ��������ȼ�����ֵԽ�����ȼ�Խ�ߡ�
OSBYTE osekTask_PriorityIndexTable[256] = {
0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7

};

#endif /* #if defined(CONFIG_OSEK_TARGET_SOFTBITMAP) */


/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    osekTask_ChangeRunningTaskPriority: �ѵ�ǰ��������ȼ�����Ϊָ�������ȼ���
 *                                        ������������ȻҪ���ڶ�Ӧ���ȼ��������е���ͷ���ڲ���������
 * @param[in]	newPri���µ����ȼ�
 * @returns 	��
 *
 */
void osekTask_ChangeRunningTaskPriority( OSPRIOTYPE newPri )
{
	T_OSEK_TASK_ControlBlock *tcbPtr;
	tcbPtr = osekTask_RunningTask->taskControlBlock;

	// �Ƚ������ԭ�����ȼ��ľ����������Ƴ���Ȼ��������ȼ�λͼ�еĶ�Ӧλ
	OSEK_TASK_MoveTaskFromReadyTable(tcbPtr->curPriority);
	OSEK_TASK_ClearPriorityMap(tcbPtr->curPriority);

	tcbPtr->curPriority = newPri;

	// �Ƚ����ȼ�λͼ�������ȼ���Ӧλ��λ��Ȼ��������뵽�����ȼ��������е�ͷ��
	OSEK_TASK_SetPriorityBitMap(newPri);
	OSEK_TASK_AddTask2ReadyTableAtHead(osekTask_RunningTask);
}


/*
 * @brief
 *    osekTask_ActiveTask������ָ�������񣬴�Ϊ��API���������ڶ��Ѿ���ȷ��������Ч�Ժ�ļ���������ڲ���������
 *
 * @param[in]	tcbPtr����Ҫ�����������ƽṹ��ָ�롣
 * @returns 	E_OK: �ɹ����
 *              E_OS_LIMIT: ����״̬���ԣ����߳�������󼤻������
 *              OSEK_TASK_NEED_DISPATCH: �ɹ��������Ҫ���µ��ȡ�
 */
StatusType osekTask_ActiveTask(T_OSEK_TASK_ControlBlock *tcbPtr)
{

	// ���ڷ�SUSPEND״̬��������������μ�����Ҽ������С����󼤻������������µľ����鲢�Լ�����������ۼӺ󷵻�E_OK�����򷵻�E_OS_LIMIT��
	if( tcbPtr->status != SUSPENDED )
	{
#if defined(CONFIG_OSEK_SYSTEM_MACTIVE)
		if(tcbPtr->curActiveNum < tcbPtr->configTable.maxActive)
		{
			if( OSEK_TASK_AddaReadyBlock(tcbPtr) == E_OK )
			{
				tcbPtr->curActiveNum++;
				return E_OK;
			}
			else
			{
				return E_OS_LIMIT;
			}
		}
		else
		{
			return E_OS_LIMIT ;
		}
#else /* #if defined(CONFIG_OSEK_SYSTEM_MACTIVE)  */
		return E_OS_LIMIT ;
#endif /* #else defined(CONFIG_OSEK_SYSTEM_MACTIVE)  */
	}


#if defined(CONFIG_OSEK_SYSTEM_ET)
	// �¼���������������õ��¼��������㡣
	tcbPtr->setEvent = 0;
#endif  /* #if defined(CONFIG_OSEK_SYSTEM_ET) */

	// ����SUSPEND״̬����������µľ����鵽��������β�����ۼӼ���������޸�����״̬Ϊ����
	if( OSEK_TASK_AddaReadyBlock(tcbPtr) == E_OS_LIMIT )
	{
		return E_OS_LIMIT;// û�п��еľ��������
	}
#if defined(CONFIG_OSEK_SYSTEM_EP)
	tcbPtr->curActiveNum = 1;
#endif
	tcbPtr->status = OSEK_TASK_FIRST_RUN | READY;

	// �����ǰ��������ȼ��ȼ�����������ȼ��ͣ������Ƿ���Ҫ���ȡ�
	if( tcbPtr->curPriority > osekTask_RunningTask->taskControlBlock->curPriority )
	{
		// ��ǰ����������ռ
		if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
		{
#if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2) || defined(CONFIG_OSEK_INTERRUPT_ISR_ALL)
			// ������ж��е��õĴ˺��������Ƴ��л����������ж��˳��л���־�����򷵻�OSEK_TASK_NEED_DISPATCH
			if( osekInterrupt_NestedLevl != 0 )
			{
				osekTask_IsrTriggeredTaskSwitchNecessary = 1;
			}
			else
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	    	if(osekResource_ISRLast == 0)	// ϵͳû��ʹ���ж���Դ
#endif  /* defined(CONFIG_OSEK_RESOURCE_ISR) */

#endif /* #if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2)|| defined(CONFIG_OSEK_INTERRUPT_ISR_ALL) */
			{
				return OSEK_TASK_NEED_DISPATCH;
			}
		}
	}

	return E_OK;
}


/*
 * @brief
 *    osekTask_WakeTask�����ѵȴ��¼��������ڲ���������
 *
 * @param[in]	tcbPtr����Ҫ���ѵ�������ƽṹ��ָ�롣
 * @returns 	E_OK: �ɹ����ѣ�
 *              OSEK_TASK_NEED_DISPATCH: �ɹ����Ѳ�����Ҫ���µ���;
 *              E_OS_LIMIT: û���㹻�ľ�������á�
 *
 */
StatusType osekTask_WakeTask(T_OSEK_TASK_ControlBlock *tcbPtr)
{

	// ����µľ����鵽�������е�β�����޸�����״̬Ϊ����
	if( OSEK_TASK_AddaReadyBlock(tcbPtr) == E_OS_LIMIT )
	{
		return E_OS_LIMIT;// û�п��еľ��������
	}
	tcbPtr->status = READY;

	// �����ǰ��������ȼ��Ȼ�����������ȼ��ͣ������Ƿ���Ҫ���ȡ�
	if( tcbPtr->curPriority > osekTask_RunningTask->taskControlBlock->curPriority )
	{
		// ��ǰ����������ռ
		if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
		{
#if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2) || defined(CONFIG_OSEK_INTERRUPT_ISR_ALL)
			// ������ж��е��õĴ˺��������Ƴ��л����������ж��˳��л���־�����򷵻�OSEK_TASK_NEED_DISPATCH
			if( osekInterrupt_NestedLevl != 0 )
			{
				osekTask_IsrTriggeredTaskSwitchNecessary = 1;
			}
			else
#endif /* #if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2)|| defined(CONFIG_OSEK_INTERRUPT_ISR_ALL) */
			{
				return OSEK_TASK_NEED_DISPATCH;
			}
		}
	}

	return E_OK;
}


/*
 * @brief
 *    osekTask_WaitTask��ʹ��ǰ�������ȴ�״̬���ڲ���������
 *
 * @param[in]	��
 * @returns 	��
 *
 */
void osekTask_WaitTask( void )
{
	T_OSEK_TASK_ControlBlock *tcbPtr;
	tcbPtr = osekTask_RunningTask->taskControlBlock;

	// �޸ĵ�ǰ����״̬Ϊ�ȴ�̬�������Ƴ��������У��ͷž����飬��������ȼ�λͼ����Ӧλ
	tcbPtr->status = WAITING ;
	OSEK_TASK_MoveTaskFromReadyTable(tcbPtr->curPriority);
	OSEK_TASK_ReleaseReadyBlock(osekTask_RunningTask);
	OSEK_TASK_ClearPriorityMap(tcbPtr->curPriority);

	//���ʹ�����ڲ���Դ���������ȴ�����ʱ�����ȼ�Ӧ�ָ���
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
#if defined(CONFIG_OSEK_SYSTEM_EP)
	tcbPtr->curPriority = tcbPtr->configTable.basePriority ;
#else
	tcbPtr->curPriority = OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId);
#endif /* #if defined(CONFIG_OSEK_SYSTEM_EP) */
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

	// �����ǵ�ǰ�������ȴ�״̬����˱�������ص��ȡ�
	osekTask_Dispatch();

}


/*
 * @brief
 *    ActivateTask������ָ��������
 * @param[in]	taskId�������ID�š�
 * @returns		E_OK���ɹ�����
 * <p>			E_OS_LIMIT������״̬���Ի��߳�������󼤻����
 * <p>          [E_OS_ID����Ч������ID]
 */
StatusType ActivateTask( TaskType taskId )
{
	StatusType status;
	T_OSEK_TASK_ControlBlock *tcbPtr;
	OSEK_TARGET_OSIntSave( osIntSave );

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// ����ID��Ч������E_OS_ID
	if( taskId > (TaskType)CONFIG_OSEK_TASK_MAX_ID )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_ActivateTask,taskId) ;
	}
#endif /* #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS) */

	tcbPtr = &osekTask_TaskTable[taskId];

	OSEK_TARGET_DisableOSInt(osIntSave);

	// �����ڲ�������������
	status = osekTask_ActiveTask(tcbPtr);
	// ��������������Ҫ�ص��ȣ���ʵʩ����
	if( status == OSEK_TASK_NEED_DISPATCH )
	{
		osekTask_Dispatch();
	}
	else
	{
		if( status != E_OK )
		{
			OSEK_TARGET_EnableOSInt(osIntSave);
			OSEK_HOOK_ErrorHook(status,OSServiceId_ActivateTask,taskId) ;
		}
	}

	OSEK_TARGET_EnableOSInt(osIntSave);
	return E_OK;
}


/*
 * @brief
 *    TerminateTask��������ǰ����, ��ȷ������ǲ��᷵�صġ�
 * @param[in]	��
 * @returns		[E_OS_RESOURCE��������Դû���ͷţ�]
 * <p>			[E_OS_CALLEVEL�����ж��е����˸ù��ܡ�]
 *
 */
StatusType TerminateTask( void )
{
	T_OSEK_TASK_ControlBlock *tcbPtr;
	tcbPtr = osekTask_RunningTask->taskControlBlock;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)

#if defined(CONFIG_OSEK_RESOURCE)
	// ������Դû���ͷţ�����E_OS_RESOURCE
	if( tcbPtr->resourceList != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_TerminateTask,0) ;
	}

	// û���ͷŵ�������Դ������E_OS_RESOURCE
	if( osekTask_SchedulerLockLevel != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_TerminateTask,0) ;
	}

#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// ����ж���Դû���ͷţ�����E_OS_RESOURCE
    if (osekResource_ISRLast != 0)
    {
        OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_TerminateTask,0) ;
    }
#endif  /* defined(CONFIG_OSEK_RESOURCE_ISR) */

#endif /* #if defined(CONFIG_OSEK_RESOURCE) */

	// ���ж���ʹ���˸ù��ܣ�����E_OS_CALLEVEL
	if( osekInterrupt_NestedLevl != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_CALLEVEL,OSServiceId_TerminateTask,0) ;
	}
#endif /* #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS) */

	// ��Ϊ���᷵�أ����ֱ�ӹر��жϣ������ر����ж�״̬��
	OSEK_TARGET_DisableOSIntWithoutSave();

	// ִ��������ȥ����չ����
	OSEK_HOOK_PostTaskHook();

	// �Ӿ����������Ƴ���Ӧ�ľ����飬�黹�����о����������У����������ȼ�λͼ
	OSEK_TASK_MoveTaskFromReadyTable(tcbPtr->curPriority);
	OSEK_TASK_ReleaseReadyBlock(osekTask_RunningTask);
	OSEK_TASK_ClearPriorityMap(tcbPtr->curPriority);

#if defined(CONFIG_OSEK_SYSTEM_MACTIVE)
	tcbPtr->curActiveNum-- ;
	// �������ĵ�ǰ���������Ϊ�㣬��������Ϊ��ʼ״̬��
	if( tcbPtr->curActiveNum != 0)
	{
		tcbPtr->status = OSEK_TASK_FIRST_RUN | READY;
	}
	// ����������Ϊ�����Ĺ���״̬
	else
	{
		tcbPtr->status = SUSPENDED ;
	}
	// �ָ���������ȼ�
	tcbPtr->curPriority = tcbPtr->configTable.basePriority ;
#else /* #if defined(CONFIG_OSEK_SYSTEM_MACTIVE) */

	// ����֧�ֶ�μ������Ϊ�����Ĺ���״̬
	osekTask_RunningTask->taskControlBlock->status = SUSPENDED ;
	// һ�����ȼ���ֻ����һ������ʱ����������ȼ���ͨ����ID��ת���ġ�
	tcbPtr->curPriority = OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId);

#endif /* #else defined(CONFIG_OSEK_SYSTEM_MACTIVE) */

	// ִ��������ȥ���ص���
	osekTask_TerminateDispatch();

	// ���򲻻�ִ�е���������Ӹ�����Ǳ��������������
	return E_OK;
}


/*
 * @brief
 *    ChainTask��������ǰ�����Ҽ���ָ��������
 * @param[in]	taskId����Ҫ���������ID��
 * @returns		E_OS_LIMIT����Ҫ���������״̬���ԣ����߳�������󼤻������
 * <p>          [E_OS_RESOURCE��������Դû���ͷţ�]
 * <p>			[E_OS_CALLEVEL�����ж��е��ô˺�����]
 * <p>			[E_OS_ID����Ҫ���������ID�Ų��Ϸ���]
 *
 */
StatusType ChainTask( TaskType taskId )
{
	T_OSEK_TASK_ControlBlock *tcbPtr;
	T_OSEK_TASK_ControlBlock *runningTcb;
	OSEK_TARGET_OSIntSave( osIntSave ) ;

	runningTcb = osekTask_RunningTask->taskControlBlock;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)

#if defined(CONFIG_OSEK_RESOURCE)
	// ���������Դû���ͷţ�����E_OS_RESOURCE
	if( runningTcb->resourceList != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_ChainTask,taskId) ;
	}

	// �����������Դû���ͷţ�����E_OS_RESOURCE
	if( osekTask_SchedulerLockLevel != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_ChainTask,taskId) ;
	}
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// ����ж���Դû���ͷţ�����E_OS_RESOURCE
    if (osekResource_ISRLast != 0)
    {
        OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_ChainTask,taskId) ;
    }
#endif  /* defined(CONFIG_OSEK_RESOURCE_ISR) */
#endif /* #if defined(CONFIG_OSEK_RESOURCE) */

	// ������ж��е��øú���������E_OS_CALLEVEL
	if( osekInterrupt_NestedLevl != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_CALLEVEL,OSServiceId_ChainTask,taskId) ;
	}

	// �������ID���Ϸ�������E_OS_ID
	if( taskId > CONFIG_OSEK_TASK_MAX_ID )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_ChainTask,taskId) ;
	}

#endif /* #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS) */

	tcbPtr = &osekTask_TaskTable[taskId];

	OSEK_TARGET_DisableOSInt(osIntSave);

	// ��ǰ����chain�Լ�ʱ��������һ�μ������������ڳ�ʼ����̬�����ͷ��ڲ���Դ
	if(tcbPtr == runningTcb)
	{
		OSEK_HOOK_PostTaskHook();
		tcbPtr->status = OSEK_TASK_FIRST_RUN | READY;
		// ������Ӿ�������ͷ��ȡ��
		OSEK_TASK_MoveTaskFromReadyTable(tcbPtr->curPriority);

#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
#if defined(CONFIG_OSEK_SYSTEM_EP)
		if(tcbPtr->curPriority > tcbPtr->configTable.basePriority)
		{
			OSEK_TASK_ClearPriorityMap(tcbPtr->curPriority);
			tcbPtr->curPriority = tcbPtr->configTable.basePriority ;
			OSEK_TASK_SetPriorityBitMap(tcbPtr->configTable.basePriority);
		}
#else /* #if defined(CONFIG_OSEK_SYSTEM_EP) */
		if(tcbPtr->curPriority > OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId))
		{
			OSEK_TASK_ClearPriorityMap(tcbPtr->curPriority);
			tcbPtr->curPriority = OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId);
			OSEK_TASK_SetPriorityBitMap(OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId));
		}
#endif /* #else defined(CONFIG_OSEK_SYSTEM_EP) */
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

		// ������ҵ���������β��
		OSEK_TASK_AddTask2ReadyTableAtTail(osekTask_RunningTask);

	}
	else
	{
		// ���ڷ�SUSPEND״̬����������������μ���򼤻�����ﵽ���ֵ������E_OS_LIMIT��
		if( tcbPtr->status != SUSPENDED )
		{
#if defined(CONFIG_OSEK_SYSTEM_MACTIVE)
			if(tcbPtr->curActiveNum == tcbPtr->configTable.maxActive)
			{
				OSEK_TARGET_EnableOSInt(osIntSave);
				OSEK_HOOK_ErrorHook(E_OS_LIMIT,OSServiceId_ChainTask,taskId) ;
			}
#else /* #if defined(CONFIG_OSEK_SYSTEM_MACTIVE) */
			OSEK_TARGET_EnableOSInt(osIntSave);
			OSEK_HOOK_ErrorHook(E_OS_LIMIT,OSServiceId_ChainTask,taskId) ;
#endif /* #else defined(CONFIG_OSEK_SYSTEM_MACTIVE) */
		}

		// ִ��������ȥ����չ����
		OSEK_HOOK_PostTaskHook();

		// �Ӿ����������Ƴ���Ӧ�ľ����飬�黹�����о����������У����������ȼ�λͼ
		OSEK_TASK_MoveTaskFromReadyTable(runningTcb->curPriority);
		OSEK_TASK_ReleaseReadyBlock(osekTask_RunningTask);
		OSEK_TASK_ClearPriorityMap(runningTcb->curPriority);

#if defined(CONFIG_OSEK_SYSTEM_MACTIVE)
		runningTcb->curActiveNum-- ;
		// �������ĵ�ǰ���������Ϊ�㣬��������Ϊ��ʼ״̬��
		if( runningTcb->curActiveNum != 0)
		{
			runningTcb->status = OSEK_TASK_FIRST_RUN | READY;
		}
		// ����������Ϊ�����Ĺ���״̬
		else
		{
			runningTcb->status = SUSPENDED ;
		}
		// �ָ���������ȼ�
		runningTcb->curPriority = runningTcb->configTable.basePriority ;

#else /*  #if defined(CONFIG_OSEK_SYSTEM_MACTIVE) */

		// ����֧�ֶ�μ������Ϊ�����Ĺ���״̬
		osekTask_RunningTask->taskControlBlock->status = SUSPENDED ;
		// һ�����ȼ���ֻ����һ������ʱ����������ȼ���ͨ����ID��ת���ġ�
		runningTcb->curPriority = OSEK_TASK_ID2PRI(runningTcb->configTable.taskId);

#endif /* #if defined(CONFIG_OSEK_SYSTEM_MACTIVE) */

		// ����Ҫ�����������뵽���������У����ۼ��伤�������������״̬Ϊ������ʼ̬��
		if( OSEK_TASK_AddaReadyBlock(tcbPtr) == E_OS_LIMIT )
		{
			OSEK_TARGET_EnableOSInt(osIntSave);
			return E_OS_LIMIT;	// û�п��еľ��������
		}
#if defined(CONFIG_OSEK_SYSTEM_EP)
		tcbPtr->curActiveNum++ ;
#endif
		if( tcbPtr->status == SUSPENDED )
		{
			tcbPtr->status = OSEK_TASK_FIRST_RUN | READY;
		}
	}
#if defined(CONFIG_OSEK_SYSTEM_ET)
	// �¼���������������õ��¼��������㡣
	tcbPtr->setEvent = 0;
#endif /* #if defined(CONFIG_OSEK_SYSTEM_ET) */

   	osekTask_TerminateDispatch();

	// ���򲻻�ִ�е���������Ӹ�����Ǳ��������������
	return E_OK;

}


/*
 * @brief
 *    Schedule���ص��ȣ���Ҫ����������������CPU�������������ȼ��������С�
 * @param[in]	�ޡ�
 * @returns		E_OK���ɹ���
 * <p>          [E_OS_RESOURCE: ������Դ��������������Դ���ж���Դ��û���ͷţ�]
 * <p>		    [E_OS_CALLEVEL: ���ж��е��õĴ˺�����]
 *
 */
StatusType Schedule( void )
{
	OSEK_TARGET_OSIntSave( osIntSave ) ;
	T_OSEK_TASK_ControlBlock *tcbPtr;
	tcbPtr = osekTask_RunningTask->taskControlBlock;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)

#if defined(CONFIG_OSEK_RESOURCE)
	// �������Դû���ͷţ�����E_OS_RESOURCE
	if( tcbPtr->resourceList != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_Schedule,0) ;
	}

	// �����������Դû���ͷţ�����E_OS_RESOURCE
	if( osekTask_SchedulerLockLevel != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_Schedule,0) ;
	}
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// ����ж���Դû���ͷţ�����E_OS_RESOURCE
    if (osekResource_ISRLast != 0)
    {
        OSEK_HOOK_ErrorHook(E_OS_RESOURCE,OSServiceId_Schedule,0) ;
    }
#endif  /* defined(CONFIG_OSEK_RESOURCE_ISR) */

#endif /* #if defined(CONFIG_OSEK_RESOURCE) */

	// ������ж��е��õĴ˺���������E_OS_CALLEVEL
	if( osekInterrupt_NestedLevl != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_CALLEVEL,OSServiceId_Schedule,0) ;
	}
#endif /* #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS) */

	OSEK_TARGET_DisableOSInt(osIntSave);

	// ����������ڲ���Դ�������ͷ��ڲ���Դ��ʵ���Ͼ��ǵ������ȼ�
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
#if defined(CONFIG_OSEK_SYSTEM_EP)
	if( tcbPtr->curPriority > tcbPtr->configTable.basePriority )
	{
		osekTask_ChangeRunningTaskPriority(tcbPtr->configTable.basePriority);
	}
#else /* #if defined(CONFIG_OSEK_SYSTEM_EP) */
	if( tcbPtr->curPriority > OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId))
	{
		osekTask_ChangeRunningTaskPriority(OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId));
	}
#endif /* #else defined(CONFIG_OSEK_SYSTEM_EP) */
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

	osekTask_Dispatch();

	OSEK_TARGET_EnableOSInt(osIntSave);

	return E_OK;
}


/*
 * @brief
 *    osekTask_Dispatch: ���������л�����ʹ�����ǲ�����ռ��Ҳ�ᷢ���л����ڲ���������
 * @param[in]	�ޡ�
 * @returns		�ޡ�
 *
 */
void osekTask_Dispatch( void )
{
	OSPRIOTYPE pri;
	T_OSEK_TASK_ReadyBlock *oldTask;
	T_OSEK_TASK_ControlBlock *tcbPtr;

#if defined(CONFIG_OSEK_HOOK_POSTTASK)
	T_OSEK_TASK_ReadyBlock *newTask;
#endif

	// ������δ�ͷţ��򲻽��е���
	if( osekTask_SchedulerLockLevel  != 0)
	{
		return ;
	}

	// ���ж���Ҳ�����е���
	if( osekInterrupt_NestedLevl != 0 )
	{
		return ;
	}

	oldTask = osekTask_RunningTask ;
	pri = OSEK_TASK_GetHighestPriority();

#if defined(CONFIG_OSEK_HOOK_POSTTASK)
	newTask = OSEK_TASK_GetReadyTask(pri);

	// ��ִ��������ȥ��չʱ���������ڵ�ǰ������Ȼ����ȥ����������£���˲��������л���ǰ����
	if( newTask != osekTask_RunningTask)
	{
		 OSEK_HOOK_PostTaskHook();
	}
	osekTask_RunningTask = newTask;
#else /* #if defined(CONFIG_OSEK_HOOK_POSTTASK) */

	osekTask_RunningTask = OSEK_TASK_GetReadyTask(pri);

#endif /* #else defined(CONFIG_OSEK_HOOK_POSTTASK) */

	tcbPtr = osekTask_RunningTask->taskControlBlock;

	// ֻ����Ҫ�л��������ǵ�ǰ����ʱ�Ž����л�
	if( oldTask != osekTask_RunningTask )
	{
		// ������ȥ�����������
		if( osekTarget_SaveContext(oldTask->taskControlBlock->context) != 0)
		{
			// �������л��������ȼ���Ƿ���Ҫ�����ڲ���Դ���������ȼ���Ȼ���������������չ���á�
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
			if( osekTask_RunningTask->taskControlBlock->curPriority < osekTask_RunningTask->taskControlBlock->configTable.inresPriority )
			{
				osekTask_ChangeRunningTaskPriority( osekTask_RunningTask->taskControlBlock->configTable.inresPriority );
			}
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

			OSEK_HOOK_PreTaskHook();
			return;

		}

		// ��ȥ�����ǻ�������ʱ��Ҫ������һ��������������ʱ��ջָ�롣
		if( (oldTask->taskControlBlock->configTable.property & OSEK_TASK_EXTENDED) == 0  )
		{
			OSEK_TARGET_SaveBTSP((oldTask->taskControlBlock->context)->sp);
		}

		// �����һ������ʱ����Ҫ����ջָ�룬Ȼ�����ֱ�ӵ��õķ�ʽ��������
		if( (tcbPtr->status & OSEK_TASK_FIRST_RUN) != 0 )
		{
			// �����һ�����б�־
			tcbPtr->status &= (~OSEK_TASK_FIRST_RUN);

			// ��չ�����ж�����ջ��������Ҫ���е�����չ������������ջ�л�������Ǵ���չ��������������Ҳ��Ҫ����ջ�л���
#if defined(CONFIG_OSEK_SYSTEM_ET)
			if((tcbPtr->configTable.property & OSEK_TASK_EXTENDED) != 0)
			{
				osekTarget_LoadETSP(tcbPtr->configTable.stackTop);
			}
			else
#endif /* #if defined(CONFIG_OSEK_SYSTEM_ET) */
			{
				osekTarget_LoadBTSP();
			}

			// �����ڲ���Դ�����ȼ�����������������ȼ�
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
			if( osekTask_RunningTask->taskControlBlock->curPriority < osekTask_RunningTask->taskControlBlock->configTable.inresPriority )
			{
				osekTask_ChangeRunningTaskPriority(osekTask_RunningTask->taskControlBlock->configTable.inresPriority );
			}
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

			OSEK_HOOK_PreTaskHook();

			// ���ν�������ʱ���ж϶���ʹ�ܵġ�
			OSEK_TARGET_EnableOSIntWithoutSave();
			//CLEAR_IPL;

			// ������������
			OSEK_TASK_CallTaskEntry();
		}
		// ��������ǵ�һ�����У���ֱ�ӻָ������������л�������
		else /* if( (osekTask_RunningTask->taskControlBlock->status & OSEK_TASK_FIRST_RUN) != 0 ) */
		{
			osekTarget_RestoreContext(tcbPtr->context);
		}

	} /* if( oldTask != osekTask_RunningTask ) */

#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
	else	// �����������л�����Ҫ�ָ�����������ڲ���Դ���ȼ�
	{
		if( tcbPtr->curPriority < tcbPtr->configTable.inresPriority )
		{
			osekTask_ChangeRunningTaskPriority(tcbPtr->configTable.inresPriority );
		}
	}
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */
}


/*
 * @brief
 *    osekTask_TerminateDispatch��������ǰ���񣬲�ѡ�����ȼ���ߵľ����������У��ڲ���������
 * @param[in]	�ޡ�
 * @returns		�ޡ�
 *
 */
void osekTask_TerminateDispatch( void )
{
	OSPRIOTYPE pri;
	T_OSEK_TASK_ControlBlock *tcbPtr;

	pri = OSEK_TASK_GetHighestPriority();
	osekTask_RunningTask = OSEK_TASK_GetReadyTask(pri);
	tcbPtr = osekTask_RunningTask->taskControlBlock;

	// �����һ������ʱ����Ҫ����ջָ�룬Ȼ�����ֱ�ӵ��õķ�ʽ��������
	if( (tcbPtr->status & OSEK_TASK_FIRST_RUN) != 0 )
	{
		// �����һ�����б�־
		tcbPtr->status &= (~OSEK_TASK_FIRST_RUN);

		// ��չ�����ж�����ջ��������Ҫ���е�����չ������������ջ�л�������Ǵ���չ��������������Ҳ��Ҫ����ջ�л���
#if defined(CONFIG_OSEK_SYSTEM_ET)
		if((tcbPtr->configTable.property & OSEK_TASK_EXTENDED) != 0)
		{
			osekTarget_LoadETSP(tcbPtr->configTable.stackTop);
		}
		else
#endif /* #if defined(CONFIG_OSEK_SYSTEM_ET) */
		{
			osekTarget_LoadBTSP();
		}

		// �����ڲ���Դ�����ȼ�����������������ȼ�
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
		if( osekTask_RunningTask->taskControlBlock->curPriority < osekTask_RunningTask->taskControlBlock->configTable.inresPriority )
		{
			osekTask_ChangeRunningTaskPriority(osekTask_RunningTask->taskControlBlock->configTable.inresPriority );
		}
#endif /* #if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

		// ��������������չ���ã�ʹ���жϣ���������������
		OSEK_HOOK_PreTaskHook();
		OSEK_TARGET_EnableOSIntWithoutSave();
		OSEK_TASK_CallTaskEntry();
	}
	else	// �����ǵ�һ�����У���ֱ�ӻָ������������л�������
	{
#if defined(CONFIG_OSEK_SYSTEM_ET)
		if( (tcbPtr->configTable.property & OSEK_TASK_EXTENDED) == 0  )
#endif /* #if defined(CONFIG_OSEK_SYSTEM_ET) */
		{
			OSEK_TARGET_SaveBTSP((tcbPtr->context)->sp);
		}
		osekTarget_RestoreContext(tcbPtr->context);
	}

}


/*
 * @brief
 *    GetTaskState����ȡָ�������״̬��״̬����RUNNING��WAITING��READY��SUSPENDED�ȡ�
 * @param[in]	taskId������ID�ţ�
 *              state: ����״̬���������ã����ڱ������������״̬��
 * @returns 	E_OK: �ɹ���ȡ������״̬��
 * <p>          [E_OS_ID������ID����Ч��]
 *
 */
StatusType GetTaskState ( TaskType taskId, TaskStateRefType state )
{

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������ID������Χ������E_OS_ID
	if( taskId > CONFIG_OSEK_TASK_MAX_ID )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetTaskState,0) ;
	}
#endif /* #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS) */

	// ��������ʱ�����¼״̬�ı�����Ȼ����ΪREADY����˴˴������״̬������ʽ��ֵΪRUNNING��
	if( osekTask_RunningTask->taskControlBlock->configTable.taskId == taskId )
	{
		*state = RUNNING ;
	}
	else
	{
		*state = (osekTask_TaskTable[taskId].status & OSEK_TASK_STATE_MASK);
	}

	return E_OK;

}


/*
 * @brief
 *    GetTaskID����ȡ��ǰ�����ID�š�
 * @param[in]	taskId����������ID�ı���������
 * @returns		E_OK: �ɹ���ȡ������״̬��
 *
 */
StatusType GetTaskID( TaskRefType taskId )
{

	*taskId = osekTask_RunningTask->taskControlBlock->configTable.taskId;
	if(*taskId == OSEK_TASK_IDLE_ID)
	{
		*taskId = INVALID_TASK;
	}

	return E_OK;

}


/*
 * @brief
 *    osekTask_Initialize: ��ʼ�����������Ҫ�Ǹ�����������ý�����ؽṹ�ĳ�ʼ�����ڲ���������
 * @param[in]	��
 * @returns		��
 *
 */
void osekTask_Initialize( void )
{
	OSDWORD i;
	T_OSEK_TASK_ControlBlock *tcbPtr;

	// ��ʼ��������
	osekTask_SchedulerLockLevel = 0;

	// ��ʼ�����ȼ�λͼ
#if defined(CONFIG_OSEK_TARGET_HARDBITMAP)
	osekTask_PriorityBitMap1 = 0;
#if defined(CONFIG_OSEK_TASK_EXTPRIORS)
	osekTask_PriorityBitMap2 = 0;
#endif /* #if defined(CONFIG_OSEK_TASK_EXTPRIORS) */
#endif /* #if defined(CONFIG_OSEK_TARGET_HARDBITMAP) */

#if defined(CONFIG_OSEK_TARGET_SOFTBITMAP)
	//memset(osekTask_PriorityBitMap,0,sizeof(osekTask_PriorityBitMap));
	osekTask_PriorityBitMapMajor = 0;
#endif /* #if defined(CONFIG_OSEK_TARGET_SOFTBITMAP) */

	// ��ʼ��������ƽṹ���������б����������ġ��������
	//memset(osekTask_TaskTable,0,sizeof(osekTask_TaskTable));
	//memset(osekTask_ReadyTaskTable,0,sizeof(osekTask_ReadyTaskTable));
	//memset(osekTask_ContextTable,0,sizeof(osekTask_ContextTable));
	//memset(osekTask_ReadyBlock,0,sizeof(osekTask_ReadyBlock));

	// �����о�������֯������
	for(i=0; i<((OSDWORD)(CONFIG_OSEK_TASK_TOTAL_ACTIVATE_NUMBER-1)); i++)
	{
		osekTask_ReadyBlock[i].nextTask = &osekTask_ReadyBlock[i+1];
	}
	osekTask_FreeReadyBlock = &osekTask_ReadyBlock[0];

	// ����������Ϣ��ʼ����������
	tcbPtr = &osekTask_TaskTable[0];
	for( i = 0; i < ((OSDWORD)(CONFIG_OSEK_TASK_NUMBER)) ; i++ )
	{

		tcbPtr->configTable = osekConfig_TaskTable[i] ;

		// �������ȼ�Խ�ߵ����������ýṹ�е���ӦֵԽС���������һ�¡�
#if defined(CONFIG_OSEK_SYSTEM_EP)
		tcbPtr->curPriority = tcbPtr->configTable.basePriority ;
#else /* #if defined(CONFIG_OSEK_SYSTEM_EP) */
		tcbPtr->curPriority =OSEK_TASK_ID2PRI(tcbPtr->configTable.taskId );
#endif /* #else defined(CONFIG_OSEK_SYSTEM_EP) */

		// ���Ӧ��ģʽ������1��������Զ��������������������񣬷����������ļ����������ж��Ƿ񼤻�����
#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
        if ((tcbPtr->configTable.autoStart & (1 << osekExecution_CurrentAppMode)) != 0 )
#else /* #if (CONFIG_OSEK_SYSTEM_APPMODES > 1) */
		if( (tcbPtr->configTable.property & OSEK_TASK_ACTIVE ) != 0 )
#endif /* #else (CONFIG_OSEK_SYSTEM_APPMODES > 1) */
		{
			OSEK_TASK_AddaReadyBlock(tcbPtr);	// ��ȷ���˲�ִ�н����OK��
#if defined(CONFIG_OSEK_SYSTEM_EP)
			tcbPtr->curActiveNum = 1;
#endif
			tcbPtr->status = OSEK_TASK_FIRST_RUN | READY;
		}
		else
		{
			tcbPtr->status = SUSPENDED ;
		}

		// ��ʼ������������ָ��
		tcbPtr->context = &osekTask_ContextTable[i];

		// �����Ҫ��������ջ�ļ�飬���ջ������䡣
#if defined(CONFIG_OSEK_TASK_STACK_CHECK)
#if defined(CONFIG_OSEK_SYSTEM_ET)
		if( (tcbPtr->configTable.property & OSEK_TASK_EXTENDED ) != 0 )
		{
			memset(tcbPtr->configTable.stackBottom,OSEK_DEBUG_STACKPATTERN,(tcbPtr->configTable.stackTop - tcbPtr->configTable.stackBottom));
		}
#endif /* #if defined(CONFIG_OSEK_SYSTEM_ET) */
#endif /* #if defined(CONFIG_OSEK_TASK_STACK_CHECK) */

		tcbPtr++;

	}

	// ��ʼ��IDLE����IDLE��������ñ��������һ��,��IDLE��������ǻ�������IDLE�����״ֻ̬����READY
	osekTask_TaskTable[OSEK_TASK_IDLE_ID].status = READY;

}


