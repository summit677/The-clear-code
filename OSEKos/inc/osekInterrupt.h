/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekInterrupt.h,v $
 * Revision 1.0  2008/03/21 09:41:00
 * �����ļ�
*/

/**
 * @file 	osekInterrupt.h
 * @brief
 *	<li>���ܣ������ж���صĽӿڡ��ꡢ�ṹ�ȡ�</li>
 * @author
 * @date 	2008-03-21
 * <p>���ţ�
 */

/**
 * \defgroup  Interrupt �ж�
 * �жϹ���ģ��,��Ҫʵ���жϵĹ���
 */
/**@{*/
/** @name �жϹ���ģ��*/
//@{


#ifndef _OSEK_INTERRUPT_H
#define _OSEK_INTERRUPT_H

/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

// ��������
extern OSDWORD osekInterrupt_NestedLevl;

// �ڲ�����
void osekInterrupt_Initialize( void );

// �жϹ����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    DisableAllInterrupts����ֹ�����жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void DisableAllInterrupts( void );

/**
 * @brief
 *    EnableAllInterrupts��ʹ�������жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void EnableAllInterrupts( void );

/**
 * @brief
 *    SuspendAllInterrupts�����������жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void SuspendAllInterrupts( void );

/**
 * @brief
 *    ResumeAllInterrupts���ָ������жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void ResumeAllInterrupts( void );

/**
 * @brief
 *    SuspendOSInterrupts������OS��ص��жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void SuspendOSInterrupts( void );

/**
 * @brief
 *    ResumeOSInterrupts���ָ�OS��ص��жϡ�
 * @param   	�ޡ�
 * @returns     �ޡ�
 */
void ResumeOSInterrupts( void );


/**************************** ���岿�� *********************************/

#define ISR(isrName) void isrName(void)




#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
