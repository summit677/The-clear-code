/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekHook.c,v $
 * Revision 1.0  2008/04/10 14:54:00
 * �����ļ�
*/

/*
 * @file 	osekHook.c
 * @brief
 *	<li>���ܣ�ʵ��HOOK������ݡ�</li>
 * @author
 * @date 	2008-04-10
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"

/*************************** ǰ���������� ******************************/

/**************************** ���岿�� *********************************/

// ȫ�ֱ���
#if defined(CONFIG_OSEK_SYSTEM_GETSERVICEID) || defined(CONFIG_OSEK_SYSTEM_PARAMETERACCESS)
OSBYTE  osekHook_ServiceId;
OSDWORD osekHook_ObjId;
#endif


#if defined(CONFIG_OSEK_HOOK_ERROR)
OSBYTE  osekHook_ErrorNestedLevel;
#endif

/**************************** ʵ�ֲ��� *********************************/


