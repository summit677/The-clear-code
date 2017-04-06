/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekCounter.c,v $
 * Revision 1.0  2008/03/29 14:31:00
 * �����ļ���
 */

/*
 * @file 	osekCounter.c
 * @brief
 *	<li>���ܣ�ʵ��Counter�Ĺ���</li>
 * @author
 * @date 	2008-03-29
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"
#include <string.h>

#if defined(CONFIG_OSEK_COUNTER)

/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

// ȫ�ֱ���
// COUNTER���ƿ��
T_OSEK_COUNTER_ControlBlock osekCounter_CounterTable[CONFIG_OSEK_COUNTER_NUMBER];


/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    InitCounter����ʼ��COUNTER�ļ���ֵ��
 * @param
 * @param[in]	ctrId��COUNTER��ID�š�
 *          	value��COUNTER�ļ���ֵ��
 * @param[out]  �ޡ�
 * @returns:    E_OK�� �ɹ���
 * <p>          [E_OS_ID:��Ч��COUNTER ID�š�]
 * <p>          [E_OS_VALUE:�����valueֵ������Χ��]
 * <p>          [E_OS_CALLEVEL:���ж��е����˴˺�����]
 */

StatusType InitCounter( CtrType ctrId, TickType value )
{

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// ���COUNTER ID������Χ������E_OS_ID
	if( ctrId > (CONFIG_OSEK_COUNTER_NUMBER - 1) )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_InitCounter,ctrId) ;
	}

	// �������ļ���ֵ�������õ����ֵ������E_OS_VALUE
	if( value > osekCounter_CounterTable[ctrId].configTable.maxallowedvalue )
	{
		OSEK_HOOK_ErrorHook(E_OS_VALUE,OSServiceId_InitCounter,ctrId) ;
	}

	// ������ж��е��ô˺���������E_OS_CALLEVEL
	if( osekInterrupt_NestedLevl != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_CALLEVEL,OSServiceId_InitCounter,ctrId) ;
	}
#endif

	// ������ļ���ֵ����COUNTER�ĵ�ǰ����ֵ
	osekCounter_CounterTable[ctrId].currentTick = value ;

	// �ɹ�������E_OK
	return E_OK;

}


/*
 * @brief
 *    GetCounterValue����ȡָ�� COUNTER �ļ���ֵ��
 * @param
 * @param[in]	ctrId��COUNTER��ID�š�
 * @param[out]	ticks��COUNTER ����ֵ���������á�
 * @returns:    E_OK�� �ɹ���
 * <p>          [E_OS_ID:��Ч��COUNTER ID�š�]
 */

StatusType GetCounterValue( CtrType ctrId, TickRefType ticks )
{
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// ���COUNTER ID������Χ������E_OS_ID
	if( ctrId > (CONFIG_OSEK_COUNTER_NUMBER - 1) )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetCounterValue,ctrId) ;
	}
#endif

	// ��ȡָ���������ĵ�ǰ����ֵ�����������
	*ticks =  osekCounter_CounterTable[ctrId].currentTick ;

	return E_OK;

}


/*
 * @brief
 *    CounterTrigger������ָ����COUNTER��
 * @param
 * @param[in]	ctrId��COUNTER �� ID�š�
 * @param[out]	�ޡ�
 * @returns:    E_OK�� �ɹ���
 * <p>          [E_OS_ID:��Ч��COUNTER ID�š�]
 */

StatusType CounterTrigger( CtrType ctrId )
{
	T_OSEK_COUNTER_ControlBlock * ctrPtr;
	OSEK_TARGET_OSIntSave( osIntSave ) ;

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// ���ʹ������չ״̬���ж�COUNTER ID�Ƿ񳬳���Χ�����Ƿ���E_OS_ID
	if( ctrId > (CONFIG_OSEK_COUNTER_NUMBER - 1) )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_CounterTrigger,ctrId) ;
	}
#endif

	OSEK_TARGET_DisableOSInt(osIntSave);

	ctrPtr = &(osekCounter_CounterTable[ctrId]);
	// ���COUNTER ��ǰ����ֵ�������õ�������ֵ���򽫼���ֵ��λ��0
    if( ctrPtr->currentTick == ctrPtr->configTable.maxallowedvalue )
    {
        ctrPtr->currentTick = 0;
    }
	// ����COUNTER ��ǰ����ֵ��1
    else
    {
        ctrPtr->currentTick++;
    }

#if defined(CONFIG_OSEK_ALARM)
	// ����Ƿ���ALARM ���ڲ�����Ӧ�������ûص������������¼��򼤻�����
    osekAlarm_Check1( ctrId );
#endif

    OSEK_TARGET_EnableOSInt(osIntSave);

	// �ɹ�������E_OK
	return E_OK;

}


/*
 * @brief
 *    GetCounterInfo����ȡָ�� COUNTER �Ļ�����Ϣ��
 * @param
 * @param[in]	ctrId��COUNTER ��ID�š�
 * @param[out]	info�� COUNTER ������Ϣ�ṹ�����á�
 * @returns:    E_OK�� �ɹ���
 * <p>          [E_OS_ID:��Ч�� COUNTER ID�š�]
 */

StatusType GetCounterInfo( CtrType ctrId, CtrInfoRefType info )
{
// ���ʹ������չ״̬
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// ���COUNTER ID������Χ������E_OS_ID
	if( ctrId > (CONFIG_OSEK_COUNTER_NUMBER - 1) )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetCounterInfo,ctrId) ;
	}
#endif

	// ��ȡ��������������Ϣ�����������
	*info =  osekCounter_CounterTable[ctrId].configTable ;

	// �ɹ�������E_OK
	return E_OK;

}


/*
 * @brief
 *    osekCounter_Initialize������������Ϣ��ʼ��COUNTER ���Ʊ��ڲ���������
 * @param
 * @param[in]	�ޡ�
 * @param[out]	�ޡ�
 * @returns:    �ޡ�
 */

void osekCounter_Initialize( void )
{
	int i;

	//memset((void*)osekCounter_CounterTable,0,sizeof(osekCounter_CounterTable));

	for( i = 0; i < CONFIG_OSEK_COUNTER_NUMBER; i++)
	{
		osekCounter_CounterTable[i].configTable = osekConfig_CounterTable[i];
	}

}

#endif /* #if defined(CONFIG_OSEK_COUNTER) */
