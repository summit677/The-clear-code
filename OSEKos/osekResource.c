/****************************************************************************
 *				���ӿƼ���ѧǶ��ʽ����������� ��Ȩ����
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC. All Rights Reserved.
 ***************************************************************************/

/*
 * $Log: osekResource.c,v $
 * Revision 1.0  2008/04/04 14:55:00
 * �����ļ���
 */

/*
 * @file 	osekResource.c
 * @brief
 *	<li>���ܣ�ʵ�ֶ���Դ�Ĺ���������ȡ���ͷš�</li>
 * @author
 * @date 	2008-04-04
 * <p>���ţ�
 */


/**************************** ���ò��� *********************************/

#include "osprop.h"

#include "osapi.h"
#include <string.h>

#if defined(CONFIG_OSEK_RESOURCE)

/*************************** ǰ���������� ******************************/


/**************************** ���岿�� *********************************/

// ȫ�ֱ���

// ��Դ���ƿ��
#if CONFIG_OSEK_RESOURCE_NUMBER > 0
T_OSEK_RESOURCE_ControlBlock osekResource_ResourceTable[CONFIG_OSEK_RESOURCE_NUMBER];
#endif

#if defined(CONFIG_OSEK_RESOURCE_SCHEDULER)
// ��Դ����������
T_OSEK_RESOURCE_ControlBlock osekResource_Scheduler;
#endif

#if defined(CONFIG_OSEK_RESOURCE_ISR)
// �ж���Դ����ͷ
ResourceType    osekResource_ISRLast;
#endif


/**************************** ʵ�ֲ��� *********************************/

/*
 * @brief
 *    GetResource����ȡ��Դ��
 * @param
 * @param[in]	resId��ָ����Դ���ƿ��ָ�롣
 * @param[out]  �ޡ�
 * @returns:    E_OK���ɹ�
 * <p>          [E_OS_ID]: ��ԴID���Ϸ�
 * <p>          [E_OS_ACCESS]:��Դ�ѱ�ʹ�ã����������ȼ�������Դ���ȼ�����ϵͳ���ڹص��ȣ���û����ȷ��ʹ���ж���Դ
 */

StatusType GetResource( ResourceType resId )
{
	OSEK_TARGET_OSIntSave( osIntSave ) ;
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	OSEK_TARGET_OSIntSave( save ) ;
	OSEK_TARGET_OSIntSave( vector ) ;
#endif

	// ���֧����Դ����������ϵͳ�ص���
#if defined(CONFIG_OSEK_RESOURCE_SCHEDULER)
	if( resId == RES_SCHEDULER )
	{
		if( osekTask_SchedulerLockLevel != 0 )
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}
		else
		{
			osekTask_SchedulerLockLevel++;
			return E_OK;
		}
	}
#endif

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �����ԴID���Ϸ����򷵻�E_OS_ID
	if( resId != resId->resourceId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_GetResource,resId) ;
	}

	// �������Դ�ѱ�ʹ�ã�����E_OS_ACCESS
	if( (resId->isUsed) != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
	}

	//������жϳ����е��÷��ж���Դ������E_OS_ACCESS
	if( osekInterrupt_NestedLevl != 0 )
	{
#if defined(CONFIG_OSEK_RESOURCE_ISR)
		// �ж���Դ�Ĳ���
		if(resId->ceilingPriority < 0)
		{
			// �����Դ���ȼ�С��ԭʼ��̬�����ж����ȼ�������E_OS_ACCESS
			OSEK_ISR_VectorSave(&vector);
			if( ((OSPRIOTYPE)vector)-1 > -(resId->ceilingPriority + 1) )
			{
				OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
			}
		}
		else
#endif /* defined(CONFIG_OSEK_RESOURCE_ISR) */
		{
			// ����Դ�������ж���Դ
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}

	}

#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// ������Դ�Ĳ���
	if(resId->ceilingPriority >= 0)
#endif /* defined(CONFIG_OSEK_RESOURCE_ISR) */
	{
		// ����Դ�������ж���Դ
		if( osekInterrupt_NestedLevl != 0 )
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}

		// �����Դ���ȼ�С����������ԭʼ��̬�����������ȼ�������E_OS_ACCESS
#if defined(CONFIG_OSEK_SYSTEM_EP)
		if( osekTask_RunningTask->taskControlBlock->configTable.basePriority > resId->ceilingPriority )
#else
		if( OSEK_TASK_ID2PRI(osekTask_RunningTask->taskControlBlock->configTable.taskId) > resId->ceilingPriority )
#endif /* #else defined(CONFIG_OSEK_SYSTEM_EP) */
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId);
		}
	}

	// �����������Ϊ0������E_OS_ACCESS
	if( osekTask_SchedulerLockLevel != 0 )
	{
		OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
	}
#endif	// #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)

	OSEK_TARGET_DisableOSInt(osIntSave);

#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// �ж���Դ�Ĳ���
	if(resId->ceilingPriority < 0)
	{
		//�������쳣�ж���Դ�����
	#if defined (CONFIG_OSEK_TARGET_MPC5554)
		if (-(resId->ceilingPriority) == 17)    /* ISR resource for FIT */
		{
			resId->savedIsrMask = 17;
		}
		else
	#endif
		{
			// ��ȡ��ǰ���ж�����ֵ
			OSEK_ISR_MaskSave( &save );

        	resId->savedIsrMask = save;
		}


        // �����ж���Դ���ȼ����ε�ǰ�����͵��ж�
        OSEK_ISR_MaskConversion(save, (-(resId->ceilingPriority + 1)));

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
        // ������Դ����ʹ�ñ�־
        resId->isUsed = 1;
#endif

 		// ������Դ�ҽӵ��жϵ���Դ����
        resId->nextResource = osekResource_ISRLast;
        osekResource_ISRLast = resId;

        // �����µ��ж�����ֵ
        OSEK_ISR_MaskRestore(save);
	}
	else	// ������Դ�Ĳ���
#endif /* defined(CONFIG_OSEK_RESOURCE_ISR) */
	{
#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
		// ������Դ״̬Ϊ��ʹ��
		resId->isUsed = 1;
#endif

		// ������Դ��ӵ��������Դ����
		resId->nextResource = osekTask_RunningTask->taskControlBlock->resourceList;
		osekTask_RunningTask->taskControlBlock->resourceList = resId;

		// �������������ż���������Դ���ȼ�
		if( osekTask_RunningTask->taskControlBlock->curPriority < resId->ceilingPriority )
		{
			osekTask_ChangeRunningTaskPriority(resId->ceilingPriority);
		}
		// chenlr add 2008-12-17
		// ������Դ�ĵ�ǰ���ȼ�
		resId->currentPriority = osekTask_RunningTask->taskControlBlock->curPriority;
	}

	OSEK_TARGET_EnableOSInt(osIntSave);

	return E_OK;

}



/*
 * @brief
 *    ReleaseResource���ͷ���Դ��
 * @param
 * @param[in]	resId��ָ����Դ���ƿ��ָ�롣
 * @param[out]  �ޡ�
 * @returns:    E_OK:�ɹ�
 * <p>          E_OS_NOFUNC:�ͷŵ��ǵ�������Դ��ϵͳδ�ص���
 * <p>          [E_OS_ID]: ��ԴID���Ϸ�
 * <p>          [E_OS_NOFUNC]: ��Դδ��ʹ�ã���Ҫ�ͷŵĲ���������Դ�б��ͷ�ڵ㣨δ����ȷ˳���ͷ���Դ������δ��ȷʹ���ж���Դ
 * <p>          [E_OS_ACCESS]: �������ȼ�������Դ���ȼ�����ϵͳ���ڹص���
 */
StatusType ReleaseResource( ResourceType resId )
{
	OSEK_TARGET_OSIntSave( osIntSave ) ;
#if defined(CONFIG_OSEK_RESOURCE_ISR)
	OSEK_TARGET_OSIntSave( save ) ;
	OSEK_TARGET_OSIntSave( vector ) ;
#endif

#if defined(CONFIG_OSEK_RESOURCE_SCHEDULER)
	// ���֧����Դ���������������������Ƿ���ռ���ͣ�������������
	if( resId == RES_SCHEDULER )
	{
		if( osekTask_SchedulerLockLevel == 0 )
		{
			OSEK_HOOK_ErrorHook(E_OS_NOFUNC,OSServiceId_ReleaseResource,resId) ;
		}
		else
		{
			osekTask_SchedulerLockLevel--;

			if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
			{
				OSEK_TARGET_DisableOSInt(osIntSave);
				osekTask_Dispatch();
				OSEK_TARGET_EnableOSInt(osIntSave);
			}

			return E_OK;
		}
	}
#endif

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
	// �����ԴID���Ϸ����򷵻�E_OS_ID
	if( resId != resId->resourceId )
	{
		OSEK_HOOK_ErrorHook(E_OS_ID,OSServiceId_ReleaseResource,resId) ;
	}

	// �����Դδ��ʹ�ã�����E_OS_NOFUNC
	if( resId->isUsed != 1 )
	{
		OSEK_HOOK_ErrorHook(E_OS_NOFUNC,OSServiceId_ReleaseResource, resId) ;
	}

#if defined(CONFIG_OSEK_RESOURCE_ISR)
    if( resId->ceilingPriority < 0 )	// �ж���Դ�Ĳ���
    {
    	if( osekResource_ISRLast != resId )
        {
            OSEK_HOOK_ErrorHook(E_OS_NOFUNC, OSServiceId_ReleaseResource, resId );
        }

        //������жϳ����е��÷��ж���Դ������E_OS_ACCESS
		if( osekInterrupt_NestedLevl != 0 )
		{
			// �����Դ���ȼ�С��ԭʼ��̬�����ж����ȼ�������E_OS_ACCESS
			OSEK_ISR_VectorSave(&vector);
			if( ((OSPRIOTYPE)vector -1) > -(resId->ceilingPriority + 1) )
			{
				OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
			}
		}

    }
    else	// ������Դ���ֵĲ���
#endif /* defined(CONFIG_OSEK_RESOURCE_ISR) */
    {
		// ���Ҫ�ͷŵĲ���������Դ�б��ͷ�ڵ㣨δ����ȷ˳���ͷ���Դ��������E_OS_NOFUNC
		if( osekTask_RunningTask->taskControlBlock->resourceList != resId )
		{
			OSEK_HOOK_ErrorHook(E_OS_NOFUNC,OSServiceId_ReleaseResource,resId) ;
		}

		// �����������Ϊ0������E_OS_ACCESS
		if( osekTask_SchedulerLockLevel != 0 )
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}

		if (osekInterrupt_NestedLevl != 0 )
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}

		// �����Դ���ȼ�С����������ԭʼ��̬�����������ȼ�������E_OS_ACCESS
#if defined(CONFIG_OSEK_SYSTEM_EP)
		if( osekTask_RunningTask->taskControlBlock->configTable.basePriority > resId->ceilingPriority )
#else
		if( OSEK_TASK_ID2PRI(osekTask_RunningTask->taskControlBlock->configTable.taskId) > resId->ceilingPriority )
#endif /* #else defined(CONFIG_OSEK_SYSTEM_EP) */
		{
			OSEK_HOOK_ErrorHook(E_OS_ACCESS,OSServiceId_GetResource,resId) ;
		}
	}

#else	// #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
#if defined(CONFIG_OSEK_RESOURCE_ISR)
    if( osekInterrupt_NestedLevl != 0 )
   	{
   		return E_OK;
    }
#endif
#endif	// #if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)

	OSEK_TARGET_DisableOSInt(osIntSave);

#if defined(CONFIG_OSEK_RESOURCE_ISR)
    if( resId->ceilingPriority < 0 )	// �ж���Դ�Ĳ���
    {

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
        // �����Դ����ʹ�ñ�־
        resId->isUsed = 0;
        // �����ж���Դ��
        osekResource_ISRLast = resId->nextResource;
#endif
		save = resId->savedIsrMask;

		//�������쳣�ж���Դ�����
	#if defined (CONFIG_OSEK_TARGET_MPC5554)
		if (-(resId->ceilingPriority) == 17)    /* ISR resource for FIT */
		{
			// �����µ��ж�����ֵ
	    	OSEK_FIT_MaskRestore(save);
		}
		else
	#endif
		{
			// �����µ��ж�����ֵ
		    OSEK_ISR_MaskRestore(save);
		}

		OSEK_TARGET_EnableOSInt(osIntSave);

	    // ������ͷ������е��ж���Դ
	    if( osekResource_ISRLast == 0 )
		{
		#if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2) || defined(CONFIG_OSEK_INTERRUPT_ISR_ALL)
			// �����жϷ�������е��øú���ʱ��ʹ���жϴ����������
			if( osekInterrupt_NestedLevl != 0 )
			{
				osekTask_IsrTriggeredTaskSwitchNecessary++;
			}
			// ����ʵʩ����
			else
		#endif /* #if defined(CONFIG_OSEK_INTERRUPT_ONLY_ISR2)|| defined(CONFIG_OSEK_INTERRUPT_ISR_ALL) */
			{
				OSEK_TARGET_DisableOSInt(osIntSave);
				osekTask_Dispatch();
				OSEK_TARGET_EnableOSInt(osIntSave);
			}
		}

    }
    else	// ������Դ�Ĳ���
#endif /* defined(CONFIG_OSEK_RESOURCE_ISR) */
	{

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
		// ������Դ״̬Ϊδʹ��
		resId->isUsed = 0;
#endif

		// ���������������Դ�б�
    	osekTask_RunningTask->taskControlBlock->resourceList = resId->nextResource;

		// �������ӵ��������Դ�������������ȼ���ƥ����Դ�����ȼ��������е���
		resId = resId->nextResource;
		if( resId != 0 )
	    {
	      	if( osekTask_RunningTask->taskControlBlock->curPriority > resId->currentPriority )
	       	{
	       	    osekTask_ChangeRunningTaskPriority( resId->currentPriority );

	            if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
				{
				  	 osekTask_Dispatch();
				}
	        }
	    }
		// ������ӵ���κ���Դ����������²���
	    else
	    {

#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
			// ���ʹ�����ڲ���Դ�������������ȼ��������ڲ���Դ���ȼ�������������ȼ�Ϊ�ڲ���Դ���ȼ���ʵʩ����
	        if( osekTask_RunningTask->taskControlBlock->curPriority > osekTask_RunningTask->taskControlBlock->configTable.inresPriority && osekTask_RunningTask->taskControlBlock->configTable.inresPriority != 0)
	        {
				osekTask_ChangeRunningTaskPriority( osekTask_RunningTask->taskControlBlock->configTable.inresPriority );
				if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
				{
					osekTask_Dispatch();
				}
			}
			// û��ʹ���ڲ���Դ
			else if(osekTask_RunningTask->taskControlBlock->configTable.inresPriority == 0)
			{
#endif /* if defined(CONFIG_OSEK_RESOURCE_INTERNAL) */

#if defined(CONFIG_OSEK_SYSTEM_EP)
				// ���ʹ������չ���ȼ�������������ȼ���������������ȼ��������������ȼ����������ȼ��������е���
				if( osekTask_RunningTask->taskControlBlock->curPriority != osekTask_RunningTask->taskControlBlock->configTable.basePriority )
				{
					osekTask_ChangeRunningTaskPriority( osekTask_RunningTask->taskControlBlock->configTable.basePriority );
					if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
					{
						osekTask_Dispatch();
					}
				}

#else
				// ���δʹ����չ���ȼ�������������ȼ���������IDת�������ȼ��������������ȼ���IDת�������ȼ��������е���
				if( osekTask_RunningTask->taskControlBlock->curPriority != OSEK_TASK_ID2PRI(osekTask_RunningTask->taskControlBlock->configTable.taskId) )
				{
					osekTask_ChangeRunningTaskPriority(OSEK_TASK_ID2PRI(osekTask_RunningTask->taskControlBlock->configTable.taskId));

					if( (osekTask_RunningTask->taskControlBlock->configTable.property & OSEK_TASK_NONPREEMPT ) == 0 )
					{
	       				osekTask_Dispatch();
					}
				}
#endif

#if defined(CONFIG_OSEK_RESOURCE_INTERNAL)
			}
#endif

	    }

	    OSEK_TARGET_EnableOSInt(osIntSave);
		return E_OK;

	}

	return E_OK;

}


/*
 * @brief
 *    osekResource_Initialize����Դ��ʼ�����ڲ���������
 * @param
 * @param[in]	�ޡ�
 * @param[out]  �ޡ�
 * @returns:    �ޡ�
 */

void osekResource_Initialize( void )
{

#if CONFIG_OSEK_RESOURCE_NUMBER > 0

	int i;

	// ��Դ���ƿ�����
	//memset((void*)osekResource_ResourceTable,0,sizeof(osekResource_ResourceTable));

	for( i = 0; i < CONFIG_OSEK_RESOURCE_NUMBER ; i++)
	{
		// ����ÿ����Դ���컨�����ȼ�
		osekResource_ResourceTable[i].ceilingPriority = osekConfig_ResourcePriorityTable[i];
		osekResource_ResourceTable[i].currentPriority = osekConfig_ResourcePriorityTable[i];

#if defined(CONFIG_OSEK_SYSTEM_EXTSTATUS)
		// ������Դ��ID
		osekResource_ResourceTable[i].resourceId = &osekResource_ResourceTable[i];
#endif

	}

#if defined(CONFIG_OSEK_RESOURCE_ISR)
	// ��ʼ���ж���Դ��
	osekResource_ISRLast = 0;
#endif

#endif /* #if CONFIG_OSEK_RESOURCE_NUMBER > 0 */

}


#endif /* #if defined(CONFIG_OSEK_RESOURCE) */

