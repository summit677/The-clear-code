/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekTurboConfig.h,v $
 * Revision 1.0  2008/03/24 13:11:00
 * �����ļ�
*/

/*
 * @file 	osekTurboConfig.h
 * @brief
 *	<li>���ܣ���OSEKTurbo�����ú궨��ת��ΪDeltaOSEK����Ҫ�����ú궨�塣</li>
 * @author
 * @date 	2008-03-24
 * <p>���ţ�
 */


#ifndef _OSEK_TURBO_CONFIG_H
#define _OSEK_TURBO_CONFIG_H


/**************************** ���ò��� *********************************/


/**************************** �������� *********************************/


/**************************** ���岿�� *********************************/

// ϵͳ���ò���

#if defined(OSBCC1) || defined(OSBCC2)  // ϵͳ��ֻ�����л�������
#define CONFIG_OSEK_SYSTEM_BT
#endif

#if defined(OSECC1) || defined(OSECC2) // ϵͳ�������л����������չ����
#define CONFIG_OSEK_SYSTEM_ET
#endif

#if defined(OSBCC1) || defined(OSECC1) // ϵͳ��ֻ����һ�����ȼ��������һ������
#define CONFIG_OSEK_SYSTEM_BP
#endif

#if defined(OSBCC2) || defined(OSECC2)	// ϵͳ������һ�����ȼ����ж������������������񱻶�μ���
#define CONFIG_OSEK_SYSTEM_EP
#define CONFIG_OSEK_SYSTEM_MACTIVE
#endif


#if defined(OSEXTSTATUS) // ����ϵͳ����չ��Ϣ����
#define CONFIG_OSEK_SYSTEM_EXTSTATUS
#endif


#define CONFIG_OSEK_SYSTEM_APPMODES  OSNAPPMODES	// Ӧ��ģʽ��


#define CONFIG_OSEK_SYSTEM_RTI_LEVEL  OSORTIDEBUGLEVEL	// ���Լ���



// �������ò���

#if defined(OSNOPREEMPT) // ϵͳ��ֻ�з���ռ������
#define CONFIG_OSEK_TASK_NOPREEMPT
#endif

#if defined(OSMIXPREEMPT) // ϵͳ���з���ռ����ռ������
#define CONFIG_OSEK_TASK_MIXPREEMPT
#endif

#if defined(OSFULLPREEMPT) // ϵͳ�ж���������ռ������
#define CONFIG_OSEK_TASK_FULLPREEMPT
#endif

#if defined(OSEXTPRIORS) // ����֧��64�����ȼ������δ���������֧��32�����ȼ�
#define CONFIG_OSEK_TASK_EXTPRIORS
#define CONFIG_OSEK_TASK_PRIORITY_NUMBER 64
#else
#define CONFIG_OSEK_TASK_PRIORITY_NUMBER 32
#endif


#define CONFIG_OSEK_TASK_NUMBER OSNTSKS	// ϵͳ�е���������
#define CONFIG_OSEK_TASK_MAX_ID (CONFIG_OSEK_TASK_NUMBER - 2)  // ������IDLE�������ڵ��������ID
#define OSEK_TASK_IDLE_ID ((OSDWORD)(CONFIG_OSEK_TASK_NUMBER - 1))	// IDLE�����ID
#define CONFIG_OSEK_TASK_TOTAL_ACTIVATE_NUMBER OSTOTALACTIVENUMBER	// ϵͳ���������񼤻��ܴ���


#if defined(OSBCC1)&&(!defined(OSEXTSTATUS))&&(!defined(OSNOFASTTERMINATE))
#error "Not Support Fast Terminate Configuration:"
#endif

#if defined(OSSTKCHECK)	// ��ջ���
#define CONFIG_OSEK_TASK_STACK_CHECK
#endif

#define CONFIG_OSEK_TASK_STACK_BOTTOM



// ��Դ���ò���

#if defined(OSRESOURCE)	// ʹ����Դ������
#define CONFIG_OSEK_RESOURCE
#endif

#if defined(OSINRES)	// ʹ�����ڲ���Դ
#define CONFIG_OSEK_RESOURCE_INTERNAL
#endif

#define CONFIG_OSEK_RESOURCE_NUMBER OSNALLRES	// ϵͳ�е���Դ��������������������Դ��



// HOOK���ò���

#if defined(OSHOOKERROR) // �û�Ҫʹ��Error hook
#define CONFIG_OSEK_HOOK_ERROR
#endif

#if defined(OSHOOKPRETASK) // �û�Ҫʹ���������ʱhook
#define CONFIG_OSEK_HOOK_PRETASK
#endif

#if defined(OSHOOKPOSTTASK) // �û�Ҫʹ�������˳�ǰhook
#define CONFIG_OSEK_HOOK_POSTTASK
#endif

#if defined(OSHOOKSTARTUP) // �û�Ҫʹ��ϵͳ������hook
#define CONFIG_OSEK_HOOK_STARTUP
#endif

#if defined(OSHOOKSHUTDOWN) // �û�Ҫʹ��ϵͳ�رյ�hook
#define CONFIG_OSEK_HOOK_SHUTDOWN
#endif

#if defined(OSHOOKSCHEDULER) // �û�Ҫʹ��ϵͳ���е�hook
#define CONFIG_OSEK_HOOK_IDLE
#endif



// �ж����ò���

#if defined(OSNOISR2)&& (!defined(OSNOISR1))	// ϵͳ��ֻ������1���ж�
#define CONFIG_OSEK_INTERRUPT_ONLY_ISR1
#endif

#if defined(OSNOISR1)&& (!defined(OSNOISR2))	// ϵͳ��ֻ������2���ж�
#define CONFIG_OSEK_INTERRUPT_ONLY_ISR2
#endif

#if (!defined(OSNOISR1))&& (!defined(OSNOISR2))	// ϵͳ�м�������1��������2���ж�
#define CONFIG_OSEK_INTERRUPT_ISR_ALL
#endif

#if defined(OSNOISR2)&& defined(OSNOISR1)	// ϵͳ��û���ж�
#define CONFIG_OSEK_INTERRUPT_ISR_NULL
#endif



// Counter��Alarm���ò���

#if defined(OSALARM)	// ʹ��ALARM����
#define CONFIG_OSEK_ALARM
#endif

#if defined(OSALMSETEVENT)	// ʹ��ALARM�������¼�����
#define CONFIG_OSEK_ALARM_EVENT
#endif

#if defined(OSALMCALLBACK)	// ʹ��ALARM�Ļص�����
#define CONFIG_OSEK_ALARM_CALLBACK
#endif

#define CONFIG_OSEK_COUNTER_NUMBER  OSNCTRS	// ϵͳ�м�����������
#define CONFIG_OSEK_ALARM_NUMBER    OSNALMS	// ϵͳALARM����
#if defined(OSNAUTOALMS)
#define CONFIG_OSEK_ALARM_AUTO_NUMBER	OSNAUTOALMS	// �Զ�������ALARM����
#endif



// �¼����ò���



// ͨ�����ò���

#if defined(OSUSEMESGRESOURCE)	// ʹ����ͨ����Դ
#define		CONFIG_OSEK_COM_USE_MESSAGE_RESOURCE
#endif

#if defined(OSUSEMESGSTATUS)	// ʹ������Ϣ״̬
#define		CONFIG_OSEK_COM_USE_MESSAGE_STATUS
#endif

// ͨ�ŷ�Χ
#if defined(LOCALMESSAGESONLY)	// ֻ���ڲ�ͨ��
#define		CONFIG_OSEK_COM_LOCALMESSAGESONLY
#endif

// ��Ϣ֪ͨ����
#if defined(OSSIGACTIVTASK)	// ��������Ϣ����ʱ��������
#define		CONFIG_OSEK_MSG_ACTIVATETASK
#endif

#if defined(OSSIGEVENT)	// ��������Ϣ����ʱ�����¼�
#define		CONFIG_OSEK_MSG_SETEVENT
#endif

#if defined(OSSIGCALLBACK)	// ��������Ϣ����ʱ�ص�����
#define		CONFIG_OSEK_MSG_CALLBACK
#endif

#if defined(OSSIGFLAG)	// ��������Ϣ����ʱ���ñ�־
#define		CONFIG_OSEK_MSG_FLAG
#endif

#if defined (CONFIG_OSEK_COM_LOCALMESSAGESONLY)

// ����Ϣ����, ����COM�������Ŀ��غ�
#define CONFIG_OSEK_COM_NUMBER_OF_MESSAGES		OSNMSGS

// ��־����, ���ÿ��ƿ����Ƿ��б�־���ԣ��Լ�����֪ͨ������صķ���
#define CONFIG_OSEK_COM_NUMBER_OF_FLAGS			OSNFLAGS

// ��������Ϣ����, ���ü��ÿ��ƿ�ṹ
#define CONFIG_OSEK_COM_NUMBER_OF_QUEUED_MESSAGES	 OSNQUEMSGS

#endif  /* CONFIG_OSEK_COM_LOCALMESSAGESONLY */



// �������ò���

#define CONFIG_OSEK_COMPILER_GCC



// Ŀ������ò���

//#define OSMPC555
#define OSPC386		// ��ʱʹ��PC386


#if defined(OSFLOATINGPOINT)	// ʹ���˸��㴦��
#define CONFIG_OSEK_TARGET_FLOAT
#endif

// PowerPCĿ���ϵ��
#if defined(OSMPC555)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC555
#endif

#if defined(OSMPC561)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC561
#endif

#if defined(OSMPC562)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC562
#endif

#if defined(OSMPC563)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC563
#endif

#if defined(OSMGT5100)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MGT5100
#endif

#if defined(OSMGT5200)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MGT5200
#endif

#if defined(OSMPC5500)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC5500
#endif


// X86Ŀ���ϵ��
#if defined(OSPC386)
#define CONFIG_OSEK_TARGET_X86
#define CONFIG_OSEK_TARGET_PC386
#endif


// ARMĿ���ϵ��
#if defined(OSARM44b0X)
#define CONFIG_OSEK_TARGET_ARM
#define CONFIG_OSEK_TARGET_ARM44b0X
#endif


// MIPSĿ���ϵ��
#if defined(OSMIPSR4000)
#define CONFIG_OSEK_TARGET_MIPS
#define CONFIG_OSEK_TARGET_MIPSR4000
#endif




// ��Ҫת���ĺ�

#define OSTASKENTRY  T_OSEK_TASK_Entry
#define OSISRCBTYPE  OSDWORD
#define OSTSK        T_OSEK_TASK_ConfigTable

#define OSTSKACTIVATE   OSEK_TASK_ACTIVE
#define OSTSKNONPREEMPT OSEK_TASK_NONPREEMPT
#define OSTSKEXTENDED   OSEK_TASK_EXTENDED
#define OSGETTOPOFSTACK OSEK_TASK_GETTOPOFSTACK

#define OSHOOKENTRY  T_OSEK_ALARM_CallBackEntry
#define OSMSG        T_OSEK_MESSAGE_ConfigTable

/* ������OSEKturbo���� */
#define __rom       const               /* ROM�������� */
#define __ram                           /* RAM�������� */



// ��OSEKturbo�����ñ�ͨ�����滻��ʽת��Ϊ�µı�������
#define OsTaskCfgTable osekConfig_TaskTable
#define OsTaskEntry osekTask_EntryTable
#define OsIsr osekInterrupt_IsrEntryTable

#define OsMsg osekConfig_MsgTable


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif

