/****************本文件是自动生成的,请勿修改 !****************************/




#ifndef OCC_CFG_H
#define OCC_CFG_H

/**************************** 引用部分 *********************************/


/**************************** 声明部分 *********************************/


/**************************** 定义部分 *********************************/


/* 应用模式对象定义 */ 
//APPMODE对象序列号的定义
#define		OSDEFAULTAPPMODE		0


/* 中断对象定义 */
//中断服务程序入口函数声明
extern		void		Ir_RealTimInt(void);



/* 任务对象定义 */
//Task对象序号定义
#define		TaskError		0
#define		Task1		4
#define		Task2		2
#define		Task3		3

//任务入口函数引用
extern	void	FuncTaskError(void);
extern	void	FuncTask1(void);
extern	void	FuncTask2(void);
extern	void	FuncTask3(void);




/* 计数器对象定义 */
//COUNTER对象的ID定义
#define		SysCounter		0


/* 报警对象定义 */
//ALARM对象的配置列表定义
#define		AlarmError		&osekAlarm_AlarmTable[0]




/* 消息对象宏定义 */
//Message对象的相关定义
#if defined (OCC_LOCALMESSAGESONLY)
//消息ID的定义
#define		Msg1		&osekMsg_MessageTable[0]
#define		Msg4		&osekMsg_MessageTable[1]

#include "userMSG.h"

//消息实体的外部引用声明
extern		string		osekMsg_Msg1Object;
extern		uint8		osekMsg_Msg4Object;

//消息标志类型ID的定义



//任务中发送者消息对象

//非拷贝对象
#define		MsgBuffer_21_out		osekMsg_Msg1Object

//任务中发送者消息对象

//非拷贝对象
#define		MsgBuffer_34_out		osekMsg_Msg4Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_11_in		osekMsg_Msg1Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_14_in		osekMsg_Msg4Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_21_in		osekMsg_Msg1Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_24_in		osekMsg_Msg4Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_34_in		osekMsg_Msg4Object

//任务接收者消息对象

//非拷贝对象
#define		MsgBuffer_31_in		osekMsg_Msg1Object

//消息回调原型定义

#endif  /* OCC_LOCALMESSAGESONLY */




#endif/*	ifndef OCC_CFG_H	*/



