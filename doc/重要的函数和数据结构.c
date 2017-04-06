// ***** The important func and struct  *****//

// *******************  9S12  *****************//

// ************ 任务上下文结构体  ************//
typedef struct T_OSEK_TARGET_TaskContext_struct
{


OSWORD CCR;
OSWORD sp;
OSWORD X;
OSWORD Y;
OSBYTE PAGE;
OSWORD pc;


}T_OSEK_TARGET_TaskContext_struct;  

/// 任务的配置结构
typedef struct T_OSEK_TASK_ConfigTable_Struct
{

	/// 任务入口
	T_OSEK_TASK_Entry entry;
	/// 任务的ID(0-255)，在BCC1和ECC1时，系统最多支持64个任务，并且任务的优先级与ID号相关
	TaskType taskId;

// 应用模式大于1，表示系统中有多个模式
#if (CONFIG_OSEK_SYSTEM_APPMODES > 1)
	/// 是否要系统自动启动任务，每个位表示一个模式，如果需要在该模式启动任务，则将该变量的对应位置位（该属性在应用模式大于1时才有效）
	OSDWORD autoStart;
#endif

	/// 配置任务的属性：是否启动时激活任务、是否是扩展任务、是否是非抢占任务
	OSBYTE property;

// 扩展任务的栈配置
#if defined(CONFIG_OSEK_SYSTEM_ET)
	/// 扩展任务的栈顶（在配置了扩展任务时该属性才存在）
	OSBYTEPTR stackTop;
	/// 扩展任务的栈底（在配置了扩展任务时该属性才存在）
	OSBYTEPTR stackBottom;
#endif

// 当使用内部资源时
#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
	/// 使用内部资源时任务的优先级（在配置了内部资源时该属性才存在）
	OSPRIOTYPE inresPriority;
#endif

// 允许一个优先级上有多个任务时
#if defined(CONFIG_OSEK_SYSTEM_EP)
	/// 任务的优先级（允许一个优先级上有多个任务时该属性才存在）
	OSPRIOTYPE basePriority;
	/// 基本任务的最大激活次数（允许一个优先级上有多个任务时该属性才存在）
	OSBYTE maxActive;
#endif

}T_OSEK_TASK_ConfigTable_Struct;


/// 任务的控制结构
typedef struct T_OSEK_TASK_ControlBlock_Struct
{

	/// 任务状态信息，其中0-1位表示基本状态（0－运行，1－等待，2－就绪，3－挂起），位2表示任务是第一次运行
	TaskStateType status;

// 允许一个优先级上有多个任务时
#if defined(CONFIG_OSEK_SYSTEM_EP)
	/// 任务的当前激活次数（允许一个优先级上有多个任务时该属性才存在）
	OSBYTE curActiveNum;
#endif

	/// 任务的当前优先级；
	OSPRIOTYPE curPriority;
    /// 任务的配置表
    T_OSEK_TASK_ConfigTable configTable;

// 当使用扩展任务时
#if defined(CONFIG_OSEK_SYSTEM_ET)
	/// 任务要等待的事件，最多32个事件（当配置了扩展任务时该属性才存在）
	EventMaskType waitEvent;
	/// 任务被设置的事件，最多32个事件（当配置了扩展任务时该属性才存在）
	EventMaskType setEvent;
#endif

	/// 任务上下文，如果系统中只有基本任务是没有任务上下文的
	T_OSEK_TARGET_TaskContext      *context;

// 当使用了资源
#if defined(CONFIG_OSEK_RESOURCE)
	/// 任务使用的资源的链表（当配置了资源时该属性才存在）
	ResourceType resourceList;
#endif

}T_OSEK_TASK_ControlBlock_Struct;

// 用于在就绪队列中排队的就绪块结构
typedef struct T_OSEK_TASK_ReadyBlock_Struct
{
	struct T_OSEK_TASK_ReadyBlock_Struct   *nextTask;			// 下一个就绪的任务节点
	T_OSEK_TASK_ControlBlock_Struct *taskControlBlock; // 指向对应任务控制块的指针
}T_OSEK_TASK_ReadyBlock_Struct;

// 就绪任务队列表结构
typedef struct
{

	T_OSEK_TASK_ReadyBlock_Struct *readyTaskHead; // 就绪任务队列的头指针
	T_OSEK_TASK_ReadyBlock_Struct *readyTaskTail; // 就绪任务队列的尾指针

}T_OSEK_TASK_ReadyTaskTableItem;

OSWORD osekTarget_SaveContext( void *context) 
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

#define OSEK_TARGET_SaveBTSP(sp) 	  	(osekTarget_SavedBTSP = (sp) - (OSWORD)0x20)
#define osekTarget_LoadBTSP()	  	  	__asm(LDS osekTarget_SavedBTSP)
#define osekTarget_LoadETSP(sp)   		{unsigned char*temp=sp;__asm(LDS temp);}


#define OSEK_TARGET_OSIntSave( osIntSave ) OSWORD osIntSave

#define OSEK_TARGET_DisableOSInt(osIntSave)  {__asm PSHCW ;__asm PULD ; __asm STD osIntSave;DisableInterrupts}
#define OSEK_TARGET_EnableOSInt(osIntSave)   {__asm(LDD osIntSave);__asm(PSHD);__asm(PULCW);}


#define OSEK_TARGET_DisableOSIntWithoutSave()  DisableInterrupts
#define OSEK_TARGET_EnableOSIntWithoutSave()   EnableInterrupts

#define OSEK_TARGET_DisableAllInt()   {__asm PSHCW;__asm PULD; __asm STD osekTarget_AllIntMask ;DisableInterrupts;} 
#define OSEK_TARGET_EnableAllInt() 	  {__asm LDD osekTarget_AllIntMask ;__asm PSHD ;__asm PULCW;} 

#define OSEK_TARGET_DisableNestedAllInt()	{__asm(PSHCW);__asm(PULD);__asm(STD osekTarget_NestedAllIntMask);DisableInterrupts;}
#define OSEK_TARGET_EnableNestedAllInt()    {__asm(LDD osekTarget_NestedAllIntMask);__asm(PSHD);__asm(PULCW);}

#define OSEK_TARGET_DisableNestedOsInt()   {__asm(PSHCW);__asm(PULD);__asm(STD osekTarget_NestedOsIntMask);DisableInterrupts;}
#define OSEK_TARGET_EnableNestedOsInt()    {__asm(LDD osekTarget_NestedOsIntMask);__asm(PSHD);__asm(PULCW);}

/*CLEAR_IPL is used to clear IPL bits when a new task is activated in ISR state*/ 
#define CLEAR_IPL {__asm(TFR CCRH,A);__asm(ANDA #$F8);__asm(TFR A,CCRH);}

#endif 