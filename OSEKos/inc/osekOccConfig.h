/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekOccConfig.h,v $
 * Revision 1.0  2008/03/24 13:13:00
 * �����ļ�
*/

/*
 * @file 	osekOccConfig.h
 * @brief
 *	<li>���ܣ���OCC���������ú궨��ת��ΪDeltaOSEK�ڲ���Ҫ�ĺ궨�塣</li>
 * @author
 * @date 	2008-03-24
 * <p>���ţ�
 */


#ifndef _OSEK_OCC_CONFIG_H
#define _OSEK_OCC_CONFIG_H


/**************************** ���ò��� *********************************/


/**************************** �������� *********************************/


/**************************** ���岿�� *********************************/

// ϵͳ���ò���

#if defined (OCC_BCC1) || defined(OCC_BCC2)	// ϵͳ��ֻ�����л�������
#define CONFIG_OSEK_SYSTEM_BT
#endif

#if defined(OCC_ECC1) || defined(OCC_ECC2)	// ϵͳ�������л����������չ����
#define CONFIG_OSEK_SYSTEM_ET
#endif

#if defined(OCC_BCC1) || defined(OCC_ECC1)	// ϵͳ��ֻ����һ�����ȼ��������һ������
#define CONFIG_OSEK_SYSTEM_BP
#endif

#if defined(OCC_BCC2) || defined(OCC_ECC2)	// ϵͳ������һ�����ȼ����ж����������������񱻶�μ���
#define CONFIG_OSEK_SYSTEM_EP
#define CONFIG_OSEK_SYSTEM_MACTIVE
#endif


#if defined (OCC_EXTSTATUS)	// ����ϵͳ����չ��Ϣ����
#define CONFIG_OSEK_SYSTEM_EXTSTATUS
#endif


#define CONFIG_OSEK_SYSTEM_APPMODES  OCC_NAPPMODES	// Ӧ��ģʽ��


#define CONFIG_OSEK_SYSTEM_RTI_LEVEL  OCC_ORTIDEBUGLEVEL	// ���Լ���


#if defined(OCC_GETSERVICEID)	// ��ȡ����ID
#define CONFIG_OSEK_SYSTEM_GETSERVICEID
#endif

#if defined(OCC_PARAMETERACCESS)	// ��ȡ���ʲ���
#define CONFIG_OSEK_SYSTEM_PARAMETERACCESS
#endif



// �������ò���
#if defined(OCC_NOPREEMPT) // ϵͳ��ֻ�з���ռ������
#define CONFIG_OSEK_TASK_NOPREEMPT
#endif

#if defined(OCC_MIXPREEMPT) // ϵͳ���з���ռ����ռ������
#define CONFIG_OSEK_TASK_MIXPREEMPT
#endif

#if defined(OCC_FULLPREEMPT) // ϵͳ�ж���������ռ������
#define CONFIG_OSEK_TASK_FULLPREEMPT
#endif

#if defined(OCC_EXTPRIORS) // ����֧��64�����ȼ������δ���������֧��32�����ȼ�
#define CONFIG_OSEK_TASK_EXTPRIORS
#define CONFIG_OSEK_TASK_PRIORITY_NUMBER 64
#else
#define CONFIG_OSEK_TASK_PRIORITY_NUMBER 32
#endif


#define CONFIG_OSEK_TASK_NUMBER OCC_NTSKS	// ϵͳ�е���������
#define CONFIG_OSEK_TASK_MAX_ID ((OSDWORD)(CONFIG_OSEK_TASK_NUMBER - 2))  // ������IDLE�������ڵ��������ID
#define OSEK_TASK_IDLE_ID ((OSDWORD)(CONFIG_OSEK_TASK_NUMBER - 1))	// IDLE�����ID
#define CONFIG_OSEK_TASK_TOTAL_ACTIVATE_NUMBER OCC_TOTALACTIVENUMBER	// ϵͳ���������񼤻��ܴ���


#if defined(OCC_STKCHECK)	// ��ջ���
#define CONFIG_OSEK_TASK_STACK_CHECK
#endif

#define CONFIG_OSEK_TASK_STACK_BOTTOM



// ��Դ���ò���

#if defined(OCC_RESOURCE)	// ʹ����Դ������
#define CONFIG_OSEK_RESOURCE
#endif

#if defined(OCC_RESSCHEDULER)	// ʹ���˵�������Դ
#define CONFIG_OSEK_RESOURCE_SCHEDULER
#endif

#if defined(OCC_INRES)	// ʹ�����ڲ���Դ
#define CONFIG_OSEK_RESOURCE_INTERNAL
#endif

#if defined(OCC_ISRRES)	// ʹ�����ж���Դ
#define CONFIG_OSEK_RESOURCE_ISR
#endif

#define CONFIG_OSEK_RESOURCE_NUMBER OCC_NALLRES	// ϵͳ�е���Դ��������������������Դ��



// HOOK���ò���

#if defined(OCC_HOOKERROR) // �û�Ҫʹ��Error hook
#define CONFIG_OSEK_HOOK_ERROR
#endif

#if defined(OCC_HOOKPRETASK) // �û�Ҫʹ���������ʱhook
#define CONFIG_OSEK_HOOK_PRETASK
#endif

#if defined(OCC_HOOKPOSTTASK) // �û�Ҫʹ�������˳�ǰhook
#define CONFIG_OSEK_HOOK_POSTTASK
#endif

#if defined(OCC_HOOKSTARTUP) // �û�Ҫʹ��ϵͳ������hook
#define CONFIG_OSEK_HOOK_STARTUP
#endif

#if defined(OCC_HOOKSHUTDOWN) // �û�Ҫʹ��ϵͳ�رյ�hook
#define CONFIG_OSEK_HOOK_SHUTDOWN
#endif

#if defined(OCC_HOOKIDLE) // �û�Ҫʹ��ϵͳ���е�hook
#define CONFIG_OSEK_HOOK_IDLE
#endif



// �ж����ò���
#if defined(OCC_ISR1)&& (!defined(OCC_ISR2))	// ϵͳ��ֻ������1���ж�
#define CONFIG_OSEK_INTERRUPT_ONLY_ISR1
#endif

#if defined(OCC_ISR2)&& (!defined(OCC_ISR1))	// ϵͳ��ֻ������2���ж�
#define CONFIG_OSEK_INTERRUPT_ONLY_ISR2
#endif

#if defined(OCC_ISR1)&& defined(OCC_ISR2)	// ϵͳ�м�������1��������2���ж�
#define CONFIG_OSEK_INTERRUPT_ISR_ALL
#endif

#if (!defined(OCC_ISR1))&& (!defined(OCC_ISR2))	// ϵͳ��û���ж�
#define CONFIG_OSEK_INTERRUPT_ISR_NULL
#endif

#define CONFIG_OSEK_INTERRUPT_WITH_TYPE

#define CONFIG_OSEK_INTERRUPT_STACK_SIZE OCC_ISRSTACKSIZE	// �ж϶�ջ�ĳߴ�

#define CONFIG_OSEK_INTERRUPT_ISRLEVEL_NUMBER OCC_ISRLEVELNUM	// �жϼ���


// Alarm���ò���

#if defined(OCC_ALARM)	// ʹ��ALARM����
#define CONFIG_OSEK_ALARM
#endif

#if defined(OCC_ALMSETEVENT)	// ʹ��ALARM�������¼�����
#define CONFIG_OSEK_ALARM_EVENT
#endif

#if defined(OCC_ALMCALLBACK)	// ʹ��ALARM�Ļص�����
#define CONFIG_OSEK_ALARM_CALLBACK
#endif

#define CONFIG_OSEK_ALARM_NUMBER    OCC_NALMS	// ϵͳALARM����
#if defined(OCC_NAUTOALMS)
#define CONFIG_OSEK_ALARM_AUTO_NUMBER	OCC_NAUTOALMS	// �Զ�������ALARM����
#endif



// COUNTER���ò���

#if defined(OCC_COUNTER)	// ʹ���˼���������
#define CONFIG_OSEK_COUNTER
#endif

#if defined(OCC_NCTRS)	// ϵͳ�м�����������
#define CONFIG_OSEK_COUNTER_NUMBER  OCC_NCTRS
#endif


// �¼����ò���



// ͨ�����ò���

#if defined(OCC_USEMESSAGERESOURCE)	// ʹ����ͨ����Դ
#define		CONFIG_OSEK_COM_USE_MESSAGE_RESOURCE
#endif

#if defined(OCC_USEMESSAGESTATUS)	// ʹ������Ϣ״̬
#define		CONFIG_OSEK_COM_USE_MESSAGE_STATUS
#endif

// ͨ�ŷ�Χ
#if defined(OCC_LOCALMESSAGESONLY)	// ֻ���ڲ�ͨ��
#define		CONFIG_OSEK_COM_LOCALMESSAGESONLY
#endif

// ��Ϣ֪ͨ����
#if defined(OCC_SIGACTIVTASK)	// ��������Ϣ����ʱ��������
#define		CONFIG_OSEK_MSG_ACTIVATETASK
#endif

#if defined(OCC_SIGEVENT)	// ��������Ϣ����ʱ�����¼�
#define		CONFIG_OSEK_MSG_SETEVENT
#endif

#if defined(OCC_SIGCALLBACK)	// ��������Ϣ����ʱ�ص�����
#define		CONFIG_OSEK_MSG_CALLBACK
#endif

#if defined(OCC_SIGFLAG)	// ��������Ϣ����ʱ���ñ�־
#define		CONFIG_OSEK_MSG_FLAG
#endif


#if defined (CONFIG_OSEK_COM_LOCALMESSAGESONLY)

// ����Ϣ����, ����COM�������Ŀ��غ�
#define CONFIG_OSEK_COM_NUMBER_OF_MESSAGES		OCC_NMSGS

// ��־����, ���ÿ��ƿ����Ƿ��б�־���ԣ��Լ�����֪ͨ������صķ���
#define CONFIG_OSEK_COM_NUMBER_OF_FLAGS			OCC_NFLAGS

// ��������Ϣ����, ���ü��ÿ��ƿ�ṹ
#define CONFIG_OSEK_COM_NUMBER_OF_QUEUED_MESSAGES	OCC_NQUEMSGS

#endif  /* CONFIG_OSEK_COM_LOCALMESSAGESONLY */



// �������ò���

#define CONFIG_OSEK_COMPILER_GCC



// Ŀ������ò���

#if defined(OCC_FLOATINGPOINT)	// ʹ���˸��㴦��
#define CONFIG_OSEK_TARGET_FLOAT
#endif

// PowerPCĿ���ϵ��
#if defined(OCC_MPC555)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC555
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MPC561)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC561
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MPC562)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC562
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MPC563)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC563
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MGT5100)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MGT5100
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MGT5200)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MGT5200
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MPC5500)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC5500
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_MPC5554)
#define CONFIG_OSEK_TARGET_PPC
#define CONFIG_OSEK_TARGET_MPC5554
#define CONFIG_OSEK_TARGET_HARDBITMAP
#endif

#if defined(OCC_HCS12X)
#define CONFIG_OSEK_TARGET_HCS12X
#define CONFIG_OSEK_TARGET_SOFTBITMAP
#endif

#if defined(OCC_CORTEXM0)
#define CONFIG_OSEK_TARGET_CORTEXM0
#define CONFIG_OSEK_TARGET_SOFTBITMAP
#endif


// X86Ŀ���ϵ��
#if defined(OCC_PC386)
#define CONFIG_OSEK_TARGET_X86
#define CONFIG_OSEK_TARGET_PC386
#define CONFIG_OSEK_TARGET_SOFTBITMAP
#endif


// ARMĿ���ϵ��
#if defined(OCC_ARM44b0X)
#define CONFIG_OSEK_TARGET_ARM
#define CONFIG_OSEK_TARGET_ARM44b0X
#define CONFIG_OSEK_TARGET_SOFTBITMAP
#endif


// MIPSĿ���ϵ��
#if defined(OCC_MIPSR4000)
#define CONFIG_OSEK_TARGET_MIPS
#define CONFIG_OSEK_TARGET_MIPSR4000
#define CONFIG_OSEK_TARGET_SOFTBITMAP
#endif




#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif

