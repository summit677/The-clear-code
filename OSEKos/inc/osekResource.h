/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/**
 * $Log: osekResource.h,v $
 * Revision 1.0  2008/03/11 14:23:00
 * �����ļ�
*/

/**
 * @file 	osekResource.h
 * @brief
 *	<li>���ܣ�������Դ��ص����ݽṹ���ꡢ�����ȡ�</li>
 * @author
 * @date 	2008-03-11
 * <p>���ţ�
 */

/**
 * \defgroup  Resource ��Դ
 * ��Դ����ģ��,��Ҫʵ����Դ�Ĺ���
 */
/**@{*/
/** @name ��Դ����ģ��*/
//@{


#ifndef _OSEK_RESOURCE_H
#define _OSEK_RESOURCE_H

/**************************** ���ò��� *********************************/

#ifdef __cplusplus
extern "C" {
#endif

/**************************** �������� *********************************/

// �ڲ�����
void osekResource_Initialize( void );
// �ж�����Ĵ�������
extern void int_mask_save(unsigned int *value);
extern void int_mask_restore(unsigned int value);
extern void int_fit_restore(unsigned int value);
extern void int_vector_save(unsigned int *value);


// ��Դ�����ṩ���ⲿ�Ĺ������ú���

/**
 * @brief
 *    GetResource����ȡ��Դ��
 * @param[in]	resId��ָ����Դ���ƿ��ָ�롣
 * @returns     E_OK���ɹ�
 * @returns     [E_OS_ID]: ��ԴID���Ϸ�
 * @returns     [E_OS_ACCESS]:��Դ�ѱ�ʹ�ã����������ȼ�������Դ���ȼ�����ϵͳ���ڹص��ȣ���û����ȷ��ʹ���ж���Դ
 */
StatusType GetResource( ResourceType resId );

/**
 * @brief
 *    ReleaseResource���ͷ���Դ��
 * @param[in]	resId��ָ����Դ���ƿ��ָ�롣
 * @returns     E_OK:�ɹ�
 * @returns     E_OS_NOFUNC:�ͷŵ��ǵ�������Դ��ϵͳδ�ص���
 * @returns     [E_OS_ID]: ��ԴID���Ϸ�
 * @returns     [E_OS_NOFUNC]: ��Դδ��ʹ�ã���Ҫ�ͷŵĲ���������Դ�б��ͷ�ڵ㣨δ����ȷ˳���ͷ���Դ������δ��ȷʹ���ж���Դ
 * @returns     [E_OS_ACCESS]: �������ȼ�������Դ���ȼ�����ϵͳ���ڹص���
 */
StatusType ReleaseResource( ResourceType resId );




/**************************** ���岿�� *********************************/

/// ��Դ�Ŀ��ƽṹ
typedef struct T_OSEK_RESOURCE_ControlBlock_Struct
{

// ���ʹ������չ״̬
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	/// ��ԴID�ţ�����������չ����״̬ʱ�����ԲŴ��ڣ�
	ResourceType    resourceId;
	/// ��Դ�Ƿ�ʹ�ã�����������չ����״̬ʱ�����ԲŴ��ڣ�
	OSBYTE          isUsed;
#endif

// ���ʹ�����ж���Դ
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	/// ����ռ����Դ֮ǰ���ж����루���������ж���Դʱ�����ԲŴ��ڣ�
	IntMaskType 		savedIsrMask;
#endif

	/// ��Դ�����ȼ�
	OSPRIOTYPE      ceilingPriority;
	/// �����ȡ����Դ��ĵ�ǰ���ȼ�������ֹ����Դ��ȡ���������ȼ���
	OSPRIOTYPE		currentPriority;
	/// ָ����һ����Դ
	ResourceType    nextResource;

}T_OSEK_RESOURCE_ControlBlock_Struct;


#define DeclareResource(resource)

#if defined(CONFIG_OSEK_RESOURCE_ISR)


#define OSEK_ISR_MaskSave(save) \
    int_mask_save(save)

#define OSEK_ISR_MaskRestore(save) \
    int_mask_restore(save)

#define OSEK_FIT_MaskRestore(save) \
    int_fit_restore(save)

#define OSEK_ISR_VectorSave(save) \
    int_vector_save(save)

#define OSEK_ISR_MaskConversion(save, resLevel) \
    save = resLevel
    //save = ~( (1 << (32 - resLevel)) - 1 )


#define OSEK_ISR_MaskFirstMorethenSecond(mask1, mask2) \
    mask1 > mask2

#define OSEK_ISR_MaskCopyFirst2Second(mask1, mask2) \
    mask2 = mask1

#endif


// ��������
#if CONFIG_OSEK_RESOURCE_NUMBER > 0
// ��Դ���ƿ������
extern T_OSEK_RESOURCE_ControlBlock osekResource_ResourceTable[CONFIG_OSEK_RESOURCE_NUMBER];
/// ��Դ���ȼ����ñ�����������������Դʱ�ñ����Ŵ��ڣ�
extern OSPRIOTYPE osekConfig_ResourcePriorityTable[CONFIG_OSEK_RESOURCE_NUMBER];
#endif

#if defined(CONFIG_OSEK_RESOURCE_SCHEDULER)
// ��������Դ���ƿ�����
extern T_OSEK_RESOURCE_ControlBlock osekResource_Scheduler;
/// ��������Դ���������������˵�������Դʱ�ú�Ŵ��ڣ�
#define RES_SCHEDULER              &osekResource_Scheduler
#endif

#if defined(CONFIG_OSEK_RESOURCE_ISR)
// �ж���Դ���ƿ�������
extern ResourceType    osekResource_ISRLast;
#endif



#ifdef __cplusplus
}
#endif

#endif

/* end of include file */
//@}
/** @}*/
