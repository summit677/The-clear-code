/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekTarget.h,v $
 * Revision 1.0  2008/03/12 11:24:00
 * �����ļ�
*/

/**
 * @file 	osekTarget.h
 * @brief
 *	<li>���ܣ�����CPU��ص����ݽṹ���ꡢ�����ȡ�</li>
 * @author
 * @date 	2008-03-12
 * <p>���ţ�
 */


#ifndef _OSEK_TARGET_H
#define _OSEK_TARGET_H
#include <stdint.h>
#include "osprop.h"
#include "osapi.h"
#include "osekOccConfig.h"
#include "cfg.h"
/**************************** ���ò��� *********************************/


#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**********if defined(TARGET_CORTEXM0)*************
#if defined(CONFIG_OSEK_TARGET_CORTEXM0)

// �ڲ�����
OSDWORD osekTarget_SaveContext( void * savedContext );
void osekTarget_RestoreContext( void * restoredContext );
//int fun(void * savedContext );

// ����ĺ������ڵ�һ��������չ����ͻ�������ʱ���������ջ
void osekTarget_LoadETSP(void* sp) ;
void osekTarget_LoadBTSP( void );
void osekTarget_SaveBTSP(OSWORD sp );

// ��������
extern OSWORD	osIntSave_en;
extern OSWORD osIntSave_pending;
extern OSWORD osekTarget_AllIntMask_en;
extern OSWORD osekTarget_AllIntMask_pending;
extern OSWORD osekTarget_NestedAllIntMask_en;
extern OSWORD osekTarget_NestedAllIntMask_pending;
extern OSWORD osekTarget_NestedOsIntMask_en;
extern OSWORD osekTarget_NestedOsIntMask_pending;

extern OSWORD osekTarget_SavedBTSP;

//Cortex M0�����������Ľṹ
typedef struct T_OSEK_TARGET_TaskContext_struct
{
	OSWORD sp;
	OSWORD LR;
	OSWORD pc;
	OSWORD xPSR;
	
	OSWORD r4;
	OSWORD r5;
	OSWORD r6;
	OSWORD r7;
	OSWORD r8;
	OSWORD r9;
	OSWORD r10;
	OSWORD r11;

	OSWORD primask;

}T_OSEK_TARGET_TaskContext_struct;  





#define OSEK_TARGET_SaveBTSP(sp) (osekTarget_SavedBTSP = (sp) - (OSWORD)0x20)	  	

//#define osekTarget_LoadETSP(sp) {unsigned char*temp=sp;asm("LDR r0,=__cpp(&temp);" "LDR r1,[r0];" "MOV r1,SP");}  		


#define OSEK_TARGET_OSIntSave(osIntSave) OSWORD osIntSave
//========================================================================================================
//------------------------------------    OSInt     ------------------------------------------------------
void OSEK_TARGET_DisableOSInt_func();
#define OSEK_TARGET_DisableOSInt(osIntSave) OSEK_TARGET_DisableOSInt_func();osIntSave = osIntSave_en
/*
#define OSEK_TARGET_DisableOSInt(osIntSave) asm("LDR r0,=0xE000E100\n\t"\
	"LDR r1,[r0]\n\t"\
	"LDR r0,=__cpp(&osIntSave)\n\t"\
	"STR r1,[r0]\n\t"\
	"LDR r0,=0xE000E200\n\t"\
	"LDR r1,[r0]\n\t"\
	"LDR r0,=__cpp(&osIntSave_pending)\n\t"\
	"STR r1,[r0]\n\t"\
	"CPSID I\n\t")
*/
void OSEK_TARGET_EnableOSInt(OSWORD osIntSave);
/*
#define OSEK_TARGET_EnableOSInt(osIntSave)  asm("LDR r0,=__cpp(&osIntSave)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osIntSave_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t")
*/
//********************************************************************************************************

//========================================================================================================
//------------------------------------    OSIntWithoutSave     -------------------------------------------
#define OSEK_TARGET_DisableOSIntWithoutSave()  __enable_irq() //asm("CPSID I\n\t") 
#define OSEK_TARGET_EnableOSIntWithoutSave()   __disable_irq() //asm("CPSIE I\n\t")
//********************************************************************************************************

//========================================================================================================
//------------------------------------    AllInt     -----------------------------------------------------
void OSEK_TARGET_DisableAllInt();
/*
#define OSEK_TARGET_DisableAllInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
*/
void OSEK_TARGET_EnableAllInt();
/*
#define OSEK_TARGET_EnableAllInt() 	asm("LDR r0,=__cpp(&osekTarget_AllIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
*/
//********************************************************************************************************

//========================================================================================================
//------------------------------------    NestedAllInt     -----------------------------------------------
void OSEK_TARGET_DisableNestedAllInt();
/*
#define OSEK_TARGET_DisableNestedAllInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
*/
void OSEK_TARGET_EnableNestedAllInt();
/*
#define OSEK_TARGET_EnableNestedAllInt()  asm("LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
*/
//********************************************************************************************************

//========================================================================================================
//------------------------------------    NestedOsInt     ------------------------------------------------
void OSEK_TARGET_DisableNestedOsInt();
/*
#define OSEK_TARGET_DisableNestedOsInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
*/
void OSEK_TARGET_EnableNestedOsInt();
/*
#define OSEK_TARGET_EnableNestedOsInt()  asm("LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
*/
//********************************************************************************************************

#endif 
//**********endif TARGET_CORTEXM0*************



#ifdef __cplusplus
}
#endif

#endif

