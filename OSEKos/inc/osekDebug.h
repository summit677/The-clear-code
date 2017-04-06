/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekDebug.h,v $
 * Revision 1.0  2008/04/10 15:32:00
 * �����ļ�
*/

/**
 * @file 	osekDebug.h
 * @brief
 *	<li>���ܣ��������Թ���������ⲿAPI����ȡ�</li>
 * @author
 * @date 	2008-04-10
 * <p>���ţ�
 */

/**
 * \defgroup  Debug ����
 * ���Թ���ģ��,��Ҫʵ�ֵ��Եĸ�������
 */
/**@{*/
/** @name ���Թ���ģ��*/
//@{


#ifndef _OSEK_DEBUG_H
#define _OSEK_DEBUG_H

/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif

/**************************** �������� *********************************/

// ���Թ����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    GetRunningStackUsage����ȡ��������Ķ�ջʹ�������
 * @param       �ޡ�
 * @returns     OSEK_DEBUG_STACKNOASSIGNED: ָ������û�ж�ջ��
 * @returns     ջ��ʹ�õ��ֽ�����
 */
OSDWORD GetRunningStackUsage( void );

/**
 * @brief
 *    GetStackUsage����ȡջ��ʹ�������
 * @param[in]	taskId�������ID��
 * @returns     OSEK_DEBUG_STACKNOASSIGNED: ָ������û�ж�ջ��
 * @returns     ջ��ʹ�õ��ֽ�����
 */
OSDWORD GetStackUsage( TaskType taskId );

/**
 * @brief
 *    GetTimeStamp����ȡʱ�����
 * @param       �ޡ�
 * @returns     ʱ�����ֵ��
 */
OSDWORD GetTimeStamp( void );

extern void read_timer_value(unsigned int *value);

/**************************** ���岿�� *********************************/

#define OSEK_DEBUG_STACKPATTERN    0x55555555
#define OSEK_DEBUG_STACKNOASSIGNED 0xFFFFFFFF


#define OSEK_Time_ReadCount(value) \
    read_timer_value(value)


#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
