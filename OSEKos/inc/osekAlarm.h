/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekAlarm.h,v $
 * Revision 1.0  2008/03/29 12:23:00
 * �����ļ�
*/

/**
 * @file 	osekAlarm.h
 * @brief
 *	<li>���ܣ����屨������ص����ݽṹ���꣬�Լ���غ�����������</li>
 * @author
 * @date 	2008-03-29
 * <p>���ţ�
 */

/**
 * \defgroup  Alarm ����
 * Alarm����ģ��,��Ҫʵ�ֱ����Ĺ���
 */
/**@{*/
/** @name Alarm����ģ��*/
//@{


#ifndef _OSEK_ALARM_H
#define _OSEK_ALARM_H

/**************************** ���ò��� *********************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************** �������� *********************************/

// ALARM �����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    SetRelAlarm���������ʱ��ALARM��
 * @param[in]	almId: ָ��ALARM���ƿ��ָ�롣
 * @param[in]   increment: ��tickΪ��λ�������ʼʱ��ֵ��
 * @param[in]   cycle: ������ALARM������ֵ������һ���Ե�ALARM����ֵ����Ϊ0��
 * @returns     E_OK���ɹ���
 * @returns     E_OS_STATE:ָ����ALARM�Ѿ����á�
 * @returns     [E_OS_ID:��Ч��ALARM��]
 * @returns     [E_OS_VALUE:�������ʼʱ������ڲ����������õķ�Χ��]
 */
StatusType SetRelAlarm( AlarmType almId, TickType increment, TickType cycle );

/**
 * @brief
 *    GetAlarm����ȡָ��ALARM����ǰ�����ʱ�䡣
 * @param[in]	almId: ָ��ALARM���ƿ��ָ�롣
 * @param[out]	tick:  ���ʱ��ֵ�����á�
 * @returns     E_OK���ɹ���
 * @returns     E_OS_NOFUNC:ָ����ALARMδ��ʹ�á�
 * @returns     [E_OS_ID:��Ч��ALARM��]
 */
StatusType GetAlarm( AlarmType almId, TickRefType tick );

/**
 * @brief
 *    GetAlarmBase����ȡָ��ALARM�Ļ�����Ϣ��
 * @param[in]	almId��ָ��ALARM���ƿ��ָ�롣
 * @param[out]	info�� ALARM������Ϣ�ṹ�����á�
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч��ALARM��]
 */
StatusType GetAlarmBase( AlarmType almId, AlarmBaseRefType info );

/**
 * @brief
 *    SetAbsAlarm�����þ���ʱ��ALARM��
 * @param[in]	almId: ָ��ALARM���ƿ��ָ�롣
 * @param[in]   start: ��tickΪ��λ�ľ�����ʼʱ��ֵ��
 * @param[in]   cycle: ������ALARM������ֵ������һ���Ե�ALARM����ֵ����Ϊ0��
 * @returns     E_OK���ɹ���
 * @returns     E_OS_STATE:ָ����ALARM�Ѿ����á�
 * @returns     [E_OS_ID:��Ч��ALARM��]
 * @returns     [E_OS_VALUE:�������ʼʱ������ڲ����������õķ�Χ��]
 */
StatusType SetAbsAlarm(  AlarmType almId, TickType start, TickType cycle );

/**
 * @brief
 *    CancelAlarm��ȡ�����õ�ALARM��
 * @param[in]	almId: ָ��ALARM���ƿ��ָ�롣
 * @returns     E_OK���ɹ���
 * @returns     E_OS_NOFUNC:ָ����ALARMδ��ʹ�á�
 * @returns     [E_OS_ID:��Ч�����������]
 */
StatusType CancelAlarm( AlarmType almId );

// �ڲ�����
void osekAlarm_Check1(CtrType ctrId );
StatusType osekAlarm_Check2(AlarmType almId, T_OSEK_COUNTER_ControlBlock *ctrPtr );
void osekAlarm_Initialize( void );


/**************************** ���岿�� *********************************/

/// ALARM ������Ϣ��ṹ
typedef struct T_OSEK_ALARM_ConfigTable_Struct
{
	/// ��������ID
    TaskType        taskId;
// ECC ֧���¼�����
#if defined(CONFIG_OSEK_SYSTEM_ET) && defined(CONFIG_OSEK_ALARM_EVENT)
    /// ���setEvent==0 ��alarm ��������,������Ϊ�����������¼�����������ECC����²Ŵ��ڣ�
    EventMaskType   setEvent;
#endif  /*  defined(CONFIG_OSEK_SYSTEM_ET) && defined(CONFIG_OSEK_ALARM_EVENT) */

    /// ��� Counter ��ID
    CtrType         ctrId;

#if defined(CONFIG_OSEK_ALARM_CALLBACK)
    /// Alarm �ص�������ڣ���������������ALARM�ص�ʱ�Ŵ��ڣ�
    T_OSEK_ALARM_CallBackEntry     callBack;
#endif  /* defined(CONFIG_OSEK_ALARM_CALLBACK) */

}T_OSEK_ALARM_ConfigTable_Struct;

/// ALARM ���ƿ�ṹ
typedef struct T_OSEK_ALARM_ControlBlock_Struct
{
    /// �б��е���һ�� alarm
    AlarmType       nextAlarm;
    /// �б��е�ǰһ�� alarm
    AlarmType       prevAlarm;

// ���ʹ������չ״̬
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	/// ALARM ID������������������չ����״̬ʱ�Ŵ��ڣ�
	AlarmType		alarmId;
#endif

	/// ALARM �ĵ���ʱ��ֵ
	TickType        expirationTick;
	/// ������ ALARM ������ֵ
	TickType        periodTick;

	/// ALARM ��������Ϣ��
	T_OSEK_ALARM_ConfigTable configTable;
}T_OSEK_ALARM_ControlBlock_Struct;

/// ALARM �Զ�����������Ϣ��ṹ
typedef struct T_OSEK_ALARM_AutoTypeConfigTable_Struct
{
    /// ALARM ID
    AlarmType       alarmId;
    /// ALARM ��ʼʱ��ֵ
    TickType        startTick;
    /// ������ ALARM ������ֵ
    TickType        periodTick;

#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
    /// ALARM �Ƿ��Զ���������������Ӧ��ģʽ����1ʱ�Ŵ��ڣ�
    OSDWORD         autoStart;
#endif  /* (CONFIG_OSEK_SYSTEM_APPMODES > 1) */

}T_OSEK_ALARM_AutoTypeConfigTable_Struct;


#if CONFIG_OSEK_ALARM_NUMBER > 0
// ALARM ���ƿ������
extern T_OSEK_ALARM_ControlBlock osekAlarm_AlarmTable[CONFIG_OSEK_ALARM_NUMBER];
/// ALARM ������Ϣ���������ñ�����������ALARMʱ�Ŵ��ڣ�
extern T_OSEK_ALARM_ConfigTable osekConfig_AlarmTable[CONFIG_OSEK_ALARM_NUMBER];
#if defined(CONFIG_OSEK_ALARM_AUTO_NUMBER)
/// �Զ�����ALARM ��չ������Ϣ���������ñ������������Զ�����ALARMʱ�Ŵ��ڣ�
extern T_OSEK_ALARM_AutoTypeConfigTable osekConfig_AutoAlarmTable[CONFIG_OSEK_ALARM_AUTO_NUMBER];
#endif
#endif


#define DeclareAlarm(alarm)


#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
