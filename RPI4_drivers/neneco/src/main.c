/**
 * @file main.c
 * @author Francisco Marques (fmarques_00@protonmail.com)
 * @brief The main file contains functions to test each device driver. For each driver exists a tasks and a init function.
 * @version 0.1
 * @date 2021-12-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**< C libraries includes*/
#include <stddef.h>
#include <stdint.h>
//#include <stdio.h>

/**< FreeRTOS port includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/**< Drivers includes*/
#include "uart.h"
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
#include "AD1115.h"
#include "LN298.h"
#include "ELM327.h"

/**< Hartstone bench include*/
#include "xprintf.h"
#include "hartstone.h"

/*
 * Prototypes for the standard FreeRTOS callback/hook functions implemented
 * within this file.
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );


static inline void io_halt(void)
{
    asm volatile ("wfi");
	return;
}
/*-----------------------------------------------------------*/

/**
 * @brief UART test task
 * 
 * @param pvParameters 
 * 
 * This task will print every 1000ms (1s) the string: "UART2 Working!\r\n"
 */
void TaskUART(void *pvParameters){
	(void) pvParameters;

    for( ;; )
    {
		uart_puts("TEST RTOS \n");
		/**< Wait 1500 ms*/
		vTaskDelay(1500);
    }

	return; /* Never reach this line */
}

/**
 * @brief Interval function to test the FreeRTOS timer.
 * 
 * @param pxTimer 
 * 
 * Every 50ms this function is executed. Read the uart and turn on
 * the LED on pin 42 (Green LED on RPI4 model b) if receives '1'.
 * Turn off the LED if receives '0'
 */
void interval_func(TimerHandle_t pxTimer)
{
	(void) pxTimer;
	
	gpio_pin_set(GPIO_42, GPIO_PIN_SET);
		
	return;
}
/*-----------------------------------------------------------*/


TaskHandle_t task_uart_test;
void uart_test(){
	uart_puts("\r\n Neneco - UART unit test\r\n");
	uart_putdec(13);
	uart_puthex(0x30);

	xTaskCreate(TaskUART, "Task UART Test", 512, NULL, 0x10, &task_uart_test);
}

TimerHandle_t timer;
void interval_test(void){

	timer = xTimerCreate("print_every_50ms",(50 / portTICK_RATE_MS), pdTRUE, (void *)0, interval_func);
	if(timer != NULL)
	{
		xTimerStart(timer, 0);
	}
}

void main(void)
{
	uart_init();
	// init xprintf output func
	xdev_out(uart_putchar);
	xputs("\r\n Neneco - FreeRTOS standalone\r\n");
	
	hartstone_start();
}
/*-----------------------------------------------------------*/



void vApplicationIdleHook( void )
{
}

/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
}
