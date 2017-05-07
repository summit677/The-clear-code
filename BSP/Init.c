#include "osapi.h"
#include "includes.h"
//#include "cfg.h"

void OSEK_CPU_INIT()
{
//  STR_UART_T sParam;
	//系统定时器初始化
  DrvTIMER_Init();
  DrvTIMER_Open(E_TMR0, 1000, E_PERIODIC_MODE);//E_PERIODIC_MODE == 周期模式
  DrvTIMER_EnableInt(E_TMR0);
  
	//LCD初始化
  Initial_pannel();
	clr_all_pannal();
}


void OSEK_TIMER_START()
{

DrvTIMER_Start(E_TMR0);

}

  void Delay(int count)
{
	while(count--)
	{

	 }
}
