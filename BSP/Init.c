#include "osapi.h"
#include "includes.h"
//#include "cfg.h"

void OSEK_CPU_INIT()
{
//  STR_UART_T sParam;
	//ϵͳ��ʱ����ʼ��
  DrvTIMER_Init();
  DrvTIMER_Open(E_TMR0, 1000, E_PERIODIC_MODE);//E_PERIODIC_MODE == ����ģʽ
  DrvTIMER_EnableInt(E_TMR0);
  
	//LCD��ʼ��
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
