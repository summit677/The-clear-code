;********************************************************************************************************
;                                                uC/OS-II
;                                         The Real-Time Kernel
;
;                               (c) Copyright 1992-2010, Micrium, Weston, FL
;                                          All Rights Reserved
;
;                               ARM Cortex-M0 Port (without OS extensions)
;
; File      : OS_CPU_A.ASM
; Version   : V2.86
; By        : Jean J. Labrosse
;
; For       : ARMv6M Cortex-M0 (without OS extensions)
; Mode      : Thumb2
; Toolchain : RealView Development Suite
;             RealView Microcontroller Development Kit (MDK)
;             ARM Developer Suite (ADS)
;             Keil uVision
;********************************************************************************************************

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    EXPORT  osekTarget_SaveContext                                      ; Functions declared in this file
	EXPORT  osekTarget_RestoreContext    

;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************

CM0_SETPEND     EQU     0xE000E200
CM0_IRQ0SET     EQU     0xFFFFFFFF

;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=4
	THUMB
	REQUIRE8
	PRESERVE8

osekTarget_SaveContext
	MRS r1, msp
	;LDR r0,[r0]
	
	STR r1,[r0,#0] ;store sp
	
	MOV lr,r1
	STR r1,[r0,#4] ;store LR
	
	MOV pc,r1
	STR r1,[r0,#8] ;store PC
	
	STR r4,[r0,#16] ;store R4
	STR r5,[r0,#20] ;store R5
	STR r6,[r0,#24] ;store R6
	STR r7,[r0,#28] ;store R7
	MOV r8,r1
	STR r1,[r0,#32] ;store R8
	MOV r9,r1
	STR r1,[r0,#36] ;store R9
	MOV r10,r1
	STR r1,[r0,#40] ;store R10
	MOV r11,r1
	STR r1,[r0,#44] ;store R11
	
	MRS r4,XPSR ;	store xPSR
	STR r4,[r0,#12] ;store xPSR
	
	MRS r4,PRIMASK ;	store primask
	STR r4,[r0,#48] ;store primask
	BX LR;   

osekTarget_RestoreContext
	LDR r0,[r0]
	
	LDR r1,[r0,#0] ;Restore sp
	msr msp,r1
		
	LDR r1,[r0,#4] ;Restore LR
	MOV r1,lr
	
	LDR r1,[r0,#12] ;Restore xPSR
	MSR XPSR,r1 ;	Restore xPSR
	
	LDR r1,[r0,#48] ;Restore primask
	MSR PRIMASK,r1 ;	Restore primask
		
	LDR r4,[r0,#16] ;Restore R4
	LDR r5,[r0,#20] ;Restore R5
	LDR r6,[r0,#24] ;Restore R6
	LDR r7,[r0,#28] ;Restore R7
	
	LDR r1,[r0,#32] ;Restore R8
	MOV r1,r8
	LDR r1,[r0,#36] ;Restore R9
	MOV r1,r9
	LDR r1,[r0,#40] ;Restore R10
	MOV r1,r10
	LDR r1,[r0,#44] ;Restore R11
	MOV r1,r11
	
	LDR r1,[r0,#8] ;Restore pc
	PUSH {r1} ;Restore pc
	
	MOVS r0,#1 ;函数返回值是1
	BX LR;
;*********************************************************************************************************
;                                     POINTERS TO VARIABLES
;*********************************************************************************************************

__osekTarget_SaveContext
    DCD     osekTarget_SaveContext

__osekTarget_RestoreContext
    DCD     osekTarget_RestoreContext
 
    END
