/****************本文件是自动生成的,请勿修改 !****************************/




#ifndef OCC_OSPROP_H
#define OCC_OSPROP_H

/**************************** 引用部分 *********************************/


/**************************** 声明部分 *********************************/


/**************************** 定义部分 *********************************/
#define CONFIG_OSEK_OCC


/* 操作系统对象宏定义 */
//目标板类型定义
#define		OCC_CORTEXM0

//系统状态定义
#define		OCC_EXTSTATUS

//符合类定义
#define		OCC_ECC2

//调试级别定义
#define		OCC_ORTIDEBUGLEVEL		

//STKCHECK定义
#define		OCC_STKCHECK

//HOOKSTARTUP定义
//#define		OCC_HOOKSTARTUP

//HOOKSHUTDOWN定义
//#define		OCC_HOOKSHUTDOWN

//中断总数
#define		OCC_ISRLEVELNUM		128

//中断栈大小定义
#define		OCC_ISRSTACKSIZE		1024



/* 应用模式对象宏定义 */ 
//APPMODE对象总数
#define		OCC_NAPPMODES		1



/* 中断对象宏定义 */
//中断类型定义
#define		OCC_ISR2



/* 任务对象宏定义 */
//任务调度策略
#define		OCC_FULLPREEMPT


//任务总数包含空闲任务
#define		OCC_NTSKS		5

//就绪任务队列最大数
#define		OCC_TOTALACTIVENUMBER		5



/* 计数器对象宏定义 */
//COUNTER对象总数宏定义
#define		OCC_NCTRS		1
#define		OCC_COUNTER



/* 报警对象宏定义 */
//ALARM对象总数
#define		OCC_NALMS		1
#define		OCC_ALARM


//报警机制的宏定义
#define		OCC_ALMACTIVTASK



/* 消息对象宏定义 */
//通讯范围
#define	OCC_LOCALMESSAGESONLY

//通讯机制
#define	OCC_SIGACTIVTASK


#if defined (OCC_LOCALMESSAGESONLY)
//MESSAGE对象总数宏定义
#define		OCC_NMSGS		2

//消息标志总数
#define		OCC_NFLAGS		0

//队列型消息总数
#define		OCC_NQUEMSGS		0


#endif  /* OCC_LOCALMESSAGESONLY */




#endif/*	ifndef OCC_OSPROP_H	*/



