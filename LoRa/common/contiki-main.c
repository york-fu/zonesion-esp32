#include <stdio.h>
#include <contiki.h>
#include <contiki-net.h>
#include <dev/leds.h>
#include "usart.h"
unsigned int idle_count = 0;

#define DEBUG 1

#if DEBUG
#define Debug      printf
#else
#define Debug(...)
#endif

void debug_init(void (*f)(char));

void main(void)
{
  clock_init();
  
  leds_init();
  leds_on(3);
 
  uart3_init(115200);
  debug_init(uart3_putc);

  
  Debug("\r\nStarting ");
  Debug(CONTIKI_VERSION_STRING);
  Debug(" on STM32F103x\r\n"); 
  
  process_init();
  process_start(&etimer_process, NULL);
  
  ctimer_init();
  leds_off(3);
#if AUTOSTART_ENABLE    
  autostart_start(autostart_processes);
#endif
  
  while(1) {
    do {
    } while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */ 
  }
}