
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
uint8 flag = 0;
TASK(Task1)
{
	int i;
	if(flag == 0)
		flag = 1;
	else 
		WaitEvent(0x10);
	close_seven_segment();
	while(1)
	{
		show_seven_segment(0,1);
		SetEvent(Task2, 0x30);
		for(i = 0; i < 1000000;i++);
		TerminateTask();
		//osekTask_Dispatch();
	}
	
}

TASK(Task2)
{
	int i;
	WaitEvent(0x30);
	close_seven_segment();
	while(1)
	{
		show_seven_segment(1,2);
		SetEvent(Task3, 0x40);
		for(i = 0; i < 1000000;i++);
		TerminateTask();
		//osekTask_Dispatch();
	}
	
}
TASK(Task3)
{
	int i;
	WaitEvent(0x40);
	close_seven_segment();
	while(1)
	{
		show_seven_segment(2,3);
		SetEvent(Task4, 0x50);
		for(i = 0; i < 1000000;i++);
		//TerminateTask();
		//osekTask_Dispatch();
		
	}
	
}
TASK(Task4)
{
	int i;
	WaitEvent(0x50);
	close_seven_segment();
	while(1)
	{
		show_seven_segment(3,4);
		for(i = 0; i < 1000000;i++);
		SetEvent(Task1, 0x10);
		TerminateTask();
		//osekTask_Dispatch();
	}
	
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
	unsigned char err=err;
	
	UNLOCKREG();
	SYSCLK->PWRCON.XTL12M_EN = 1; 	//Enable 12Mhz and set HCLK->12Mhz
	SYSCLK->CLKSEL0.HCLK_S = 0;
	LOCKREG();		
	
	//BSP_UartInit(); 
	OSEK_CPU_INIT();
	//BSP_TimerInit();
	//OSEK_TIMER_START();
	__enable_irq();
	//showLogo();
	
	StartOS(OSDEFAULTAPPMODE);
	
	
	return 0;
}