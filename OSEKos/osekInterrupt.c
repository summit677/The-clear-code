/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekInterrupt.c,v $
 * Revision 1.0  2008/03/21 09:41:00
 * �����ļ���
 */

/*
 * @file 	osekInterrupt.c
 * @brief
 *	<li>���ܣ�ʵ�ֳ����жϹ������ع��ܡ�</li>
 * @author
 * @date 	2008-03-21
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/
#include "osprop.h"
#include "osapi.h"

/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

// ȫ�ֱ���

// �жϷ�������е��Ա�־
//OSDWORD osekTask_IsrTriggeredTaskSwitchNecessary;

// �ж�Ƕ�����
OSDWORD osekInterrupt_NestedLevl;

// ȫ���жϿ���Ƕ�����
static OSDWORD osekInterrupt_NestedAllInt;

// ISR2���ж�Ƕ�����
static OSDWORD osekInterrupt_NestedOsInt;

// �ж�ջջ��
OSWORD osekInterrupt_IsrStackTop;

// ISR2���ж϶�ջ�ռ�
static OSBYTE isr2Stack[CONFIG_OSEK_INTERRUPT_STACK_SIZE];


/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    osekInterrupt_Initialize���жϳ�ʼ�����ڲ���������
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void osekInterrupt_Initialize(void)
{
	osekInterrupt_IsrStackTop = (OSDWORD)isr2Stack + (OSDWORD)(CONFIG_OSEK_INTERRUPT_STACK_SIZE - 0x20);
}


/*
 * @brief
 *    DisableAllInterrupts����ֹ�����жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void DisableAllInterrupts( void )
{
	OSEK_TARGET_DisableAllInt();
}


/*
 * @brief
 *    EnableAllInterrupts��ʹ�������жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void EnableAllInterrupts( void )
{
	OSEK_TARGET_EnableAllInt();
}


/*
 * @brief
 *    SuspendAllInterrupts�����������жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void SuspendAllInterrupts( void )
{

	if( osekInterrupt_NestedAllInt == 0 )
	{
		OSEK_TARGET_DisableNestedAllInt();
	}

	osekInterrupt_NestedAllInt++;
}


/*
 * @brief
 *    ResumeAllInterrupts���ָ������жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void ResumeAllInterrupts( void )
{
	// �����ֹ�жϲ���Ϊ0��ֱ�ӷ���
	if( osekInterrupt_NestedAllInt == 0)
	{
		return;
	}

	// ��ֹ�жϲ�����1������0ʱʹ�������ж�
	osekInterrupt_NestedAllInt--;
	if( osekInterrupt_NestedAllInt == 0 )
	{
		OSEK_TARGET_EnableNestedAllInt();
	}
}


/*
 * @brief
 *    SuspendOSInterrupts������OS��ص��жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void SuspendOSInterrupts( void )
{
	if( osekInterrupt_NestedOsInt == 0 )
	{
		OSEK_TARGET_DisableNestedOsInt();
	}

	osekInterrupt_NestedOsInt++;
}


/*
 * @brief
 *    ResumeOSInterrupts���ָ�OS��ص��жϡ�
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */
void ResumeOSInterrupts( void )
{
	// �����ֹ�жϲ���Ϊ0��ֱ�ӷ���
	if( osekInterrupt_NestedOsInt == 0 )
	{
		return;
	}

	// ��ֹ�жϲ�����1������0ʱʹ��OS��ص��ж�
	osekInterrupt_NestedOsInt--;

	if( osekInterrupt_NestedOsInt == 0 )
	{
		OSEK_TARGET_EnableNestedOsInt();
	}
}


