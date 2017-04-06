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
void osekTarget_LoadETSP(void* sp) ;
void osekTarget_LoadBTSP( void );
void osekTarget_SaveBTSP(OSWORD sp );

// 变量声明
extern OSWORD osIntSave_pending;
extern OSWORD osekTarget_AllIntMask_en;
extern OSWORD osekTarget_AllIntMask_pending;
extern OSWORD osekTarget_NestedAllIntMask_en;
extern OSWORD osekTarget_NestedAllIntMask_pending;
extern OSWORD osekTarget_NestedOsIntMask_en;
extern OSWORD osekTarget_NestedOsIntMask_pending;

extern OSWORD osekTarget_SavedBTSP;

//Cortex M0的任务上下文结构
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

#define osekTarget_LoadBTSP() asm("LDR r0,=__cpp(&osekTarget_SavedBTSP)\n\t"\
	"LDR r1,[r0]\n\t"\
	"MOV r1,SP\n\t") 


#define osekTarget_LoadETSP(sp) {unsigned char*temp=sp;asm("LDR r0,=__cpp(&temp);" "LDR r1,[r0];" "MOV r1,SP");}  		


#define OSEK_TARGET_OSIntSave(osIntSave) OSWORD osIntSave
//========================================================================================================
//------------------------------------    OSInt     ------------------------------------------------------
#define OSEK_TARGET_DisableOSInt(osIntSave) asm("LDR r0,=0xE000E100\n\t"\
	"LDR r1,[r0]\n\t"\
	"LDR r0,=__cpp(&osIntSave)\n\t"\
	"STR r1,[r0]\n\t"\
	"LDR r0,=0xE000E200\n\t"\
	"LDR r1,[r0]\n\t"\
	"LDR r0,=__cpp(&osIntSave_pending)\n\t"\
	"STR r1,[r0]\n\t"\
	"CPSID I\n\t")

#define OSEK_TARGET_EnableOSInt(osIntSave)  asm("LDR r0,=__cpp(&osIntSave)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osIntSave_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t")
//********************************************************************************************************

//========================================================================================================
//------------------------------------    OSIntWithoutSave     -------------------------------------------
#define OSEK_TARGET_DisableOSIntWithoutSave()  asm("CPSID I\n\t") 
#define OSEK_TARGET_EnableOSIntWithoutSave()   asm("CPSIE I\n\t")
//********************************************************************************************************

//========================================================================================================
//------------------------------------    AllInt     -----------------------------------------------------
#define OSEK_TARGET_DisableAllInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
#define OSEK_TARGET_EnableAllInt() 	asm("LDR r0,=__cpp(&osekTarget_AllIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_AllIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
//********************************************************************************************************

//========================================================================================================
//------------------------------------    NestedAllInt     -----------------------------------------------
#define OSEK_TARGET_DisableNestedAllInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
#define OSEK_TARGET_EnableNestedAllInt()  asm("LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
//********************************************************************************************************

//========================================================================================================
//------------------------------------    NestedOsInt     ------------------------------------------------
#define OSEK_TARGET_DisableNestedOsInt()  asm("LDR r0,=0xE000E100\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSID I\n\t") 
#define OSEK_TARGET_EnableNestedOsInt()  asm("LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E100\n\t" \
	"STR r1,[r0]\n\t" \
	"LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)\n\t" \
	"LDR r1,[r0]\n\t" \
	"LDR r0,=0xE000E200\n\t" \
	"STR r1,[r0]\n\t" \
	"CPSIE I\n\t") 
//********************************************************************************************************

#endif 
//**********endif TARGET_CORTEXM0*************



#ifdef __cplusplus
}
#endif

#endif

