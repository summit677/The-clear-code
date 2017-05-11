/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekTarget.c,v $
 * Revision 1.0  2008/03/20 13:37:00
 * �����ļ���
 */

/*
 * @file 	osekTarget.c
 * @brief
 *	<li>���ܣ�ʵ�������CPU��Ŀ�����صĹ��ܡ�</li>
 * @author
 * @date 	2008-03-20
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"

/*************************** ǰ���������� ******************************/


/**************************** ���岿�� *********************************/

#if defined(CONFIG_OSEK_TARGET_PPC)

// ȫ�ֱ���

// ���ڼ�¼��������ĵ�ǰ����ջλ��
OSDWORD osekTarget_SavedBTSP;

// OS����ж�����
OSDWORD osekTarget_OSIntMask;
// �����ж�����
OSDWORD osekTarget_AllIntMask;
// Ƕ�׵������жϵ�����
OSDWORD osekTarget_NestedAllIntMask;
// Ƕ�׵�OS����жϵ�����
OSDWORD osekTarget_NestedOsIntMask;


/**************************** ʵ�ֲ��� *********************************/

#if defined(CONFIG_OSEK_COMPILER_GCC)


/*
 * OSDWORD osekTarget_SaveContext( void * savedContext)
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_SaveContext");
asm("osekTarget_SaveContext:");

// ����PC(LR)
asm("	mflr    4 ");
asm("stw     4,0(3)");

// ����ջָ��
asm("stwu    1,4(3)");

// ����r14-r31
asm("stwu    14,4(3)");
asm("stwu    15,4(3)");
asm("stwu    16,4(3)");
asm("stwu    17,4(3)");
asm("stwu    18,4(3)");
asm("stwu    19,4(3)");
asm("stwu    20,4(3)");
asm("stwu    21,4(3)");
asm("stwu    22,4(3)");
asm("stwu    23,4(3)");
asm("stwu    24,4(3)");
asm("stwu    25,4(3)");
asm("stwu    26,4(3)");
asm("stwu    27,4(3)");
asm("stwu    28,4(3)");
asm("stwu    29,4(3)");
asm("stwu    30,4(3)");
asm("stwu    31,4(3)");

#if defined(CONFIG_OSEK_TARGET_FLOAT)
#if defined(CONFIG_OSEK_TARGET_MPC555)
//����f14-f31
asm("stfdu   14,4(3)");
asm("stfdu   15,8(3)");
asm("stfdu   16,8(3)");
asm("stfdu   17,8(3)");
asm("stfdu   18,8(3)");
asm("stfdu   19,8(3)");
asm("stfdu   20,8(3)");
asm("stfdu   21,8(3)");
asm("stfdu   22,8(3)");
asm("stfdu   23,8(3)");
asm("stfdu   24,8(3)");
asm("stfdu   25,8(3)");
asm("stfdu   26,8(3)");
asm("stfdu   27,8(3)");
asm("stfdu   28,8(3)");
asm("stfdu   29,8(3)");
asm("stfdu   30,8(3)");
asm("stfdu   31,8(3)");
#endif
#endif

// ������
asm("li      3,0");
asm("blr");



/*
 * void osekTarget_RestoreContext( void * restoredContext )
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_RestoreContext");
asm("osekTarget_RestoreContext:");

// �ָ�LR
asm("lwz     4,0(3)");
asm("mtlr    4");

// �ָ�ջָ��
asm("lwzu    1,4(3)");

// �ָ�r14-r31
asm("lwzu    14,4(3)");
asm("lwzu    15,4(3)");
asm("lwzu    16,4(3)");
asm("lwzu    17,4(3)");
asm("lwzu    18,4(3)");
asm("lwzu    19,4(3)");
asm("lwzu    20,4(3)");
asm("lwzu    21,4(3)");
asm("lwzu    22,4(3)");
asm("lwzu    23,4(3)");
asm("lwzu    24,4(3)");
asm("lwzu    25,4(3)");
asm("lwzu    26,4(3)");
asm("lwzu    27,4(3)");
asm("lwzu    28,4(3)");
asm("lwzu    29,4(3)");
asm("lwzu    30,4(3)");
asm("lwzu    31,4(3)");

#if defined(CONFIG_OSEK_TARGET_FLOAT)
#if defined(CONFIG_OSEK_TARGET_MPC555)
// �ָ�f14-f31
asm("lfdu   14,4(3)");
asm("lfdu   15,8(3)");
asm("lfdu   16,8(3)");
asm("lfdu   17,8(3)");
asm("lfdu   18,8(3)");
asm("lfdu   19,8(3)");
asm("lfdu   20,8(3)");
asm("lfdu   21,8(3)");
asm("lfdu   22,8(3)");
asm("lfdu   23,8(3)");
asm("lfdu   24,8(3)");
asm("lfdu   25,8(3)");
asm("lfdu   26,8(3)");
asm("lfdu   27,8(3)");
asm("lfdu   28,8(3)");
asm("lfdu   29,8(3)");
asm("lfdu   30,8(3)");
asm("lfdu   31,8(3)");
#endif
#endif

// ����1
asm("li      3,1");
asm("blr");



/*
 * void osekTarget_LoadETSP(void* sp)
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_LoadETSP");
asm("osekTarget_LoadETSP:");
asm("mr 1,3");
asm("blr");


/*
 * void osekTarget_SaveBTSP(OSDWORD sp )
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_SaveBTSP");
asm("osekTarget_SaveBTSP:");
asm("subi 3,3,0x20");
asm("mtsprg 0,3 ");
asm("blr");


/*
 * void osekTarget_LoadBTSP( void )
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_LoadBTSP");
asm("osekTarget_LoadBTSP:");
asm("mfsprg 1,0");
asm("blr");


#endif /* #if defined(CONFIG_OSEK_COMPILER_GCC) */


#endif /* #if defined(CONFIG_OSEK_TARGET_PPC) */



/**************************** ���岿�� *********************************/

#if defined(CONFIG_OSEK_TARGET_X86)

// ȫ�ֱ���

// ���ڼ�¼��������ĵ�ǰ����ջλ��
OSDWORD osekTarget_SavedBTSP;

// OS����ж�����
OSDWORD osekTarget_OSIntMask;
// �����ж�����
OSDWORD osekTarget_AllIntMask;
// Ƕ�׵������жϵ�����
OSDWORD osekTarget_NestedAllIntMask;
// Ƕ�׵�OS����жϵ�����
OSDWORD osekTarget_NestedOsIntMask;


/**************************** ʵ�ֲ��� *********************************/

#if defined(CONFIG_OSEK_COMPILER_GCC)


/*
 * OSDWORD osekTarget_SaveContext( void *context)
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_SaveContext");
asm("osekTarget_SaveContext:");
asm("movl 4(%esp),%eax");
asm("pushf");
asm("popl 0(%eax)");
asm("movl %esp,4(%eax)");
asm("movl %ebp,8(%eax)");
asm("movl %ebx,0xc(%eax)");
asm("movl %esi,0x10(%eax)");
asm("movl %edi,0x14(%eax)");
asm("movl (%esp),%edi");
asm("movl %edi,0x18(%eax)");
#if defined(CONFIG_OSEK_TARGET_FLOAT)
asm("fsave 0x1c(%eax)");
#endif
asm("movl $0,%eax");
asm("ret");



/*
 * void osekTarget_RestoreContext( void *context )
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_RestoreContext");
asm("osekTarget_RestoreContext:");
asm("movl 4(%esp),%eax");
asm("pushl 0(%eax)");
asm("popf ");
asm("movl 4(%eax),%esp");
asm("movl 8(%eax),%ebp");
asm("movl 0xc(%eax),%ebx");
asm("movl 0x10(%eax),%esi");
asm("movl 0x14(%eax),%edi");
asm("addl $4,%esp");
asm("pushl 0x18(%eax)");
#if defined(CONFIG_OSEK_TARGET_FLOAT)
asm("frstor 0x1c(%eax)");
#endif
asm("movl $1,%eax");
asm("ret");



/*
 * void osekTarget_LoadETSP(void* sp)
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_LoadETSP");
asm("osekTarget_LoadETSP:");
asm("movl (%esp),%ecx");
asm("movl 4(%esp),%esp");
asm("movl %esp,%ebp");
asm("pushl %ecx");
asm("ret");


/*
 * void osekTarget_LoadBTSP( void )
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_LoadBTSP");
asm("osekTarget_LoadBTSP:");
asm("movl (%esp),%ecx");
asm("movl osekTarget_SavedBTSP,%esp");
asm("movl %esp,%ebp");
asm("pushl %ecx");
asm("ret");


/*
 * void osekTarget_IsrHandler( void )
 * ע�⣺�ڽ��뱾����ʱecx�����ڵ�ǰջ�У�����ecx�ĵ�ǰֵΪ�ж�������
 */

asm(".text");
asm(".align  4");
asm(".global osekTarget_IsrHandler");
asm("osekTarget_IsrHandler:");

// ����������Ҫ�����������
asm("pushl %eax");
asm("pushl %edx");

// �����ж�������
asm(".equ PIC_MASTER_IMR_IO_PORT ,0x21");
asm(".equ PIC_SLAVE_IMR_IO_PORT,0xa1");
asm(".equ PIC_MASTER_COMMAND_IO_PORT,0x20");
asm(".equ PIC_SLAVE_COMMAND_IO_PORT, 0xa0");

asm(".equ PIC_EOI,0x20");

// ����ԭ����������
asm("movw	BSP_i8259Mask, %ax ");
asm("pushl	%eax	");

// �����ж����������µ�������
asm("movw	BSP_i8259MaskTable(,%ecx,2), %dx");
asm("orw	%dx, %ax");

// �����µ��ж�������
asm("movw   %ax, BSP_i8259Mask");
asm("outb	$PIC_MASTER_IMR_IO_PORT");
asm("movb	%ah, %al");
asm("outb	$PIC_SLAVE_IMR_IO_PORT");

// �ж�Ӧ������Ǵ�Ƭ�жϻ���ҪӦ���Ƭ������Ƭ����Ӧ��
asm("movb	$PIC_EOI, %al");
asm("cmpl   $7, %ecx");
asm("jbe	.master");
asm("outb   $PIC_SLAVE_COMMAND_IO_PORT");
asm(".master:");
asm("outb   $PIC_MASTER_COMMAND_IO_PORT");

// �������õ��ж����ͽ�����ת
asm("movb	osekConfig_InterruptTypeTable(%ecx),%al");
asm("cmpb	$1,%al");
asm("je		.isr1");

// ����ǰջ��ջָ�뱣�浽ebp��
asm("pushl	%ebp");
asm("movl   %esp,%ebp");

// �ж��Ƿ�Ƕ�ף����Ƕ�����ٽ����ж�ջ���л�
asm("cmpl   $0, osekInterrupt_NestedLevl ");
asm("jne    .nested ");
asm("movl   osekInterrupt_IsrStackTop, %esp");

// ʹǶ����ȼ�1
asm(".nested:");
asm("incl osekInterrupt_NestedLevl");
asm("sti");
asm("movl osekConfig_InterruptEntryTable(,%ecx,4),%eax");
asm("subl $0xc,%esp");
asm("call *%eax");
asm("cli");

// �ָ�ջָ��
asm("movl	%ebp,%esp");
asm("popl	%ebp");

// �ָ��ж�������
asm("popl	%eax");
asm("movw	%ax, BSP_i8259Mask");
asm("outb	$PIC_MASTER_IMR_IO_PORT");
asm("movb	%ah, %al");
asm("outb	$PIC_SLAVE_IMR_IO_PORT");

// �жϲ�Ƕ�ײ�����Ҫ�����л�ʱ���������л�
asm("decl	osekInterrupt_NestedLevl");
asm("jne    .exit");
asm("cmpb   $0,osekTask_IsrTriggeredTaskSwitchNecessary");
asm("jne	.schedule");
asm("jmp	.exit");

// ���������л�����
asm(".schedule:");
asm("movb	$0,osekTask_IsrTriggeredTaskSwitchNecessary");
asm("subl	$0xc,%esp");
asm("call	osekTask_Dispatch");
asm("addl	$0xc,%esp");
asm("jmp	.exit");

asm(".isr1:");
asm("movl	osekConfig_InterruptEntryTable(,%ecx,4),%eax");
asm("subl	$0xc,%esp");
asm("call	*%eax");
asm("addl	$0xc,%esp");

// �ָ��ж�������
asm(".restorePIC:");
asm("popl	%eax");
asm("movw	%ax, BSP_i8259Mask");
asm("outb	$PIC_MASTER_IMR_IO_PORT");
asm("movb	%ah, %al");
asm("outb	$PIC_SLAVE_IMR_IO_PORT");

// �ָ��ж������Ĳ��˳��ж�
asm(".exit:");
asm("popl	%edx");
asm("popl	%eax");
asm("popl	%ecx");
asm("iret");



/* �ⲿ�ж����� */

asm(".macro OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY  vector ");
asm("	.p2align 4 ");
asm("   .global osekTarget_IsrPrologue_\\vector ");
asm("	osekTarget_IsrPrologue_\\vector: ");
asm("	pushl   %ecx ");
asm("	movl    $\\vector, %ecx ");
asm("	jmp   osekTarget_IsrHandler ");
asm(".endm");

asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 0");

asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 1");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 2");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 3");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 4");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 5");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 6");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 7");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 8");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 9");

asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 10");

asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 11");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 12");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 13");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 14");
asm("OSEK_TARGET_DISTINCT_INTERRUPT_ENTRY 15");



/* �쳣������ */

asm(".text");
asm(".align  4");
asm(".global osekTarget_ExceptionHandler");
asm("	osekTarget_ExceptionHandler:");
asm("	pusha	");
asm("	pushl	%esp	");
asm("	call	osekTarget_ExceptionMonitor");
asm("	addl	$4, %esp");
asm("	popa	");
asm("	addl	$8, %esp	");
asm("	iret");



/* �쳣���� */

asm(".macro OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY vector ");
asm("	.p2align 4 ");
asm("	.global osekTarget_ExceptionPrologue_\\vector	");
asm("	osekTarget_ExceptionPrologue_\\vector:	");
asm("	pushl	$\\vector	");
asm("	jmp   osekTarget_ExceptionHandler");
asm(".endm");


asm(".macro OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY vector ");
asm("	.p2align 4 ");
asm("	.global osekTarget_ExceptionPrologue_\\vector	");
asm(" 	osekTarget_ExceptionPrologue_\\vector:	");
asm("	pushl	$0	");
asm("	pushl	$\\vector	");
asm("  	jmp   osekTarget_ExceptionHandler");
asm(".endm");


/*
 * Divide Error
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 0");

/*
 * Debug Exception
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 1");

/*
 * NMI
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 2");

/*
 * Breakpoint
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 3");

/*
 * Overflow
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 4");

/*
 * Bound Range Exceeded
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 5");

/*
 * Invalid Opcode
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 6");

/*
 * No Math Coproc
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 7");

/*
 * Double Fault
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 8");

/*
 * Coprocessor segment overrun
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 9");

/*
 * Invalid TSS
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 10");

/*
 * Segment Not Present
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 11");

/*
 * Stack segment Fault
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 12");

/*
 * General Protection Fault
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 13");

/*
 * Page Fault
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 14");

/*
 * Floating point error (NB 15 is reserved it is therefor skipped)
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITHOUT_FAULTCODE_ENTRY 16");

/*
 * Aligment Check
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 17");

/*
 * Machine Check
 */
asm("OSEK_TARGET_DISTINCT_EXCEPTION_WITH_FAULTCODE_ENTRY 18");



void osekTarget_ExceptionMonitor(T_OSEK_TARGET_ExceptionFrame *exceptionFrame)
{
	while(1)
	{
	}
}


#endif /* #if defined(CONFIG_OSEK_COMPILER_GCC) */


#endif /* #if defined(CONFIG_OSEK_TARGET_X86) */

/*************************** ǰ���������� ******************************/
#if defined(CONFIG_OSEK_TARGET_HCS12X)

#include <mc9s12xep100.h>
// ȫ�ֱ���
// ���ڼ�¼��������ĵ�ǰ����ջλ��
OSWORD osekTarget_SavedBTSP;

// OS����ж�����
OSWORD osekTarget_OSIntMask;
// �����ж�����
OSWORD osekTarget_AllIntMask;
// Ƕ�׵������жϵ�����
OSWORD osekTarget_NestedAllIntMask;
// Ƕ�׵�OS����жϵ�����
OSWORD osekTarget_NestedOsIntMask;



#pragma CODE_SEG NON_BANKED
OSDWORD osekTarget_SaveContext( void *context) 
  {

  
   __asm {

XGDX       ;   //change register D and X
STD 4,X    ;   //store x
TFR CCRW,D ;
STD 0,x    ;   //store  ccr
STY 6,X    ;   //store y

LDAA 0,SP  ;
STAA 8,X   ;  //store  ppage
LDD 1,SP   ;
STD 9,X    ;  //store pc
LEAY 3,SP  ;
STY  2,X   ;  //store sp
   
   }
   
return 0;
                  
 }
  
  
void osekTarget_RestoreContext( void *context )
  {
   
    __asm {

XGDX;

LDD 0,X ;
TFR D,CCRW;    //resore ccr
LDS 2,X;       //resore sp
LDY 6,X  ;     //resore y
LDD  9,X ;
PSHD     ;     //restore pc
LDAA 8,X ;
PSHA     ;     //restore ppage
LDX 4,x  ;     //resore x

//write 1 to register D (used in dispatch func) 
LDD #$1  ;

RTC      ;
  } 
  
  
  } 
  
  
void int_mask_save(unsigned int *value) {

  *value=1;
  
 

}
void int_mask_restore(unsigned int value){
 if(value==66) {  
    PITINTE=0;
 }else {
    PITINTE=1;
 }
    
}
void int_fit_restore(unsigned int value){

}
void int_vector_save(unsigned int *value){
  
}

#pragma CODE_SEG DEFAULT

#endif //#if defined(CONFIG_OSEK_TARGET_HCS12X)

/*************************** ǰ���������� ******************************/
#if defined(CONFIG_OSEK_TARGET_CORTEXM0)

#include <NUC1xx.h>
#include <core_cm0.h>
#include <system_NUC1xx.h>

// ȫ�ֱ���
// ���ڼ�¼��������ĵ�ǰ����ջλ��
OSDWORD osekTarget_SavedBTSP;

// OS����ж�����
OSDWORD osekTarget_OSIntMask;
  
OSDWORD	osIntSave_en;
OSDWORD osIntSave_pending;
  
OSDWORD osekTarget_AllIntMask_en;
OSDWORD osekTarget_AllIntMask_pending;
  
OSDWORD osekTarget_NestedAllIntMask_en;
OSDWORD osekTarget_NestedAllIntMask_pending;
  
OSDWORD osekTarget_NestedOsIntMask_en;
OSDWORD osekTarget_NestedOsIntMask_pending;


//==========================================================================================
void OSEK_TARGET_SaveBTSP(OSDWORD sp)
{	
	osekTarget_SavedBTSP = sp - (OSDWORD)0x20;
}
__asm OSDWORD osekTarget_SaveContext( void *context) 
{
	MRS r1, msp
	STR r1,[r0,#0] ;store sp
	
	MOV R1,lr
	STR r1,[r0,#4] ;store LR
	
	MOV r1,pc
	STR r1,[r0,#8] ;store PC
	
	STR r4,[r0,#16] ;store R4
	STR r5,[r0,#20] ;store R5
	STR r6,[r0,#24] ;store R6
	STR r7,[r0,#28] ;store R7
	MOV r1,r8
	STR r1,[r0,#32] ;store R8
	MOV r1,r9
	STR r1,[r0,#36] ;store R9
	MOV r1,r10
	STR r1,[r0,#40] ;store R10
	MOV r1,r11
	STR r1,[r0,#44] ;store R11
	
	MOVS r0,#0 ;��������ֵ��0
	BX LR;
	
}
  
  
__asm void osekTarget_RestoreContext( void *context )
{
		LDR r1,[r0,#0] ;Restore sp
	  msr msp,r1
		
		LDR r1,[r0,#4] ;Restore LR
		MOV lr,r1

			
		LDR r4,[r0,#16] ;Restore R4
		LDR r5,[r0,#20] ;Restore R5
		LDR r6,[r0,#24] ;Restore R6
		LDR r7,[r0,#28] ;Restore R7
	
		LDR r1,[r0,#32] ;Restore R8
		MOV r8,r1
		LDR r1,[r0,#36] ;Restore R9
		MOV r9,r1
		LDR r1,[r0,#40] ;Restore R10
		MOV r10,r1
		LDR r1,[r0,#44] ;Restore R11
		MOV r11,r1
		
		MOVS r0,#1 ;��������ֵ��1
		BX LR;

} 


__asm void osekTarget_LoadBTSP()
{	
	LDR r0,=__cpp(&osekTarget_SavedBTSP);
	LDR r1,[r0];
	msr msp,r1
	bx lr
}

__asm void osekTarget_LoadETSP(OSBYTEPTR sp)
{
	;LDR r1,[r0]
	msr msp,r0
	bx lr
}

__asm void OSEK_TARGET_DisableOSInt_func()
{
	LDR r0,=0xE000E100
	LDR r1,[r0]
	;LDR r0,=__cpp(&osIntSave_en)
	STR r1,[r0]
	LDR r0,=0xE000E200
	LDR r1,[r0]
	LDR r0,=__cpp(&osIntSave_pending)
	STR r1,[r0]
	CPSID I
	bx lr
}	
__asm void OSEK_TARGET_EnableOSInt(OSWORD osIntSave)
{
	;LDR r0,=__cpp(&osIntSave)
	;LDR r1,[r0]
	LDR r1,=0xE000E100
	STR r0,[r1]
	LDR r0,=__cpp(&osIntSave_pending)
	LDR r1,[r0]
	LDR r0,=0xE000E200
	STR r1,[r0]
	CPSIE I
	bx lr
}
__asm void OSEK_TARGET_DisableAllInt()
{
	LDR r0,=0xE000E100
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_AllIntMask_en)
	STR r1,[r0]
	LDR r0,=0xE000E200
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_AllIntMask_pending)
	STR r1,[r0]
	CPSID I
	bx lr
}
__asm void OSEK_TARGET_EnableAllInt()
{
	LDR r0,=__cpp(&osekTarget_AllIntMask_en)
	LDR r1,[r0]
	LDR r0,=0xE000E100
	STR r1,[r0]
	LDR r0,=__cpp(&osekTarget_AllIntMask_pending)
	LDR r1,[r0]
	LDR r0,=0xE000E200
	STR r1,[r0]
	CPSIE I
	bx lr
}
__asm void OSEK_TARGET_DisableNestedAllInt()
{
	LDR r0,=0xE000E100
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)
	STR r1,[r0]
	LDR r0,=0xE000E200
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)
	STR r1,[r0]
	CPSID I
	bx lr
}
__asm void OSEK_TARGET_EnableNestedAllInt()
{
	LDR r0,=__cpp(&osekTarget_NestedAllIntMask_en)
	LDR r1,[r0]
	LDR r0,=0xE000E100
	STR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedAllIntMask_pending)
	LDR r1,[r0]
	LDR r0,=0xE000E200
	STR r1,[r0]
	CPSIE I
	bx lr
}
__asm void OSEK_TARGET_DisableNestedOsInt()
{
	LDR r0,=0xE000E100
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)
	STR r1,[r0]
	LDR r0,=0xE000E200
	LDR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)
	STR r1,[r0]
	CPSID I
	bx lr
}
__asm void OSEK_TARGET_EnableNestedOsInt()
{
	LDR r0,=__cpp(&osekTarget_NestedOsIntMask_en)
	LDR r1,[r0]
	LDR r0,=0xE000E100
	STR r1,[r0]
	LDR r0,=__cpp(&osekTarget_NestedOsIntMask_pending)
	LDR r1,[r0]
	LDR r0,=0xE000E200
	STR r1,[r0]
	CPSIE I
	bx lr
}
//==========================================================================================
void int_mask_save(unsigned int *value) {

  *value=1;
  
 

}
void int_mask_restore(unsigned int value){

    
}
void int_fit_restore(unsigned int value){

}
void int_vector_save(unsigned int *value){
  
}

#endif //#if defined(CONFIG_OSEK_TARGET_HCS12X)
