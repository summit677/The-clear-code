/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekEvent.h,v $
 * Revision 1.0  2008/04/04 16:33:00
 * �����ļ�
*/

/**
 * @file 	osekEvent.h
 * @brief
 *	<li>���ܣ������¼�����������ⲿAPI</li>
 * @author
 * @date 	2008-01-23
 * <p>���ţ�
 */

/**
 * \defgroup  Event �¼�
 * �¼�����ģ��,��Ҫʵ���¼��Ĺ���
 */
/**@{*/
/** @name �¼�����ģ��*/
//@{


#ifndef _OSEK_EVENT_H
#define _OSEK_EVENT_H

/**************************** ���ò��� *********************************/

#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

// �¼������ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    SetEvent�������¼���
 * @param[in]	taskId������ID�š�
 * @param[in]	mask���¼����롣
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч������ID�š�]
 * @returns     [E_OS_ACCESS:ָ����������չ����]
 * @returns     [E_OS_STATE:ָ��������SUSPEND״̬��]
 */
StatusType  SetEvent( TaskType taskId, EventMaskType mask );

/**
 * @brief
 *    ClearEvent������¼���
 * @param[in]	mask���¼����롣
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ACCESS:������������չ����]
 * @returns     [E_OS_CALLEVEL:���ж��е����˴˺�����]
 */
StatusType  ClearEvent( EventMaskType mask );

/**
 * @brief
 *    WaitEvent���ȴ��¼���
 * @param[in]	mask���¼����롣
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ACCESS:������������չ����]
 * @returns     [E_OS_RESOURCE:��������ӵ��������Դ��ϵͳ���ڹص��ȵ������]
 * @returns     [E_OS_CALLEVEL:���ж���ʹ���˴˵��á�]
 */
StatusType  WaitEvent( EventMaskType mask );

/**
 * @brief
 *    GetEvent����ȡ�¼���
 * @param[in]	taskId�������ID�š�
 * @param[out]  mask��  �¼�������������á�
 * @returns     E_OK�� �ɹ���
 * @returns     [E_OS_ID:��Ч������ID�š�]
 * @returns     [E_OS_ACCESS:ָ����������չ����]
 * @returns     [E_OS_STATE:ָ��������SUSPEND״̬��]
 */
StatusType  GetEvent( TaskType taskId, EventMaskRefType mask );

// �ڲ�����
StatusType  osekEvent_SetEvent(T_OSEK_TASK_ControlBlock *tcbPtr,EventMaskType   mask);


/**************************** ���岿�� *********************************/

#define DeclareEvent(event)



#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
