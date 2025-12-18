#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "board.h"



static void led1_task(void *pvParameters)
{
	while(1)
	{
		led_on(led1);
		vTaskDelay(pdMS_TO_TICKS(500));
		led_off(led1);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void led2_task(void *pvParameters)
{
	while(1)
	{
		led_on(led2);
		vTaskDelay(pdMS_TO_TICKS(1000));
		led_off(led2);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void key_task(void *pvParameters)
{
    key_desc_t key = (key_desc_t)pvParameters;
	static uint8_t f1=0;
	static uint8_t f2=0;
	TaskHandle_t led1_task_handle = NULL;
	TaskHandle_t led2_task_handle = NULL;
    while (1)
    {
        if(key_read(key)==0)
		{
			vTaskDelay(pdMS_TO_TICKS(10));
			if(key_read(key)==0)
			{
				if(key==key1&&f1==0)
				{
					f1=1;
					xTaskCreate(led1_task, "led1", 100, led1, 5, &led1_task_handle);
					while(key_read(key1)==0);
					vTaskDelay(pdMS_TO_TICKS(10));
				}
				if(key==key2&&f2==0)
				{
					f2=1;
					if(led2_task_handle == NULL)
					{
						xTaskCreate(led2_task, "led2", 100, led2, 5, &led2_task_handle);
					}
					else
						vTaskResume(led2_task_handle); 
					while(key_read(key2)==0);
					vTaskDelay(pdMS_TO_TICKS(10));
				}
				if(key==key1&&f1==1)
				{
					f1=0;
					if(led1_task_handle != NULL)
					{
						vTaskDelete(led1_task_handle);
					}
					while(key_read(key1)==0);
					vTaskDelay(pdMS_TO_TICKS(10));
					led_off(led1);
				}
				if(key==key2&&f2==1)
				{
					f2=0;
					if(led2_task_handle != NULL)
					{
						vTaskSuspend(led2_task_handle);
					}
					while(key_read(key2)==0);
					vTaskDelay(pdMS_TO_TICKS(10));
					led_off(led2);
				}
			}
		}
    }
}



int main(void)
{
	
	board_init();
	
	xTaskCreate(key_task, "key1", 100, key1, 5, NULL);
	xTaskCreate(key_task, "key2", 100, key2, 5, NULL);

	vTaskStartScheduler();

	while (1)
	{
		
	}
}


void vAssertCalled(const char *file, int line)
{
	portDISABLE_INTERRUPTS();
    //printf("Assert Called: %s(%d)\n", file, line);

}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName)
{
   // printf("Stack Overflowed: %s\n", pcTaskName);
    configASSERT(0);
}

void vApplicationMallocFailedHook( void )
{
   // printf("Malloc Failed\n");
    configASSERT(0);
}


