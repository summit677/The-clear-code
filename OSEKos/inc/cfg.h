/****************���ļ����Զ����ɵ�,�����޸� !****************************/




#ifndef OCC_CFG_H
#define OCC_CFG_H

/**************************** ���ò��� *********************************/


/**************************** �������� *********************************/


/**************************** ���岿�� *********************************/


/* Ӧ��ģʽ������ */ 
//APPMODE�������кŵĶ���
#define		OSDEFAULTAPPMODE		0


/* �ж϶����� */
//�жϷ��������ں�������
extern		void		Ir_RealTimInt(void);



/* ��������� */
//Task������Ŷ���
#define		TaskError		0
#define		Task1		4
#define		Task2		2
#define		Task3		3

//������ں�������
extern	void	FuncTaskError(void);
extern	void	FuncTask1(void);
extern	void	FuncTask2(void);
extern	void	FuncTask3(void);




/* ������������ */
//COUNTER�����ID����
#define		SysCounter		0


/* ���������� */
//ALARM����������б���
#define		AlarmError		&osekAlarm_AlarmTable[0]




/* ��Ϣ����궨�� */
//Message�������ض���
#if defined (OCC_LOCALMESSAGESONLY)
//��ϢID�Ķ���
#define		Msg1		&osekMsg_MessageTable[0]
#define		Msg4		&osekMsg_MessageTable[1]

#include "userMSG.h"

//��Ϣʵ����ⲿ��������
extern		string		osekMsg_Msg1Object;
extern		uint8		osekMsg_Msg4Object;

//��Ϣ��־����ID�Ķ���



//�����з�������Ϣ����

//�ǿ�������
#define		MsgBuffer_21_out		osekMsg_Msg1Object

//�����з�������Ϣ����

//�ǿ�������
#define		MsgBuffer_34_out		osekMsg_Msg4Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_11_in		osekMsg_Msg1Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_14_in		osekMsg_Msg4Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_21_in		osekMsg_Msg1Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_24_in		osekMsg_Msg4Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_34_in		osekMsg_Msg4Object

//�����������Ϣ����

//�ǿ�������
#define		MsgBuffer_31_in		osekMsg_Msg1Object

//��Ϣ�ص�ԭ�Ͷ���

#endif  /* OCC_LOCALMESSAGESONLY */




#endif/*	ifndef OCC_CFG_H	*/



