/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekExecution.h,v $
 * Revision 1.0  2008/03/12 13:33:00
 * �����ļ�
*/

/**
 * @file 	osekExecution.h
 * @brief
 *	<li>���ܣ�����ִ����ص����ݽṹ���ꡢ�����ȡ�</li>
 * @author
 * @date 	2008-03-12
 * <p>���ţ�
 */

/**
 * \defgroup  Execution ϵͳִ��
 * ϵͳִ�й���ģ��,��Ҫʵ��ϵͳִ�еĹ���
 */
/**@{*/
/** @name ϵͳִ�й���ģ��*/
//@{


#ifndef _OSEK_EXECUTION_H
#define _OSEK_EXECUTION_H

/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

// ִ�й����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    StartOS����������ϵͳ��
 * @param[in]	mode��Ӧ��ģʽ��
 * @returns     �ޡ�
 */
void StartOS( AppModeType mode );

/**
 * @brief
 *    ShutdownOS���رղ���ϵͳ��
 * @param[in]	error��������Ϣ��
 * @returns     �ޡ�
 */
void ShutdownOS( StatusType error );

// ��������
extern OSBYTE osekExecution_CurrentAppMode;


/**************************** ���岿�� *********************************/

/**
 * @brief
 *    GetActiveApplicationMode����ȡ��ǰ��Ӧ��ģʽ��
 * @param   	�ޡ�
 * @returns     ��ǰӦ��ģʽ��
 */
#define GetActiveApplicationMode() (osekExecution_CurrentAppMode)




#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
