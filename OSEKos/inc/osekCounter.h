/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekCounter.h,v $
 * Revision 1.0  2008/03/29 11:48:00
 * �����ļ�
*/

/**
 * @file 	osekCounter.h
 * @brief
 *	<li>���ܣ������������ص����ݽṹ���꣬�Լ�������ص�������</li>
 * @author
 * @date 	2008-03-29
 * <p>���ţ�
 */

/**
 * \defgroup  Counter ������
 * ����������ģ��,��Ҫʵ�ּ������Ĺ���
 */
/**@{*/
/** @name ����������ģ��*/
//@{


#ifndef _OSEK_COUNTER_H
#define _OSEK_COUNTER_H

/**************************** ���ò��� *********************************/

#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

// COUNTER�����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    InitCounter����ʼ��COUNTER�ļ���ֵ��
 * @param[in]	ctrId��COUNTER��ID�š�
 * @param[in]	value��COUNTER�ļ���ֵ��
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч��COUNTER ID�š�]
 * @returns     [E_OS_VALUE:�����valueֵ������Χ��]
 * @returns     [E_OS_CALLEVEL:���ж��е����˴˺�����]
 */
StatusType InitCounter( CtrType ctrId, TickType value );

/**
 * @brief
 *    GetCounterValue����ȡָ�� COUNTER �ļ���ֵ��
 * @param[in]	ctrId��COUNTER��ID�š�
 * @param[out]	ticks��COUNTER ����ֵ���������á�
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч��COUNTER ID�š�]
 */
StatusType GetCounterValue( CtrType ctrId, TickRefType ticks );

/**
 * @brief
 *    CounterTrigger������ָ����COUNTER��
 * @param[in]	ctrId��COUNTER �� ID�š�
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч��COUNTER ID�š�]
 */
StatusType CounterTrigger( CtrType ctrId );

/**
 * @brief
 *    GetCounterInfo����ȡָ�� COUNTER �Ļ�����Ϣ��
 * @param[in]	ctrId��COUNTER ��ID�š�
 * @param[out]	info�� COUNTER ������Ϣ�ṹ�����á�
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч�� COUNTER ID�š�]
 */
StatusType GetCounterInfo( CtrType ctrId, CtrInfoRefType info );

// �ڲ�����
void osekCounter_Initialize( void );


/**************************** ���岿�� *********************************/

/// COUNTER ���ñ�ṹ
typedef struct T_OSEK_COUNTER_ConfigTable_Struct
{
    /// �����������ֵ
    TickType        maxallowedvalue;
    /// ת��������ÿʱ����tick��
    TickType        ticksperbase;

// ���ʹ������չ״̬
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
    /// ALARM ����С����ֵ������������������չ����״̬ʱ�Ŵ��ڣ�
    TickType        mincycle;
#endif
}T_OSEK_COUNTER_ConfigTable_Struct;

/// COUNTER ���ƿ�ṹ
typedef struct T_OSEK_COUNTER_ControlBlock_Struct
{
#if defined(CONFIG_OSEK_ALARM)
    /// ָ���Ӧ�� ALARMs ��ָ�루��������������ALARMʱ�Ŵ��ڣ�
    AlarmType           alarm;
#endif
    /// COUNTER �ĵ�ǰ����ֵ
    TickType            currentTick;
    /// COUNTER �����ñ�
    T_OSEK_COUNTER_ConfigTable    configTable;
}T_OSEK_COUNTER_ControlBlock_Struct;


#if defined(CONFIG_OSEK_COUNTER_NUMBER)
// COUNTER ���ƿ������
extern T_OSEK_COUNTER_ControlBlock_Struct osekCounter_CounterTable[];
/// COUNTER ������Ϣ���������ñ����������˼�����ʱ�Ŵ��ڣ�
extern T_OSEK_COUNTER_ConfigTable osekConfig_CounterTable[];
#endif


#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
