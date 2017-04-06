/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekAlarm.c,v $
 * Revision 1.0  2008/03/29 14:44:00
 * �����ļ���
 */

/*
 * @file 	osekAlarm.c
 * @brief
 *	<li>���ܣ�ʵ�ֱ������Ĺ���</li>
 * @author
 * @date 	2009-03-29
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/


#include <string.h>
#include "osprop.h"
#include "osapi.h"
#include "cfg.h"


#if defined(CONFIG_OSEK_ALARM)

/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

// ȫ�ֱ���
// ALARM���ƿ��
T_OSEK_ALARM_ControlBlock osekAlarm_AlarmTable[CONFIG_OSEK_ALARM_NUMBER];

/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    GetAlarmBase����ȡָ��ALARM�Ļ�����Ϣ��
 * @param
 * @param[in]	almId��ָ��ALARM���ƿ��ָ�롣
 * @param[out]	info�� ALARM������Ϣ�ṹ�����á�
 * @returns:    E_OK�� �ɹ���
 * <p>          [E_OS_ID:��Ч��ALARM��]
 */

StatusType GetAlarmBase( AlarmType almId, AlarmBaseRefType info )
{
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������Ĳ���almId�Ƿ���Ч����Ч����E_OS_ID
	if( almId != almId->alarmId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetAlarmBase,almId) ;
	}
#endif

	// ͨ��almId�ҵ���Ӧcounter��������Ϣ�������丳ֵ���������info
	*info = osekCounter_CounterTable[almId->configTable.ctrId].configTable ;

	// �ɹ�������E_OK
	return E_OK;

}


/*
 * @brief
 *    GetAlarm����ȡָ��ALARM����ǰ�����ʱ�䡣
 * @param
 * @param[in]	almId: ָ��ALARM���ƿ��ָ�롣
 * @param[out]	tick:  ���ʱ��ֵ�����á�
 * @returns:    E_OK���ɹ���
 * <p>          E_OS_NOFUNC:ָ����ALARMδ��ʹ�á�
 * <p>          [E_OS_ID:��Ч��ALARM��]
 */

StatusType GetAlarm( AlarmType almId, TickRefType tick )
{
	CtrType     ctrId;
	OSEK_TARGET_OSIntSave(osIntSave);

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������Ĳ���almId�Ƿ���Ч����Ч����E_OS_ID
	if( almId != almId->alarmId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetAlarm,almId) ;
	}
#endif

	// ���ָ��ALARMδ��ʹ�ã�����E_OS_NOFUNC
	if( almId->prevAlarm == (AlarmType)0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_NOFUNC,OSServiceId_GetAlarm,almId) ;
	}

	// ��ȡָ��ALARM����Ӧ��counter
	ctrId =  almId->configTable.ctrId;

	// �����ж�
	OSEK_TARGET_DisableOSInt(osIntSave);

	// ��ȡ�������ĵ�ǰ����ֵ
	*tick = osekCounter_CounterTable[ctrId].currentTick;

    // counter��ǰֵС�ڵ���ALARM����ֵ�����ʱ�����
	if( almId->expirationTick >= *tick )
    {
        *tick = almId->expirationTick - *tick;
    }
    // counter��ǰֵ����ALARM����ֵ�����ʱ�����
	else
    {
        *tick = almId->expirationTick + osekCounter_CounterTable[ctrId].configTable.maxallowedvalue + 1 - *tick;
    }

	// ���ж�
    OSEK_TARGET_EnableOSInt(osIntSave);

	// �ɹ�������E_OK
	return E_OK;

}

/*
 * @brief
 *    SetAlarm������ALARM���ڲ���������
 * @param		almId: ָ��ALARM���ƿ��ָ�롣
 *              start: ��tickΪ��λ����ʼʱ��ֵ��
 *              cycle: ������ALARM������ֵ������һ���Ե�ALARM����ֵ����Ϊ0��
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns: �ޡ�
 */
static void SetAlarm( AlarmType almId, TickType start, TickType cycle )
{
    CtrType     ctrId;
	StatusType	status;

	// ��ȡָ��ALARM����Ӧ��counter
    ctrId = almId->configTable.ctrId;

    almId->expirationTick = start;
    almId->periodTick = cycle;

	// ��ָ��ALARM�Ŀ��ƿ���뵽��Ӧcounter��ALARM����ͷ�ڵ�
    almId->nextAlarm =  osekCounter_CounterTable[ctrId].alarm;
    osekCounter_CounterTable[ctrId].alarm = almId;
    almId->prevAlarm = (AlarmType)(&( osekCounter_CounterTable[ctrId].alarm));
    if ( almId->nextAlarm != (AlarmType)0  )
    {
        ( almId->nextAlarm )->prevAlarm = almId;
    }

	// �����ʼʱ�����counter�ĵ�ǰtickֵ�������osekAlarm_Check2������������ѵ��ڵ�ALARM
    if (start == osekCounter_CounterTable[ctrId].currentTick )
    {
        status = osekAlarm_Check2( almId, &osekCounter_CounterTable[ctrId] );
		// ������ȱ�־��Ϊ0����ʵʩ����
		if( status == OSEK_TASK_NEED_DISPATCH )
		{
    		osekTask_Dispatch();
		}
    }
}



/*
 * @brief
 *    SetRelAlarm���������ʱ��ALARM��
 * @param		almId: ָ��ALARM���ƿ��ָ�롣
 *              increment: ��tickΪ��λ�������ʼʱ��ֵ��
 *              cycle: ������ALARM������ֵ������һ���Ե�ALARM����ֵ����Ϊ0��
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns:    E_OK���ɹ���
 * <p>          E_OS_STATE:ָ����ALARM�Ѿ����á�
 * <p>          [E_OS_ID:��Ч��ALARM��]
 * <p>          [E_OS_VALUE:�������ʼʱ������ڲ����������õķ�Χ��]
 */

StatusType  SetRelAlarm( AlarmType almId, TickType increment, TickType cycle )
{
	CtrType     ctrId;
	OSEK_TARGET_OSIntSave(osIntSave) ;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������Ĳ���almId�Ƿ���Ч����Ч����E_OS_ID
	if( almId != almId->alarmId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_SetRelAlarm,almId) ;
	}
#endif

	// ��ȡָ��ALARM����Ӧ��counter
	ctrId =  almId->configTable.ctrId;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �����ʼʱ��ֵ����counter���õ����ֵ������E_OS_VALUE
	if( increment > osekCounter_CounterTable[ctrId].configTable.maxallowedvalue )
	{
       	OSEK_HOOK_ErrorHook(E_OS_VALUE,OSServiceId_SetRelAlarm,almId) ;
	}

    // ����������ALARM���������ֵ����counter���õ����ֵ�������С����ֵ������E_OS_VALUE
    if(( cycle != 0 ) && ( (cycle > osekCounter_CounterTable[ctrId].configTable.maxallowedvalue) || (cycle < osekCounter_CounterTable[ctrId].configTable.mincycle) ) )
    {
    	OSEK_HOOK_ErrorHook(E_OS_VALUE,OSServiceId_SetRelAlarm,almId) ;
	}
#endif

    // ���ָ��ALARM�Ѿ����ã�����E_OS_STATE
    if( almId->prevAlarm != (AlarmType)0 )
    {
		OSEK_HOOK_ErrorHook(E_OS_STATE,OSServiceId_SetRelAlarm,almId) ;
	}

	// �����ж�
    OSEK_TARGET_DisableOSInt(osIntSave);

    // �����ֵת��Ϊ����ֵ
    if ((osekCounter_CounterTable[ctrId].configTable.maxallowedvalue - osekCounter_CounterTable[ctrId].currentTick) < increment )
    {
        increment -= (osekCounter_CounterTable[ctrId].configTable.maxallowedvalue - osekCounter_CounterTable[ctrId].currentTick + 1);
    }
    else
    {
        increment += osekCounter_CounterTable[ctrId].currentTick;
    }

    // ����SetAlarm����ALARM
	SetAlarm(almId,increment,cycle);

	// ���ж�
	OSEK_TARGET_EnableOSInt(osIntSave);

	// �ɹ�������E_OK
	return E_OK;

}


/*
 * @brief
 *    SetAbsAlarm�����þ���ʱ��ALARM��
 * @param		almId: ָ��ALARM���ƿ��ָ�롣
 *              start: ��tickΪ��λ�ľ�����ʼʱ��ֵ��
 *              cycle: ������ALARM������ֵ������һ���Ե�ALARM����ֵ����Ϊ0��
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns:    E_OK���ɹ���
 * <p>          E_OS_STATE:ָ����ALARM�Ѿ����á�
 * <p>          [E_OS_ID:��Ч��ALARM��]
 * <p>          [E_OS_VALUE:�������ʼʱ������ڲ����������õķ�Χ��]
 */

StatusType SetAbsAlarm(  AlarmType almId, TickType start, TickType cycle )
{
	CtrType     ctrId;
	OSEK_TARGET_OSIntSave(osIntSave) ;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������Ĳ���almId�Ƿ���Ч����Ч����E_OS_ID
	if( almId != almId->alarmId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_SetAbsAlarm,almId) ;
	}
#endif

	// ��ȡָ��ALARM����Ӧ��counter
	ctrId =  almId->configTable.ctrId;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �����ʼʱ��ֵ����counter���õ����ֵ������E_OS_VALUE
	if( start > osekCounter_CounterTable[ctrId].configTable.maxallowedvalue )
	{
		OSEK_HOOK_ErrorHook(E_OS_VALUE,OSServiceId_SetAbsAlarm,almId) ;
	}

    // ����������ALARM���������ֵ����counter���õ����ֵ�������С����ֵ������E_OS_VALUE
	if(( cycle != 0 ) && ( (cycle > osekCounter_CounterTable[ctrId].configTable.maxallowedvalue) || (cycle < osekCounter_CounterTable[ctrId].configTable.mincycle) ) )
	{
    	OSEK_HOOK_ErrorHook(E_OS_VALUE,OSServiceId_SetAbsAlarm,almId) ;
	}
#endif

    // ���ָ��ALARM�Ѿ����ã�����E_OS_STATE
	if( almId->prevAlarm != (AlarmType)0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_STATE,OSServiceId_SetAbsAlarm,almId) ;
	}

	// �����ж�
    OSEK_TARGET_DisableOSInt(osIntSave);

	// ����SetAlarm����ALARM
    SetAlarm(almId,start,cycle);

	// ���ж�
	OSEK_TARGET_EnableOSInt(osIntSave);

	// �ɹ�����ALARM������E_OK
	return E_OK;

}


/*
 * @brief
 *    CancelAlarm��ȡ�����õ�ALARM��
 * @param		almId: ָ��ALARM���ƿ��ָ�롣
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns:    E_OK���ɹ���
 * <p>          E_OS_NOFUNC:ָ����ALARMδ��ʹ�á�
 * <p>          [E_OS_ID:��Ч�����������]
 */

StatusType CancelAlarm( AlarmType almId )
{
	OSEK_TARGET_OSIntSave(osIntSave) ;

	#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �������Ĳ���almId�Ƿ���Ч����Ч����E_OS_ID
	if( almId != almId->alarmId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_CancelAlarm,almId) ;
	}
	#endif

	// �����ж�
	OSEK_TARGET_DisableOSInt(osIntSave);

	// ���ָ����ALARMδ��ʹ�ã�����E_OS_NOFUNC
	if( almId->prevAlarm == (AlarmType)0 )
	{
		OSEK_TARGET_EnableOSInt(osIntSave);
		OSEK_HOOK_ErrorHook(E_OS_NOFUNC,OSServiceId_CancelAlarm,almId) ;
	}

    // ��ָ����ALARM���ƿ����ʹ�õ�ALARM������ȥ��
	(almId->prevAlarm)->nextAlarm = almId->nextAlarm;
    if ( almId->nextAlarm != (AlarmType)0 )
    {
        (almId->nextAlarm)->prevAlarm = almId->prevAlarm;
    }

    // ��ָ����ALARM����Ϊδʹ�õ�
	almId->prevAlarm = (AlarmType)0 ;

	// ���ж�
	OSEK_TARGET_EnableOSInt(osIntSave);

	// �ɹ���ָ����ALARMȡ��������E_OK
	return E_OK;

}


/*
 * @brief
 *    NotifyAlarm������ALARM�����������¼��򼤻������ڲ���������
 * @param		almId: ָ��ALARM���ƿ��ָ�롣
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns: �����¼��򼤻�����ķ���ֵ��
 */

static StatusType NotifyAlarm(AlarmType almId)
{
	T_OSEK_TASK_ControlBlock *tcbPtr;

	// ͨ��almId��ȡ��Ӧ��������ƿ�
	tcbPtr = &osekTask_TaskTable[almId->configTable.taskId];

#if defined(CONFIG_OSEK_SYSTEM_ET) && defined(CONFIG_OSEK_ALARM_EVENT)
	// �����Ҫ�����¼���������¼�����������¼����ܣ������ؽ��
	if( almId->configTable.setEvent)
	{
 		return osekEvent_SetEvent(tcbPtr,almId->configTable.setEvent);
	}
	else
#endif
	// �������Ҫ�����¼����򼤻����񣬲����ؽ��
	{
		return osekTask_ActiveTask(tcbPtr);
	}

}


/*
 * @brief
 *    osekAlarm_Check1�����ָ��counter��ALARM���������㴥��ʱ��������ALARM������Ӧ�Ĵ���callback�������¼��򼤻����񣩣�
 *                     ���ڷ�����ALARM�����������ȥ������������ALARM��������һ�δ�����ʱ�䡣���ڲ�������
 * @param		ctrId:counter ID�š�
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns: �ޡ�
 */

void osekAlarm_Check1( CtrType ctrId )
{
    AlarmType   almId;
    OSBYTE      dispatchFlag;
    T_OSEK_COUNTER_ControlBlock *ctrPtr;
    StatusType  status;

	// ��ʼ�����ȱ�־
    dispatchFlag = 0;
	// ��ȡָ���������Ŀ��ƿ�
    ctrPtr = &osekCounter_CounterTable[ctrId];

    almId = ctrPtr->alarm;

	// ����ָ��counter��ALARM����
    while (almId != (AlarmType)0 )
    {
		// ���alarm�Ƿ��ڲ�����Ӧ����
		status = osekAlarm_Check2(almId, ctrPtr);
	    // �ж�status��ֵ�������Ҫ���ȣ������õ��ȱ�־Ϊ1
        if( status == OSEK_TASK_NEED_DISPATCH )
		{
			dispatchFlag = 1;
		}
		// �õ������е���һ��ALARM
        almId = almId->nextAlarm;
    }

	// ������ȱ�־��Ϊ0����ʵʩ����
    if( dispatchFlag != 0 )
    {
    	osekTask_Dispatch();
    }

}


/*
 * @brief
 *    osekAlarm_Check2�����ָ���ĵ���ALARM��������㴥��ʱ���������Ӧ�Ĵ���callback�������¼��򼤻����񣩣�
 *                     ���ڷ�����ALARM�����������ȥ������������ALARM��������һ�δ�����ʱ�䡣���ڲ�������
 * @param
 * @param[in]	almId:ALARM ID��,ʵ��Ϊָ��ALARM���ƽṹ��ָ�룻
 *              ctrPtr:���ALARM�������COUNTER���ƿ�ָ�롣
 * @param[out]	�ޡ�
 * @returns: status: �Ƿ���Ҫ���ȡ�
 */
StatusType osekAlarm_Check2(AlarmType almId, T_OSEK_COUNTER_ControlBlock *ctrPtr )
{
    StatusType  status;

	status = (StatusType)0;

	// ���ALARM����
	if ( almId->expirationTick == ctrPtr->currentTick )
    {
#if defined(CONFIG_OSEK_ALARM_CALLBACK)
		// ���������callback�������������
        if( almId->configTable.callBack )
        {
            almId->configTable.callBack();
        }
        // ���������¼��򼤻�����
		else
        {
#endif
           status = NotifyAlarm( almId );

#if defined(CONFIG_OSEK_ALARM_CALLBACK)
        }
#endif

		// ����Ƿ�����ALARM�������������ȥ��
        if (almId->periodTick == 0 )
        {
				(almId->prevAlarm)->nextAlarm = almId->nextAlarm;
			    if ( almId->nextAlarm != (AlarmType)0 )
			    {
			        (almId->nextAlarm)->prevAlarm = almId->prevAlarm;
			    }
		    // ��ָ����ALARM����Ϊδʹ�õ�
			almId->prevAlarm = (AlarmType)0;
        }
        // �������������ALARM��������������һ�δ�����ʱ��
		else
        {
            almId->expirationTick = ctrPtr->currentTick + almId->periodTick;

            if (almId->expirationTick > ctrPtr->configTable.maxallowedvalue )
            {
                almId->expirationTick -= (ctrPtr->configTable.maxallowedvalue + 1);
            }
        }
    }

	return status;
}


/*
 * @brief
 *    osekAlarm_Initialize������ALARM������Ϣ��ȶ�ALARM���ƿ���г�ʼ�����ڲ���������
 * @param		�ޡ�
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns: �ޡ�
 */
// �ú�������������Զ�����ALARMʧ�ܣ�Ӧ�з���ֵ��
void osekAlarm_Initialize( void )
{
	int i;
	//StatusType status;

	// ��ʼ��ALARM���ƿ��
	//memset((void*)osekAlarm_AlarmTable,0,sizeof(osekAlarm_AlarmTable));

	for( i = 0; i < CONFIG_OSEK_ALARM_NUMBER; i++)
	{
		osekAlarm_AlarmTable[i].configTable = osekConfig_AlarmTable[i];

		#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
		osekAlarm_AlarmTable[i].alarmId = &osekAlarm_AlarmTable[i];
		#endif

	}

#if defined(CONFIG_OSEK_ALARM_AUTO_NUMBER)
	// �������Զ�������ALARM
	for( i = 0; i < CONFIG_OSEK_ALARM_AUTO_NUMBER; i++)
	{

#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
        if((osekConfig_AutoAlarmTable[i].autoStart & (1 << osekExecution_CurrentAppMode)) != 0 )
		{
#endif  /* (CONFIG_OSEK_SYSTEM_APPMODES > 1) */

			SetAbsAlarm( osekConfig_AutoAlarmTable[i].alarmId, osekConfig_AutoAlarmTable[i].startTick, osekConfig_AutoAlarmTable[i].periodTick );

#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
		}
#endif  /* (CONFIG_OSEK_SYSTEM_APPMODES > 1) */

	}

#endif  /* defined(CONFIG_OSEK_ALARM_AUTO_NUMBER) */

}

#endif /* #if defined(CONFIG_OSEK_ALARM) */

