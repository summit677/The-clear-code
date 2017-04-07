
#include "osapi.h"
#include "cfg.h"
#include "includes.h"
#include "system_NUC1xx.h"

void ErrorHook( StatusType error )
{
	/*
	TaskType taskId;
	TaskStateType state;
	GetTaskID(&taskId);

	printf("\n|*********************In Error Hook *********************|\n");
	showTaskInfo(taskId);
	printf("|*********************Error Hook end*********************|\n\n");
	*/
}

void PostTaskHook( void )
{
	/*
	TaskType taskId;
	TaskStateType state;
	OSDWORD t;
	GetTaskID(&taskId);

	printf("\n|*******************In PostTask Hook ********************|\n");
	showTaskInfo(taskId);
	printf("|*******************PostTask Hook end********************|\n\n");
	*/
}

void StartupHook( void )
{
	/*
	OSBYTE t;
	t=GetActiveApplicationMode();
	showLogo();
	printf("\n|*******************In Startup Hook *********************|\n");
	printf("the active application mode is %d\n",(int)t);
	printf("|*******************Startup Hook end*********************|\n\n");
	*/
}
void ShutdownHook( StatusType error )
{

}
TASK(Task1)
{

}

TASK(Task2)
{

}
TASK(Task3)
{

}
TASK(Task4)
{

}
TASK(TaskError)
{

}


void read_timer_value(unsigned int *value)
{
	*value = DrvTIMER_GetCounters(E_TMR0);
}
int main()
{
	//BSP_UartInit(); 
	OSEK_CPU_INIT();
	//BSP_TimerInit();
	OSEK_TIMER_START();
	__enable_irq();
	//showLogo();
	StartOS(OSDEFAULTAPPMODE);
	
	
	return 0;
}