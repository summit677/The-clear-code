#line 1 "OSEKos\\osekEvent.c"




 





 








 


 

#line 1 ".\\OSEKos\\inc\\osprop.h"
 







 


 


 



 





























  





 





 












 






 










 



























#line 26 "OSEKos\\osekEvent.c"

#line 1 ".\\OSEKos\\inc\\osapi.h"




 





 








 










#line 1 ".\\OSEKos\\inc\\osekOccConfig.h"




 





 








 






 


 


 























































#line 95 ".\\OSEKos\\inc\\osekOccConfig.h"





























































































































































































































































































#line 33 ".\\OSEKos\\inc\\osapi.h"


























































typedef unsigned char       OSBYTE;

typedef unsigned char      *OSBYTEPTR;

typedef unsigned short      OSWORD;

typedef unsigned short      *OSWORDPTR;

typedef unsigned long        OSDWORD;



typedef unsigned char       OSCARDINAL;

typedef signed long          OSSIGNEDDWORD;

typedef signed short         OSPRIOTYPE;

typedef OSDWORD             OSTASKTYPE;


typedef OSBYTE			AppModeType;

typedef unsigned char   StatusType;


typedef OSDWORD			TaskType;

typedef TaskType		*TaskRefType;

typedef OSBYTE			TaskStateType;

typedef TaskStateType	*TaskStateRefType;


typedef OSDWORD			EventMaskType;

typedef EventMaskType	*EventMaskRefType;

typedef OSDWORD			IntMaskType;


typedef void          (*OSCALLBACK)( void );




typedef unsigned char      *FlagType;

typedef unsigned char       FlagValue;

typedef OSBYTE              OSMSGIDTYPE;

typedef void*               AccessNameRef;










typedef void (*T_OSEK_TASK_Entry)( void );  









typedef struct T_OSEK_RESOURCE_ControlBlock_Struct *ResourceType;

typedef struct T_OSEK_RESOURCE_ControlBlock_Struct T_OSEK_RESOURCE_ControlBlock;


typedef struct T_OSEK_TARGET_TaskContext_struct T_OSEK_TARGET_TaskContext;

typedef struct T_OSEK_TARGET_ExceptionFrame_struct T_OSEK_TARGET_ExceptionFrame;


typedef struct T_OSEK_TASK_ControlBlock_Struct T_OSEK_TASK_ControlBlock;
typedef struct T_OSEK_TASK_ReadyBlock_Struct T_OSEK_TASK_ReadyBlock;


typedef struct T_OSEK_TASK_ConfigTable_Struct T_OSEK_TASK_ConfigTable;


typedef struct T_OSEK_COUNTER_ControlBlock_Struct  T_OSEK_COUNTER_ControlBlock;


typedef struct T_OSEK_COUNTER_ConfigTable_Struct T_OSEK_COUNTER_ConfigTable;


typedef struct T_OSEK_ALARM_ControlBlock_Struct T_OSEK_ALARM_ControlBlock;


typedef struct T_OSEK_ALARM_ConfigTable_Struct T_OSEK_ALARM_ConfigTable;


typedef struct T_OSEK_ALARM_AutoTypeConfigTable_Struct T_OSEK_ALARM_AutoTypeConfigTable;


typedef struct T_OSEK_MESSAGE_ControlBlock_Struct  T_OSEK_MESSAGE_ControlBlock;

typedef T_OSEK_MESSAGE_ControlBlock*        MsgType;


typedef struct T_OSEK_MESSAGE_ConfigTable_Struct  T_OSEK_MESSAGE_ConfigTable;



typedef OSDWORD             TickType;

typedef TickType*           TickRefType;


typedef unsigned char       CtrType;


typedef T_OSEK_COUNTER_ConfigTable     CtrInfoType;

typedef CtrInfoType*        CtrInfoRefType;





typedef void          (*T_OSEK_ALARM_CallBackEntry)( void );


typedef T_OSEK_ALARM_ControlBlock*            AlarmType;

typedef T_OSEK_COUNTER_ConfigTable            AlarmBaseType;

typedef AlarmBaseType*      AlarmBaseRefType;



typedef OSBYTE  OSSERVICEIDTYPE;

#line 311 ".\\OSEKos\\inc\\osapi.h"


#line 344 ".\\OSEKos\\inc\\osapi.h"



#line 1 ".\\OSEKos\\inc\\osekTarget.h"




 





 








 


#line 1 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "F:\\LouisSoftware\\Keil5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 26 ".\\OSEKos\\inc\\osekTarget.h"
#line 27 ".\\OSEKos\\inc\\osekTarget.h"
#line 1 ".\\OSEKos\\inc\\osapi.h"




 





 








 


#line 375 ".\\OSEKos\\inc\\osapi.h"

#line 28 ".\\OSEKos\\inc\\osekTarget.h"
#line 29 ".\\OSEKos\\inc\\osekTarget.h"
#line 1 ".\\OSEKos\\inc\\cfg.h"
 







 


 


 


  




 

extern		void		Ir_RealTimInt(void);



 







extern	void	FuncTaskError(void);
extern	void	FuncTask1(void);
extern	void	FuncTask2(void);
extern	void	FuncTask3(void);




 




 






 






#line 1 ".\\OSEKos\\inc\\userMSG.h"







 












 
typedef struct
{
   char msgbuffer[6];
} string;















#line 65 ".\\OSEKos\\inc\\cfg.h"


extern		string		osekMsg_Msg1Object;
extern		unsigned char		osekMsg_Msg4Object;
























































#line 30 ".\\OSEKos\\inc\\osekTarget.h"
 












OSDWORD osekTarget_SaveContext( void * savedContext );
void osekTarget_RestoreContext( void * restoredContext );



void osekTarget_LoadETSP(void* sp) ;
void osekTarget_LoadBTSP( void );
void osekTarget_SaveBTSP(OSWORD sp );


extern OSWORD	osIntSave_en;
extern OSWORD osIntSave_pending;
extern OSWORD osekTarget_AllIntMask_en;
extern OSWORD osekTarget_AllIntMask_pending;
extern OSWORD osekTarget_NestedAllIntMask_en;
extern OSWORD osekTarget_NestedAllIntMask_pending;
extern OSWORD osekTarget_NestedOsIntMask_en;
extern OSWORD osekTarget_NestedOsIntMask_pending;

extern OSWORD osekTarget_SavedBTSP;


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













void OSEK_TARGET_DisableOSInt_func();



#line 109 ".\\OSEKos\\inc\\osekTarget.h"
 
void OSEK_TARGET_EnableOSInt(OSWORD osIntSave);


#line 121 ".\\OSEKos\\inc\\osekTarget.h"
 










void OSEK_TARGET_DisableAllInt();


#line 143 ".\\OSEKos\\inc\\osekTarget.h"
 
void OSEK_TARGET_EnableAllInt();


#line 155 ".\\OSEKos\\inc\\osekTarget.h"
 




void OSEK_TARGET_DisableNestedAllInt();


#line 171 ".\\OSEKos\\inc\\osekTarget.h"
 
void OSEK_TARGET_EnableNestedAllInt();


#line 183 ".\\OSEKos\\inc\\osekTarget.h"
 




void OSEK_TARGET_DisableNestedOsInt();


#line 199 ".\\OSEKos\\inc\\osekTarget.h"
 
void OSEK_TARGET_EnableNestedOsInt();


#line 211 ".\\OSEKos\\inc\\osekTarget.h"
 













#line 348 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekInterrupt.h"




 





 








 




 
 
 






 







 


extern OSDWORD osekInterrupt_NestedLevl;


void osekInterrupt_Initialize( void );








 
void DisableAllInterrupts( void );






 
void EnableAllInterrupts( void );






 
void SuspendAllInterrupts( void );






 
void ResumeAllInterrupts( void );






 
void SuspendOSInterrupts( void );






 
void ResumeOSInterrupts( void );


 












 

 
#line 350 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekHook.h"




 





 








 




 
 
 






 







 











 








#line 70 ".\\OSEKos\\inc\\osekHook.h"


#line 79 ".\\OSEKos\\inc\\osekHook.h"




void StartupHook( void );








void ShutdownHook( StatusType error );






#line 106 ".\\OSEKos\\inc\\osekHook.h"



#line 119 ".\\OSEKos\\inc\\osekHook.h"



#line 139 ".\\OSEKos\\inc\\osekHook.h"














 

 
#line 352 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekTask.h"




 





 








 




 
 
 






#line 35 ".\\OSEKos\\inc\\osekTask.h"
 







 










 
StatusType ActivateTask( TaskType taskId );








 
StatusType TerminateTask( void );










 
StatusType ChainTask( TaskType taskId );









 
StatusType Schedule( void );







 
StatusType GetTaskID( TaskRefType taskId );









 
StatusType GetTaskState ( TaskType taskId, TaskStateRefType state );


void osekTask_Dispatch( void );
void osekTask_TerminateDispatch( void );
void osekTask_WaitTask( void );
void osekTask_ChangeRunningTaskPriority( OSPRIOTYPE newPri );
void osekTask_Initialize( void );


 


































typedef struct T_OSEK_TASK_ConfigTable_Struct
{

	
	T_OSEK_TASK_Entry entry;
	
	TaskType taskId;







	
	OSBYTE property;


#line 177 ".\\OSEKos\\inc\\osekTask.h"








#line 191 ".\\OSEKos\\inc\\osekTask.h"

}T_OSEK_TASK_ConfigTable_Struct;



typedef struct T_OSEK_TASK_ControlBlock_Struct
{

	
	TaskStateType status;







	
	OSPRIOTYPE curPriority;
    
    T_OSEK_TASK_ConfigTable configTable;


#line 220 ".\\OSEKos\\inc\\osekTask.h"

	
	T_OSEK_TARGET_TaskContext      *context;







}T_OSEK_TASK_ControlBlock_Struct;


typedef struct T_OSEK_TASK_ReadyBlock_Struct
{
	struct T_OSEK_TASK_ReadyBlock_Struct   *nextTask;			
	T_OSEK_TASK_ControlBlock_Struct *taskControlBlock; 
}T_OSEK_TASK_ReadyBlock_Struct;


typedef struct
{

	T_OSEK_TASK_ReadyBlock_Struct *readyTaskHead; 
	T_OSEK_TASK_ReadyBlock_Struct *readyTaskTail; 

}T_OSEK_TASK_ReadyTaskTableItem;



extern T_OSEK_TASK_ReadyTaskTableItem osekTask_ReadyTaskTable[];


extern T_OSEK_TASK_ControlBlock_Struct osekTask_TaskTable[];


extern const T_OSEK_TASK_ConfigTable_Struct osekConfig_TaskTable[];


extern T_OSEK_TASK_ReadyBlock_Struct *osekTask_RunningTask;


extern T_OSEK_TASK_ReadyBlock_Struct osekTask_ReadyBlock[];

extern T_OSEK_TASK_ReadyBlock_Struct *osekTask_FreeReadyBlock;


extern OSDWORD osekTask_IsrTriggeredTaskSwitchNecessary;




#line 353 ".\\OSEKos\\inc\\osekTask.h"



extern OSDWORD osekTask_SchedulerLockLevel;





extern OSBYTE osekTask_PriorityBitMap[( (OSBYTE) (32) ) >> 3];

extern OSBYTE osekTask_PriorityBitMapMajor;

extern OSBYTE osekTask_PriorityIndexTable[256];









#pragma INLINE
static  void ClearPriorityMap( OSPRIOTYPE pri)
{
	if( osekTask_ReadyTaskTable[(pri)].readyTaskHead == ((void *)0) )
	{
		OSPRIOTYPE index = ((pri)>>3) ;
		osekTask_PriorityBitMap[index] &= (~(1<<((pri)&7))) ;
		if( osekTask_PriorityBitMap[index] == 0 )
		{
			osekTask_PriorityBitMapMajor &= (~(1 << index)) ;
		}
	}
}














#pragma INLINE
static  void AddTask2ReadyTableAtTail( T_OSEK_TASK_ReadyBlock *readyblockptr)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	



	chain = &osekTask_ReadyTaskTable[(32 - (readyblockptr->taskControlBlock->configTable . taskId) - 1)];


	(readyblockptr)->nextTask = ((void *)0) ;
	if( chain->readyTaskHead == ((void *)0) )
	{
		chain->readyTaskHead = (readyblockptr);
	}
	else
	{
		chain->readyTaskTail->nextTask = (readyblockptr);
	}
	chain->readyTaskTail = (readyblockptr);

}






static  void AddTask2ReadyTableAtHead( T_OSEK_TASK_ReadyBlock *readyblockptr)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	
	chain = &osekTask_ReadyTaskTable[readyblockptr->taskControlBlock->curPriority];
	(readyblockptr)->nextTask = chain->readyTaskHead ;
	if( chain->readyTaskTail == ((void *)0) )
	{
		chain->readyTaskTail = (readyblockptr);
	}
	chain->readyTaskHead = (readyblockptr);

}




static  StatusType AddaReadyBlock( T_OSEK_TASK_ControlBlock *tcbPtr )
{
	T_OSEK_TASK_ReadyBlock *readyBlock;

	if(osekTask_FreeReadyBlock!=((void *)0))
	{
		readyBlock = osekTask_FreeReadyBlock;
		osekTask_FreeReadyBlock = osekTask_FreeReadyBlock->nextTask;

		readyBlock->taskControlBlock = tcbPtr;

		



		do { osekTask_PriorityBitMap[((32 - (tcbPtr->configTable . taskId) - 1))>>3] |= (1<<(((32 - (tcbPtr->configTable . taskId) - 1))&7)) ; osekTask_PriorityBitMapMajor |= (1 << (((32 - (tcbPtr->configTable . taskId) - 1))>>3)); }while(0);

		(AddTask2ReadyTableAtTail(readyBlock));

		return ( (StatusType)0 );
	}
	else
	{
		return ( (StatusType)4 );
	}

}




static  void ReleaseReadyBlock( T_OSEK_TASK_ReadyBlock *readyBlock )
{

	readyBlock->nextTask = osekTask_FreeReadyBlock;
	osekTask_FreeReadyBlock = readyBlock;

}




static  void MoveTaskFromReadyTable(OSPRIOTYPE pri)
{
	T_OSEK_TASK_ReadyTaskTableItem *chain;

	chain = &osekTask_ReadyTaskTable[(pri)];
	chain->readyTaskHead = chain->readyTaskHead->nextTask;  
	if(chain->readyTaskHead == ((void *)0) )
	{
		chain->readyTaskTail = ((void *)0);
	}
}
#pragma NO_INLINE







StatusType osekTask_ActiveTask(T_OSEK_TASK_ControlBlock *tcbPtr);
StatusType osekTask_WakeTask(T_OSEK_TASK_ControlBlock *tcbPtr);







 

 
#line 354 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekResource.h"




 





 








 




 
 
 






 





 


void osekResource_Initialize( void );

extern void int_mask_save(unsigned int *value);
extern void int_mask_restore(unsigned int value);
extern void int_fit_restore(unsigned int value);
extern void int_vector_save(unsigned int *value);











 
StatusType GetResource( ResourceType resId );










 
StatusType ReleaseResource( ResourceType resId );




 


typedef struct T_OSEK_RESOURCE_ControlBlock_Struct
{



	
	ResourceType    resourceId;
	
	OSBYTE          isUsed;








	
	OSPRIOTYPE      ceilingPriority;
	
	OSPRIOTYPE		currentPriority;
	
	ResourceType    nextResource;

}T_OSEK_RESOURCE_ControlBlock_Struct;




#line 137 ".\\OSEKos\\inc\\osekResource.h"



#line 146 ".\\OSEKos\\inc\\osekResource.h"

#line 153 ".\\OSEKos\\inc\\osekResource.h"














 

 
#line 356 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekExecution.h"




 





 








 




 
 
 






 







 








 
void StartOS( AppModeType mode );






 
void ShutdownOS( StatusType error );


extern OSBYTE osekExecution_CurrentAppMode;


 






 











 

 
#line 358 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekCounter.h"




 





 








 




 
 
 






 






 












 
StatusType InitCounter( CtrType ctrId, TickType value );








 
StatusType GetCounterValue( CtrType ctrId, TickRefType ticks );







 
StatusType CounterTrigger( CtrType ctrId );








 
StatusType GetCounterInfo( CtrType ctrId, CtrInfoRefType info );


void osekCounter_Initialize( void );


 


typedef struct T_OSEK_COUNTER_ConfigTable_Struct
{
    
    TickType        maxallowedvalue;
    
    TickType        ticksperbase;



    
    TickType        mincycle;

}T_OSEK_COUNTER_ConfigTable_Struct;


typedef struct T_OSEK_COUNTER_ControlBlock_Struct
{

    
    AlarmType           alarm;

    
    TickType            currentTick;
    
    T_OSEK_COUNTER_ConfigTable    configTable;
}T_OSEK_COUNTER_ControlBlock_Struct;




extern T_OSEK_COUNTER_ControlBlock_Struct osekCounter_CounterTable[];

extern T_OSEK_COUNTER_ConfigTable osekConfig_CounterTable[];









 

 
#line 360 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekAlarm.h"




 





 








 




 
 
 






 





 













 
StatusType SetRelAlarm( AlarmType almId, TickType increment, TickType cycle );









 
StatusType GetAlarm( AlarmType almId, TickRefType tick );








 
StatusType GetAlarmBase( AlarmType almId, AlarmBaseRefType info );











 
StatusType SetAbsAlarm(  AlarmType almId, TickType start, TickType cycle );








 
StatusType CancelAlarm( AlarmType almId );


void osekAlarm_Check1(CtrType ctrId );
StatusType osekAlarm_Check2(AlarmType almId, T_OSEK_COUNTER_ControlBlock *ctrPtr );
void osekAlarm_Initialize( void );


 


typedef struct T_OSEK_ALARM_ConfigTable_Struct
{
	
    TaskType        taskId;






    
    CtrType         ctrId;






}T_OSEK_ALARM_ConfigTable_Struct;


typedef struct T_OSEK_ALARM_ControlBlock_Struct
{
    
    AlarmType       nextAlarm;
    
    AlarmType       prevAlarm;



	
	AlarmType		alarmId;


	
	TickType        expirationTick;
	
	TickType        periodTick;

	
	T_OSEK_ALARM_ConfigTable configTable;
}T_OSEK_ALARM_ControlBlock_Struct;


typedef struct T_OSEK_ALARM_AutoTypeConfigTable_Struct
{
    
    AlarmType       alarmId;
    
    TickType        startTick;
    
    TickType        periodTick;






}T_OSEK_ALARM_AutoTypeConfigTable_Struct;




extern T_OSEK_ALARM_ControlBlock osekAlarm_AlarmTable[1];

extern T_OSEK_ALARM_ConfigTable osekConfig_AlarmTable[1];
















 

 
#line 362 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekEvent.h"




 





 








 




 
 
 






 






 












 
StatusType  SetEvent( TaskType taskId, EventMaskType mask );








 
StatusType  ClearEvent( EventMaskType mask );









 
StatusType  WaitEvent( EventMaskType mask );










 
StatusType  GetEvent( TaskType taskId, EventMaskRefType mask );


StatusType  osekEvent_SetEvent(T_OSEK_TASK_ControlBlock *tcbPtr,EventMaskType   mask);


 











 

 
#line 364 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekDebug.h"




 





 








 




 
 
 






 






 









 
OSDWORD GetRunningStackUsage( void );







 
OSDWORD GetStackUsage( TaskType taskId );






 
OSDWORD GetTimeStamp( void );

extern void read_timer_value(unsigned int *value);

 















 

 
#line 366 ".\\OSEKos\\inc\\osapi.h"

#line 1 ".\\OSEKos\\inc\\osekMessage.h"




 





 








 




 
 
 






 








 


void Msg_Init( void );






 
extern StatusType MessageInit (void);














 
StatusType SendMessage(MsgType msg, AccessNameRef data);












 
StatusType ReceiveMessage(MsgType msg, AccessNameRef data);







 
StatusType StopCOM(OSBYTE ShutdownMode);






 
StatusType StartCOM( void );






 
StatusType InitCOM( void );






 
StatusType CloseCOM( void );


#line 136 ".\\OSEKos\\inc\\osekMessage.h"


#line 155 ".\\OSEKos\\inc\\osekMessage.h"


#line 178 ".\\OSEKos\\inc\\osekMessage.h"



 








typedef struct T_OSEK_MESSAGE_ConfigTable_Struct
{
    
    OSMSGIDTYPE    messageId;
    
    void*          messagePtr;
    
    OSDWORD        messageSize;


    
    TaskType       messageSigTask;

















#line 225 ".\\OSEKos\\inc\\osekMessage.h"
}T_OSEK_MESSAGE_ConfigTable_Struct;


typedef struct T_OSEK_MESSAGE_ControlBlock_Struct
{
    
    OSBYTE          messageStatus;
    
	T_OSEK_MESSAGE_ConfigTable messageConfigTable;

#line 243 ".\\OSEKos\\inc\\osekMessage.h"







}T_OSEK_MESSAGE_ControlBlock_Struct;


extern T_OSEK_MESSAGE_ControlBlock osekMsg_MessageTable[];

extern const T_OSEK_MESSAGE_ConfigTable osekConfig_MsgTable[];


























 

 
#line 368 ".\\OSEKos\\inc\\osapi.h"








#line 28 "OSEKos\\osekEvent.c"

 

 

 

#line 297 "OSEKos\\osekEvent.c"


