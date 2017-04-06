/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekDebug.c,v $
 * Revision 1.0  2008/04/10 15:40:00
 * �����ļ���
 */

/*
 * @file 	osekDebug.c
 * @brief
 *	<li>���ܣ�ʵ�ֵ�����ع��ܡ�</li>
 * @author
 * @date 	2008-04-10
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"

/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

/**************************** ʵ�ֲ��� *********************************/

#if defined(CONFIG_OSEK_TASK_STACK_CHECK)

#if defined(CONFIG_OSEK_SYSTEM_ET)
/*
 * @brief
 *    GetUsage����ȡ��ջ��ʹ��������ڲ���������
 * @param
 * @param[in]	startPtr����ʼλ��ָ�롣
 *          	endPtr������λ��ָ�롣
 * @param[out]  �ޡ�
 * @returns:    ��ջ��ʹ�õ��ֽ�����
 */
static OSDWORD GetUsage( OSBYTEPTR startPtr , OSBYTEPTR endPtr)
{
	// ��ȡ�ض��ַ�ģʽ����ʼλ��
	while( (startPtr != endPtr) && (*startPtr == (OSBYTE)OSEK_DEBUG_STACKPATTERN))
	{
		startPtr++;
	}

	// ���㲢���ض�ջ��ʹ�õ��ֽ�����
	return ((OSDWORD)( endPtr - startPtr ));
}
#endif  /* defined(CONFIG_OSEK_SYSTEM_ET) */


/*
 * @brief
 *    GetRunningStackUsage����ȡ��������Ķ�ջʹ�������
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    OSEK_DEBUG_STACKNOASSIGNED: ָ������û�ж�ջ��
 * <p>          ջ��ʹ�õ��ֽ�����
 */
OSDWORD GetRunningStackUsage( void )
{

#if defined(CONFIG_OSEK_SYSTEM_ET)
	// ���������������չ����������ڲ�����GetUsage��ȡ��ջ��ʹ�����
	if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_EXTENDED ) != 0 )
	{
		return GetUsage(osekTask_RunningTask->taskControlBlock->configTable.stackBottom,osekTask_RunningTask->taskControlBlock->configTable.stackTop);
	}
#endif

	// ��ǰ������������չ����û�е����Ķ�ջ������OSEK_DEBUG_STACKNOASSIGNED
	return OSEK_DEBUG_STACKNOASSIGNED ;

}


/*
 * @brief
 *    GetStackUsage����ȡջ��ʹ�������
 * @param
 * @param[in]	taskId�������ID��
 * @param[out]  �ޡ�
 * @returns:    OSEK_DEBUG_STACKNOASSIGNED: ָ������û�ж�ջ��
 * <p>          ջ��ʹ�õ��ֽ�����
 */
OSDWORD GetStackUsage( TaskType taskId )
{
#if defined(CONFIG_OSEK_SYSTEM_ET)
	T_OSEK_TASK_ControlBlock *tcbPtr;
#endif
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������ID������Χ������OSEK_DEBUG_STACKNOASSIGNED
	if( taskId > CONFIG_OSEK_TASK_MAX_ID )
	{
		return OSEK_DEBUG_STACKNOASSIGNED;
	}
#endif

#if defined(CONFIG_OSEK_SYSTEM_ET)
	
	tcbPtr = &osekTask_TaskTable[taskId];

	// ���ָ����������չ����������ڲ�����GetUsage��ȡ��ջ��ʹ�����
	if( (tcbPtr->configTable.property & OSEK_TASK_EXTENDED ) != 0 )
	{
		return GetUsage(tcbPtr->configTable.stackBottom,tcbPtr->configTable.stackTop);
	}
#endif

	// ָ����������չ����û�е����Ķ�ջ������OSEK_DEBUG_STACKNOASSIGNED
	return OSEK_DEBUG_STACKNOASSIGNED ;

}

#endif /* #if defined(CONFIG_OSEK_TASK_STACK_CHECK)  */


/*
 * @brief
 *    GetTimeStamp����ȡʱ�����
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    ʱ�����ֵ��
 */
OSDWORD GetTimeStamp( void )
{
	unsigned int value;


	// ��ȡӲ����ʱ���ļ���ֵ
	OSEK_Time_ReadCount(&value);

	return value;

}

