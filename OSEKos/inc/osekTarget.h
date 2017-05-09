/****************************************************************************
 *				电子科技大学嵌入式软件工程中心 版权所有
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekTarget.h,v $
 * Revision 1.0  2008/03/12 11:24:00
 * 创建文件
*/

/**
 * @file 	osekTarget.h
 * @brief
 *	<li>功能：定义CPU相关的数据结构、宏、申明等。</li>
 * @author
 * @date 	2008-03-12
 * <p>部门：
 */


#ifndef _OSEK_TARGET_H
#define _OSEK_TARGET_H
#include <stdint.h>
#include "osprop.h"
#include "osapi.h"
#include "osekOccConfig.h"
#include "cfg.h"
/**************************** 引用部分 *********************************/


#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//**********if defined(TARGET_CORTEXM0)*************
#if defined(CONFIG_OSEK_TARGET_CORTEXM0)

// 内部函数
	
OSDWORD osekTarget_SaveContext( void * savedContext );
void osekTarget_RestoreContext( void * restoredContext );
	
//int fun(void * savedContext );

// 下面的函数用于第一次启动扩展任务和基本任务时调整任务的栈
void osekTarget_LoadETSP(OSBYTEPTR sp) ;
void osekTarget_LoadBTSP( void );
void osekTarget_SaveBTSP(OSDWORD sp );

// 变量声明
extern OSDWORD	osIntSave_en;
extern OSDWORD osIntSave_pending;
extern OSDWORD osekTarget_AllIntMask_en;
extern OSDWORD osekTarget_AllIntMask_pending;
extern OSDWORD osekTarget_NestedAllIntMask_en;
extern OSDWORD osekTarget_NestedAllIntMask_pending;
extern OSDWORD osekTarget_NestedOsIntMask_en;
extern OSDWORD osekTarget_NestedOsIntMask_pending;

extern OSDWORD osekTarget_SavedBTSP;

//Cortex M0的任务上下文结构
typedef struct T_OSEK_TARGET_TaskContext_struct
{
	OSDWORD sp;	//0
	OSDWORD LR;	//4
	OSDWORD pc;	//8
	OSDWORD APSR;	//12
	
	OSDWORD r4;	//16
	OSDWORD r5;	//20
	OSDWORD r6;	//24
	OSDWORD r7;	//28
	OSDWORD r8;	//32
	OSDWORD r9;	//36
	OSDWORD r10;	//40
	OSDWORD r11;	//44

	OSDWORD primask;	//48
	OSDWORD IPSR;	//52
	OSDWORD EPSR;	//56

}T_OSEK_TARGET_TaskContext_struct;  





//#define OSEK_TARGET_SaveBTSP(sp) (osekTarget_SavedBTSP = (sp) - (OSWORD)0x20)	  	
void OSEK_TARGET_SaveBTSP(OSDWORD sp);
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
#define OSEK_TARGET_DisableOSIntWithoutSave()  __disable_irq() //asm("CPSID I\n\t") 
#define OSEK_TARGET_EnableOSIntWithoutSave()   __enable_irq() //asm("CPSIE I\n\t")
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

