#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "led.h"
#include "led_desc.h"
#include "key.h"
#include "key_desc.h"



static struct led_desc led1_desc = 
{
	.Port = GPIOA,
	.Pin = GPIO_Pin_6,
	.OnBit = Bit_RESET,
	.OffBit = Bit_SET,
};
led_desc_t led1 = &led1_desc;

static struct led_desc led2_desc = 
{
	.Port = GPIOA,
	.Pin = GPIO_Pin_7,
	.OnBit = Bit_RESET,
	.OffBit = Bit_SET,
};
led_desc_t led2 = &led2_desc;

static struct key_desc key1_desc = 
{
	.Port = GPIOE,
	.Pin = GPIO_Pin_4,
	.State = true,
};
key_desc_t key1 = &key1_desc;

static struct key_desc key2_desc = 
{
	.Port = GPIOE,
	.Pin = GPIO_Pin_3,
	.State = true,
};
key_desc_t key2 = &key2_desc;

void board_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		
    led_init(led1);
    led_init(led2);
    key_init(key1);
    key_init(key2);
}


