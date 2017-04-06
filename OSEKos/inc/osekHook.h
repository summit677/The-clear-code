/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekHook.h,v $
 * Revision 1.0  2008/03/21 14:43:00
 * �����ļ�
*/

/**
 * @file 	osekHook.h
 * @brief
 *	<li>���ܣ�����hook������ݡ�</li>
 * @author
 * @date 	2008-03-21
 * <p>���ţ�
 */

/**
 * \defgroup  HOOK ϵͳ��չ
 * HOOK����ģ��,��Ҫʵ��ϵͳ��չ�Ĺ���
 */
/**@{*/
/** @name HOOK����ģ��*/
//@{


#ifndef _OSEK_HOOK_H
#define _OSEK_HOOK_H

/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif


/**************************** �������� *********************************/

#if defined(CONFIG_OSEK_SYSTEM_GETSERVICEID) || defined(CONFIG_OSEK_SYSTEM_PARAMETERACCESS)
extern OSBYTE  osekHook_ServiceId;
extern OSDWORD osekHook_ObjId;
#endif

#if defined(CONFIG_OSEK_HOOK_ERROR)
extern OSBYTE  osekHook_ErrorNestedLevel;
#endif


/**************************** ���岿�� *********************************/

// ErrorHook ����
#if defined(CONFIG_OSEK_HOOK_ERROR)
/// �������HOOK����ԭ�ͣ��������˴���ص�ʱ�ú����Ŵ��ڣ�
void ErrorHook( StatusType error );
#endif

// PreTaskHook ��������غ궨��
#if defined(CONFIG_OSEK_HOOK_PRETASK)
/// �����л�ǰ��HOOK����ԭ�ͣ�������������ǰ�ص�ʱ�ú����Ŵ��ڣ�
void PreTaskHook( void );
#define OSEK_HOOK_PreTaskHook PreTaskHook
#else
#define OSEK_HOOK_PreTaskHook()
#endif

// PostTaskHook ��������غ궨��
#if defined(CONFIG_OSEK_HOOK_POSTTASK)
/// �����л����HOOK����ԭ�ͣ��������������ص�ʱ�ú����Ŵ��ڣ�
void PostTaskHook( void );
#define OSEK_HOOK_PostTaskHook  PostTaskHook
#else
#define OSEK_HOOK_PostTaskHook()
#endif

// StartupHook ��������غ궨��
#if defined(CONFIG_OSEK_HOOK_STARTUP)
/// ϵͳ������HOOK����ԭ�ͣ��������������ص�ʱ�ú����Ŵ��ڣ�
void StartupHook( void );
#define OSEK_HOOK_StartupHook StartupHook
#else
#define OSEK_HOOK_StartupHook()
#endif

// ShutdownHook ��������غ궨��
#if defined(CONFIG_OSEK_HOOK_SHUTDOWN)
/// ϵͳ�رյ�HOOK����ԭ�ͣ��������˹رջص�ʱ�ú����Ŵ��ڣ�
void ShutdownHook( StatusType error );
#define OSEK_HOOK_ShutdownHook(error) (ShutdownHook(error))
#else
#define OSEK_HOOK_ShutdownHook(error)
#endif

// IdleLoopHook ��������غ궨��
#if defined(CONFIG_OSEK_HOOK_IDLE)
/// ϵͳ���е�HOOK����ԭ�ͣ��������˿��лص�ʱ�ú����Ŵ��ڣ�
void IdleLoopHook( void );
#define OSEK_HOOK_IdleHook  IdleLoopHook
#else
#define OSEK_HOOK_IdleHook()
#endif



#if defined(CONFIG_OSEK_SYSTEM_GETSERVICEID) || defined(CONFIG_OSEK_SYSTEM_PARAMETERACCESS)
#define OSEK_HOOK_SET_INFO(id,param) \
	osekHook_ServiceId = (id); \
 	osekHook_ObjId =(OSDWORD)(param)

#define OSEK_HOOK_CLEAR_INFO() 	(osekHook_ServiceId = OSServiceId_NoService)
#else
 #define OSEK_HOOK_SET_INFO(id,param) 	((void)0)
 #define OSEK_HOOK_CLEAR_INFO()	((void)0)
#endif


// OSEK_HOOK_ErrorHook �궨��
#if defined(CONFIG_OSEK_HOOK_ERROR)

#define OSEK_HOOK_ErrorHook(error,id,param)  \
	if( osekHook_ErrorNestedLevel == 0 ) \
	{ \
		OSEK_TARGET_OSIntSave( _save ); \
		OSEK_TARGET_DisableOSInt(_save); \
		osekHook_ErrorNestedLevel++; \
		OSEK_HOOK_SET_INFO((id),(param));\
 		ErrorHook((error)); \
 		OSEK_HOOK_CLEAR_INFO();\
 		osekHook_ErrorNestedLevel--; \
		OSEK_TARGET_EnableOSInt(_save); \
	}\
	return error

#else

#define OSEK_HOOK_ErrorHook(error,id,param) return error

#endif




#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
