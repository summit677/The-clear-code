#include "osapi.h"
#include "includes.h"
//#include "cfg.h"

void OSEK_CPU_INIT()
{

//  STR_UART_T sParam;
	
  DrvTIMER_Init();
  DrvTIMER_Open(E_TMR0, 100, E_PERIODIC_MODE);
  DrvTIMER_EnableInt(E_TMR0);
  
  Initial_pannel();
	clr_all_pannal();
	
	
  /* Configure UART0 related pins */
//  DrvGPIO_InitFunction(E_FUNC_UART0);
	
  /* UART Setting */
/*  sParam.u32BaudRate      = 115200;
  sParam.u8cDataBits      = DRVUART_DATABITS_8;
  sParam.u8cStopBits      = DRVUART_STOPBITS_1;
  sParam.u8cParity        = DRVUART_PARITY_NONE;
  sParam.u8cRxTriggerLevel= DRVUART_FIFO_1BYTES;
*/
  /* Select UART Clock Source From 12Mhz*/
//  DrvSYS_SelectIPClockSource(E_SYS_UART_CLKSRC,0); 

//  DrvUART_Open(UART_PORT0, &sParam);

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
