/****************���ļ����Զ����ɵ�,�����޸� !****************************/




#ifndef OCC_OSPROP_H
#define OCC_OSPROP_H

/**************************** ���ò��� *********************************/


/**************************** �������� *********************************/


/**************************** ���岿�� *********************************/
#define CONFIG_OSEK_OCC


/* ����ϵͳ����궨�� */
//Ŀ������Ͷ���
#define		OCC_CORTEXM0

//ϵͳ״̬����
#define		OCC_EXTSTATUS

//�����ඨ��
#define		OCC_ECC2

//���Լ�����
#define		OCC_ORTIDEBUGLEVEL		

//STKCHECK����
#define		OCC_STKCHECK

//HOOKSTARTUP����
//#define		OCC_HOOKSTARTUP

//HOOKSHUTDOWN����
//#define		OCC_HOOKSHUTDOWN

//�ж�����
#define		OCC_ISRLEVELNUM		128

//�ж�ջ��С����
#define		OCC_ISRSTACKSIZE		1024



/* Ӧ��ģʽ����궨�� */ 
//APPMODE��������
#define		OCC_NAPPMODES		1



/* �ж϶���궨�� */
//�ж����Ͷ���
#define		OCC_ISR2



/* �������궨�� */
//������Ȳ���
#define		OCC_FULLPREEMPT


//��������������������
#define		OCC_NTSKS		5

//����������������
#define		OCC_TOTALACTIVENUMBER		5



/* ����������궨�� */
//COUNTER���������궨��
#define		OCC_NCTRS		1
#define		OCC_COUNTER



/* ��������궨�� */
//ALARM��������
#define		OCC_NALMS		1
#define		OCC_ALARM


//�������Ƶĺ궨��
#define		OCC_ALMACTIVTASK



/* ��Ϣ����궨�� */
//ͨѶ��Χ
#define	OCC_LOCALMESSAGESONLY

//ͨѶ����
#define	OCC_SIGACTIVTASK


#if defined (OCC_LOCALMESSAGESONLY)
//MESSAGE���������궨��
#define		OCC_NMSGS		2

//��Ϣ��־����
#define		OCC_NFLAGS		0

//��������Ϣ����
#define		OCC_NQUEMSGS		0


#endif  /* OCC_LOCALMESSAGESONLY */




#endif/*	ifndef OCC_OSPROP_H	*/



