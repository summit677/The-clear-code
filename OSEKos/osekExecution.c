/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekExecution.c,v $
 * Revision 1.0  2008/03/12 13:37:00
 * �����ļ���
 */

/*
 * @file 	osekExecution.c
 * @brief
 *	<li>���ܣ�ʵ��ϵͳ�������͹رյȹ��ܡ�</li>
 * @author
 * @date 	2008-03-12
 * <p>���ţ�
 */



/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"
#include <string.h>


/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

// ȫ�ֱ���
OSBYTE osekExecution_CurrentAppMode;


/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    StartOS����������ϵͳ��
 * @param
 * @param[in]	mode��Ӧ��ģʽ��
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */

void StartOS( AppModeType mode )
{

	// �ر��ж�
	OSEK_TARGET_DisableOSIntWithoutSave() ;

	//��ʼ��Ӧ��ģʽ��
	osekExecution_CurrentAppMode = mode;

    //��ʼ���������
	osekTask_Initialize();

	// ��ʼ���жϹ���
#if (!defined(CONFIG_OSEK_INTERRUPT_ISR_NULL))
    osekInterrupt_Initialize();
#endif

    // ��ʼ��Counter����
#if defined(CONFIG_OSEK_COUNTER)
    osekCounter_Initialize();
#endif

    // ��ʼ��Alarm����
#if defined(CONFIG_OSEK_ALARM)
    osekAlarm_Initialize();
#endif

	//��ʼ����Դ����
#if defined(CONFIG_OSEK_RESOURCE)
    osekResource_Initialize();
#endif


	// ׼���������������

	// ��ϵͳ�ĵ�һ��������ΪIDLE����
#if defined(CONFIG_OSEK_SYSTEM_EP)
	osekTask_RunningTask = OSEK_TASK_GetReadyTask(0);
#else
	osekTask_RunningTask = OSEK_TASK_GetReadyTask(OSEK_TASK_ID2PRI(OSEK_TASK_IDLE_ID));
#endif

    // ��ʼ��ͨ�Ź���
#if defined(CONFIG_OSEK_COM_LOCALMESSAGESONLY)
#if CONFIG_OSEK_COM_NUMBER_OF_MESSAGES > 0
	InitCOM();
#endif
#endif

	// ����ϵͳ����HOOK����
	OSEK_HOOK_StartupHook();

	// ����ϵͳ�ص���
	osekTask_Dispatch();

	// ���ж�
	OSEK_TARGET_EnableOSIntWithoutSave();

	// IDLE������ѭ��
	while(1)
	{

		OSEK_HOOK_IdleHook();

	}

}


/*
 * @brief
 *    ShutdownOS���رղ���ϵͳ��
 * @param
 * @param[in]	error��������Ϣ��
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */

void ShutdownOS( StatusType error )
{

	// �ر��ж�
	OSEK_TARGET_DisableOSIntWithoutSave() ;

	// ����ϵͳ�ر�HOOK����
	OSEK_HOOK_ShutdownHook(error);

	// �ر�ͨ��ģ��
#if defined(CONFIG_OSEK_COM_LOCALMESSAGESONLY)
#if CONFIG_OSEK_COM_NUMBER_OF_MESSAGES > 0
	CloseCOM();
#endif
#endif

	// ��������ѭ��
	while(1)
	{
	}

}


