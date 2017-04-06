/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osapi.h,v $
 * Revision 1.0  2008/03/04 10:34:00
 * �����ļ�
*/

/**
 * @file 	osapi.h
 * @brief
 *	<li>���ܣ����ļ���Ϊͷ�ļ�ʹ�õ�ͳһ�ⲿͷ�ļ���������˲���ϵͳ������ɲ��ֵ���ͷ�ļ���</li>
 * @author
 * @date 	2008-03-04
 * <p>���ţ�
 */


#ifndef _OS_API_H
#define _OS_API_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_OSEK_OCC 
#include "osekOccConfig.h"
#else
#include "osekTurboConfig.h"
#endif


// �������ϵͳAPI���õķ���״̬
/// ����ϵͳAPI���÷���״̬ 0�������ɹ�������OSEK�ĸ��������
#define E_OK  			( (StatusType)0 )

// 1...16��OS���ֵĴ���������
/// ����ϵͳAPI���÷���״̬ :����Ȩ�޴���
#define E_OS_ACCESS 	( (StatusType)1 )
/// ����ϵͳAPI���÷���״̬ :���ò�δ���
#define E_OS_CALLEVEL 	( (StatusType)2 )
/// ����ϵͳAPI���÷���״̬ :����ID����
#define E_OS_ID 		( (StatusType)3 )
/// ����ϵͳAPI���÷���״̬ :������Χ����
#define E_OS_LIMIT 		( (StatusType)4 )
/// ����ϵͳAPI���÷���״̬ :û�д˹���
#define E_OS_NOFUNC 	( (StatusType)5 )
/// ����ϵͳAPI���÷���״̬ :��Դδ�ͷ�
#define E_OS_RESOURCE 	( (StatusType)6 )
/// ����ϵͳAPI���÷���״̬ :״̬����
#define E_OS_STATE 		( (StatusType)7 )
/// ����ϵͳAPI���÷���״̬ :��ֵ����
#define E_OS_VALUE 		( (StatusType)8 )

// 32...63��COM���ֵĴ���������
/// ����ϵͳAPI���÷���״̬ :��Ϣ����æ��
#define E_COM_BUSY 		( (StatusType)(1 + 32) )
/// ����ϵͳAPI���÷���״̬ :��Ч����Ϣ����
#define E_COM_ID 		( (StatusType)(2 + 32) )
/// ����ϵͳAPI���÷���״̬ :��Ϣ���������
#define E_COM_LIMIT 	( (StatusType)(3 + 32) )
/// ����ϵͳAPI���÷���״̬ :��Ϣ��������
#define E_COM_LOCKED 	( (StatusType)(4 + 32) )
/// ����ϵͳAPI���÷���״̬ :��Ϣ����������Ϣ
#define E_COM_NOMSG 	( (StatusType)(5 + 32) )

// 17...31: ʵ���Զ�������
/// ����ϵͳAPI���÷���״̬ :�ڲ���ջ���
#define E_OS_SYS_STACK      ( (StatusType)17 )
/// ����ϵͳAPI���÷���״̬ :����ȷ�Ĺ��ܵ���˳��
#define E_OS_SYS_ORDER      ( (StatusType)18 )
/// ����ϵͳAPI���÷���״̬ :����ջ���
#define E_OS_SYS_MAINSTACK  ( (StatusType)19 )
/// ����ϵͳAPI���÷���״̬ :�ж�ջ���
#define E_OS_SYS_ISRSTACK   ( (StatusType)20 )


/// ��Ч������ID
#define INVALID_TASK ((OSDWORD)0xFFFFFFFF)

#define NULLPTR  ((void *)0)


// ���������������
/// OSBYTE���Ͷ���
typedef unsigned char       OSBYTE;
/// OSBYTEPTR���Ͷ���
typedef unsigned char      *OSBYTEPTR;
/// OSWORD���Ͷ���
typedef unsigned short      OSWORD;
/// OSWORDPTR���Ͷ���
typedef unsigned short      *OSWORDPTR;
/// OSDWORD���Ͷ���
typedef unsigned long        OSDWORD;
///// ����M0��32λ�Ĵ����������Զ���CPU״̬�Ĵ����Ĵ�СΪ˫��
//typedef OSDWORD        OS_CPU_SR;

typedef unsigned char       OSCARDINAL;
/// OSSIGNEDDWORD���Ͷ���
typedef signed long          OSSIGNEDDWORD;
/// OSPRIOTYPE���Ͷ���
typedef signed short         OSPRIOTYPE;
/// OSTASKTYPE���Ͷ���
typedef OSDWORD             OSTASKTYPE;

/// AppModeType���Ͷ���
typedef OSBYTE			AppModeType;
/// StatusType���Ͷ���
typedef unsigned char   StatusType;

/// TaskType���Ͷ���
typedef OSDWORD			TaskType;
/// TaskRefType���Ͷ���
typedef TaskType		*TaskRefType;
/// TaskStateType���Ͷ���
typedef OSBYTE			TaskStateType;
/// TaskStateRefType���Ͷ���
typedef TaskStateType	*TaskStateRefType;

/// EventMaskType���Ͷ���
typedef OSDWORD			EventMaskType;
/// EventMaskRefType���Ͷ���
typedef EventMaskType	*EventMaskRefType;

typedef OSDWORD			IntMaskType;

/// OSCALLBACK���Ͷ���
typedef void          (*OSCALLBACK)( void );


// COM�ض����������Ͷ���
/// FlagType���Ͷ���
typedef unsigned char      *FlagType;
/// FlagValue���Ͷ���
typedef unsigned char       FlagValue;
/// ��Ϣ����ID�����Ͷ���
typedef OSBYTE              OSMSGIDTYPE;
/// AccessNameRef���Ͷ��壺��Ϣ������ĵ�ַ
typedef void*               AccessNameRef;
/// ��־δ������
#if defined(CONFIG_OSEK_TARGET_PPC)
#define FALSE         ((FlagValue)0)
/// ��־������
#define TRUE          ((FlagValue)1)
#endif


#define TASK( TaskName ) void Func##TaskName( void )
/// T_OSEK_TASK_Entry���Ͷ���
typedef void (*T_OSEK_TASK_Entry)( void );  // ���������


/// �����������Ķ���
#define DeclareTask(TaskID)     TASK(TaskID)
/// �жϴ����������Ķ���
#define DeclareISR(isrName)     void isrName(void)

// ��Դ������ƽṹ��������Ͷ���
/// ResourceType���Ͷ���
typedef struct T_OSEK_RESOURCE_ControlBlock_Struct *ResourceType;
/// T_OSEK_RESOURCE_ControlBlock���Ͷ���
typedef struct T_OSEK_RESOURCE_ControlBlock_Struct T_OSEK_RESOURCE_ControlBlock;

/// T_OSEK_TARGET_TaskContext�����������Ľṹ�������ض���
typedef struct T_OSEK_TARGET_TaskContext_struct T_OSEK_TARGET_TaskContext;
/// T_OSEK_TARGET_ExceptionFrame��X86���쳣��ܽṹ�������ض���
typedef struct T_OSEK_TARGET_ExceptionFrame_struct T_OSEK_TARGET_ExceptionFrame;

/// T_OSEK_TASK_ControlBlock�����������ƽṹ���ͣ��ض���
typedef struct T_OSEK_TASK_ControlBlock_Struct T_OSEK_TASK_ControlBlock;
typedef struct T_OSEK_TASK_ReadyBlock_Struct T_OSEK_TASK_ReadyBlock;

/// T_OSEK_TASK_ConfigTable���������ñ�ṹ�������ض���
typedef struct T_OSEK_TASK_ConfigTable_Struct T_OSEK_TASK_ConfigTable;

/// T_OSEK_COUNTER_ControlBlock��COUNTER������ƽṹ�������ض���
typedef struct T_OSEK_COUNTER_ControlBlock_Struct  T_OSEK_COUNTER_ControlBlock;

/// T_OSEK_COUNTER_ConfigTable��COUNTER���ñ�ṹ�������ض���
typedef struct T_OSEK_COUNTER_ConfigTable_Struct T_OSEK_COUNTER_ConfigTable;

/// T_OSEK_ALARM_ControlBlock��ALARM������ƽṹ�������ض���
typedef struct T_OSEK_ALARM_ControlBlock_Struct T_OSEK_ALARM_ControlBlock;

/// T_OSEK_ALARM_ConfigTable��ALARM���ñ�ṹ�������ض���
typedef struct T_OSEK_ALARM_ConfigTable_Struct T_OSEK_ALARM_ConfigTable;

/// T_OSEK_ALARM_AutoTypeConfigTable���Զ�����ALARM���ñ�ṹ�������ض���
typedef struct T_OSEK_ALARM_AutoTypeConfigTable_Struct T_OSEK_ALARM_AutoTypeConfigTable;

/// T_OSEK_MESSAGE_ControlBlock����Ϣ���ƽṹ�������ض���
typedef struct T_OSEK_MESSAGE_ControlBlock_Struct  T_OSEK_MESSAGE_ControlBlock;
/// MsgType���Ͷ���
typedef T_OSEK_MESSAGE_ControlBlock*        MsgType;

/// T_OSEK_MESSAGE_ConfigTable����Ϣ���ñ�ṹ�������ض���
typedef struct T_OSEK_MESSAGE_ConfigTable_Struct  T_OSEK_MESSAGE_ConfigTable;


/// TickType���Ͷ���
typedef OSDWORD             TickType;
/// TickRefType���Ͷ���
typedef TickType*           TickRefType;

/// CtrType��Counter ID�����Ͷ���
typedef unsigned char       CtrType;

/// CtrInfoType��Counter���Լ�������Ϣ�������ض���
typedef T_OSEK_COUNTER_ConfigTable     CtrInfoType;
// CtrInfoRefType��ָ��Counter������Ϣ��ָ�룩���Ͷ���
typedef CtrInfoType*        CtrInfoRefType;

// ���ݲ��Լ���ext_bcc1_full_alarm_t2�������ӵ�
/// �����ص�����ԭ��
#define ALARMCALLBACK(alarmCallback)  void alarmCallback( void )
/// ALARM�ص�����������Ͷ���
typedef void          (*T_OSEK_ALARM_CallBackEntry)( void );

/// AlarmType��ָ��ALARM���ƿ��ָ�룩���Ͷ���
typedef T_OSEK_ALARM_ControlBlock*            AlarmType;
/// AlarmBaseType��Counter���ñ���Ϣ�����Ͷ���
typedef T_OSEK_COUNTER_ConfigTable            AlarmBaseType;
/// AlarmBaseRefType��Counter���ñ�����ã����Ͷ���
typedef AlarmBaseType*      AlarmBaseRefType;


/// OSSERVICEIDTYPE���Ͷ���
typedef OSBYTE  OSSERVICEIDTYPE;

#if defined(CONFIG_OSEK_SYSTEM_GETSERVICEID)

#define OSErrorGetServiceId()       (osekHook_ServiceId)

// OSEK OS �������ʶ
#define OSSYSTEMSERVICEIDBASE       0x00    // ����ϵͳִ�п��Ʒ�����
#define OSTASKSERVICEIDBASE         0x10    // ������������
#define OSISRSERVICEIDBASE          0x20    // �жϴ��������
#define OSRESOURCESERVICEIDBASE     0x30    // ��Դ���������
#define OSEVENTSERVICEIDBASE        0x40    // �¼����Ʒ�����
#define OSMESSAGESERVICEIDBASE      0x50    // ��Ϣͨ�ŷ�����
#define OSCOUNTERSERVICEIDBASE      0x70    // counter������
#define OSALARMSERVICEIDBASE        0x80    // alarm������
#define OSHOOKSERVICEIDBASE         0x90    // hook������


#define OSServiceId_NoService                   (OSSERVICEIDTYPE)0xFF

// ����ϵͳִ�п��Ʒ���
#define OSServiceId_StartOS                     (OSSERVICEIDTYPE)( OSSYSTEMSERVICEIDBASE + 0x02 )
#define OSServiceId_ShutdownOS                  (OSSERVICEIDTYPE)( OSSYSTEMSERVICEIDBASE + 0x04 )
#define OSServiceId_GetActiveApplicationMode    (OSSERVICEIDTYPE)( OSSYSTEMSERVICEIDBASE + 0x06 )
// ����������
#define OSServiceId_ActivateTask                (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x00 )
#define OSServiceId_TerminateTask               (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x02 )
#define OSServiceId_ChainTask                   (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x04 )
#define OSServiceId_Schedule                    (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x06 )
#define OSServiceId_GetTaskID                   (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x08 )
#define OSServiceId_GetTaskState                (OSSERVICEIDTYPE)( OSTASKSERVICEIDBASE + 0x0A )
// �жϴ������
#define OSServiceId_ResumeAllInterrupts         (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x00 )
#define OSServiceId_SuspendAllinterrupts        (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x02 )
#define OSServiceId_ResumeOSInterrupts          (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x04 )
#define OSServiceId_SuspendOSinterrupts         (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x06 )
#define OSServiceId_EnableAllInterrupts         (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x08 )
#define OSServiceId_DisableAllInterrupts        (OSSERVICEIDTYPE)( OSISRSERVICEIDBASE + 0x0A )
// ��Դ�������
#define OSServiceId_GetResource                 (OSSERVICEIDTYPE)( OSRESOURCESERVICEIDBASE + 0x00 )
#define OSServiceId_ReleaseResource             (OSSERVICEIDTYPE)( OSRESOURCESERVICEIDBASE + 0x02 )
// �¼����Ʒ���
#define OSServiceId_SetEvent                    (OSSERVICEIDTYPE)( OSEVENTSERVICEIDBASE + 0x00 )
#define OSServiceId_ClearEvent                  (OSSERVICEIDTYPE)( OSEVENTSERVICEIDBASE + 0x02 )
#define OSServiceId_GetEvent                    (OSSERVICEIDTYPE)( OSEVENTSERVICEIDBASE + 0x04 )
#define OSServiceId_WaitEvent                   (OSSERVICEIDTYPE)( OSEVENTSERVICEIDBASE + 0x06 )
// ��Ϣͨ�ŷ���
#define OSServiceId_SendMessage                 (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x00 )
#define OSServiceId_ReceiveMessage              (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x02 )
#define OSServiceId_GetMessageResource          (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x04 )
#define OSServiceId_ReleaseMessageResource      (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x06 )
#define OSServiceId_GetMessageStatus            (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x08 )
#define OSServiceId_StartCOM                    (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x0A )
#define OSServiceId_StopCOM                     (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x0C )
#define OSServiceId_InitCOM                     (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x0E )
#define OSServiceId_CloseCOM                    (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x10 )
#define OSServiceId_ReadFlag                    (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x12 )
#define OSServiceId_ResetFlag                   (OSSERVICEIDTYPE)( OSMESSAGESERVICEIDBASE + 0x14 )
// counter����
#define OSServiceId_InitCounter                 (OSSERVICEIDTYPE)( OSCOUNTERSERVICEIDBASE + 0x00 )
#define OSServiceId_CounterTrigger              (OSSERVICEIDTYPE)( OSCOUNTERSERVICEIDBASE + 0x02 )
#define OSServiceId_GetCounterValue             (OSSERVICEIDTYPE)( OSCOUNTERSERVICEIDBASE + 0x04 )
#define OSServiceId_GetCounterInfo              (OSSERVICEIDTYPE)( OSCOUNTERSERVICEIDBASE + 0x06 )
// alarm����
#define OSServiceId_GetAlarmBase                (OSSERVICEIDTYPE)( OSALARMSERVICEIDBASE + 0x00 )
#define OSServiceId_GetAlarm                    (OSSERVICEIDTYPE)( OSALARMSERVICEIDBASE + 0x02 )
#define OSServiceId_SetRelAlarm                 (OSSERVICEIDTYPE)( OSALARMSERVICEIDBASE + 0x04 )
#define OSServiceId_SetAbsAlarm                 (OSSERVICEIDTYPE)( OSALARMSERVICEIDBASE + 0x06 )
#define OSServiceId_CancelAlarm                 (OSSERVICEIDTYPE)( OSALARMSERVICEIDBASE + 0x08 )
// hook����
#define OSServiceId_ErrorHook                   (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x00 )
#define OSServiceId_PreTaskHook                 (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x02 )
#define OSServiceId_PostTaskHook                (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x04 )
#define OSServiceId_StartupHook                 (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x06 )
#define OSServiceId_ShutdownHook                (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x08 )
#define OSServiceId_IdleLoopHook                (OSSERVICEIDTYPE)( OSHOOKSERVICEIDBASE + 0x0A )

#endif


#if defined(CONFIG_OSEK_SYSTEM_PARAMETERACCESS)
// ��ȡ����ĵ�һ�������ĺ�
// ����������
#define OSError_StartOS_Mode()              ((AppModeType)osekHook_ObjId)
#define OSError_ActivateTask_TaskID()      ( (TaskType)osekHook_ObjId)
#define OSError_ChainTask_TaskID()          ((TaskType)osekHook_ObjId)
#define OSError_GetTaskState_TaskID()      ( (TaskType)osekHook_ObjId)
// ��Դ�������
#define OSError_GetResource_ResID()         ((ResourceType)osekHook_ObjId)
#define OSError_ReleaseResource_ResID()    ( (ResourceType)osekHook_ObjId)
// �¼����Ʒ���
#define OSError_SetEvent_TaskID()           ((TaskType)osekHook_ObjId)
#define OSError_GetEvent_TaskID()           ((TaskType)osekHook_ObjId)
// ��Ϣͨ�ŷ���
#define OSError_SendMessage_Message()      ( (MsgType)osekHook_ObjId)
#define OSError_ReceiveMessage_Message()   ( (MsgType)osekHook_ObjId)
#define OSError_GetMessageResource_Message()       ( (MsgType)osekHook_ObjId)
#define OSError_ReleaseMessageResource_Message()   ( (MsgType)osekHook_ObjId)
// alarm ����
#define OSError_GetAlarmBase_AlarmID()      ((AlarmType)osekHook_ObjId)
#define OSError_GetAlarm_AlarmID()          ((AlarmType)osekHook_ObjId)
#define OSError_SetRelAlarm_AlarmID()       ((AlarmType)osekHook_ObjId)
#define OSError_SetAbsAlarm_AlarmID()       ((AlarmType)osekHook_ObjId)
#define OSError_CancelAlarm_AlarmID()       ((AlarmType)osekHook_ObjId)
// counter����
#define OSError_InitCounter_CounterID()     ((CtrType)osekHook_ObjId)
#define OSError_CounterTrigger_CounterID()  ((CtrType)osekHook_ObjId)
#define OSError_GetCounterValue_CounterID() ((CtrType)osekHook_ObjId)
#define OSError_GetCounterInfo_CounterID()  ((CtrType)osekHook_ObjId)

#endif  /* defined(CONFIG_OSEK_SYSTEM_PARAMETERACCESS) */

// ������������ģ���ͷ�ļ�
/// ����Ŀ��ƽ̨���ͷ�ļ�
#include "osekTarget.h"
///	�����жϹ���ģ��ͷ�ļ�
#include "osekInterrupt.h"
/// ����HOOK����ģ��ͷ�ļ�
#include "osekHook.h"
/// �����������ģ��ͷ�ļ�
#include "osekTask.h"
/// ������Դ����ģ��ͷ�ļ�
#include "osekResource.h"
/// ����ϵͳִ�й���ģ��ͷ�ļ�
#include "osekExecution.h"
/// ��������������ģ��ͷ�ļ�
#include "osekCounter.h"
///	������������ģ��ͷ�ļ�
#include "osekAlarm.h"
///	�����¼�����ģ��ͷ�ļ�
#include "osekEvent.h"
/// �������Թ���ģ��ͷ�ļ�
#include "osekDebug.h"
///	������Ϣ����ģ��ͷ�ļ�
#include "osekMessage.h"

#ifdef __cplusplus
}
#endif


#endif

