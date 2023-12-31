/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "../stm_driver/inc/Stm32_F103C6_EXTI_driver.h"
#include "../stm_driver/inc/Stm32_F103C6_gpio_driver.h"


uint16_t IRQ_Flag = 0;
int x = 0 ;
void EXTI9_CallBack(void)
{
	IRQ_Flag = 1;
	__asm("nop\n \t nop");
	__asm("MRS %0,IPSR"
					: "=r"(x));
	__asm("nop\n \t nop");
}
int out ;
int in = 1 ;
int in2 = 2 ;
int CONTROL_Regist_value;
int main(void)
{

	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();


	EXTI_PinConfig_t EXTI_Cfg;
	EXTI_Cfg.EXTI_PIN = EXTI9PB9;
	EXTI_Cfg.TriggerCase = EXTI_Trigger_RISING;
	EXTI_Cfg.P_IRQ_CallBack = EXTI9_CallBack;
	EXTI_Cfg.IRQ_Enable = EXTI_IRQ_Enable;

	MCAL_EXTI_GPIO_Init(&EXTI_Cfg);

/*************lab1 non input or output************************/
	__asm("nop\n \t nop");
	__asm("nop\n \t nop");
/*************lab2 output only  ************************/

///////////////////////////////////////////////
//  ass code : destination out : source input//
///////////////////////////////////////////////

	__asm("mov %0, #0xff"    // move 0xff to a register choosen by th cpu
		:"=r" (out));        // compiler will generate a code store the result of 0xff into the adress of register that contain
							// variable  out
	__asm("nop\n \t nop");
/*************lab3 ************************/
	__asm("mov R0,%0 "    // move data in the register choosen by th cpu into the r0
		:
		: "r" (in));        // compiler will generate a code store the value  into the r0 of register into in variable

	__asm("nop\n \t nop");

/*************lab4 ************************/
	out = 0  ;
	in = 1 ;
	in2 = 2 ;
	__asm("nop\n \t nop");

	__asm("add %0,%1,%2"
		: "=r"(out)
		: "r"(in) , "r"(in2));

	__asm("nop\n \t nop");

/*****************lab5********************/
// Naming Conventional same as the last one
		__asm("add %[Out0], %[in0], %[in1]"
				:[Out0] "=r" (out)
				 :[in0] "r" (in),
				  [in1] "r" (in2));
/****************lab6*******************/
	__asm("MRS %[Cont],CONTROL"
				:[Cont] "=r"(CONTROL_Regist_value));



	IRQ_Flag = 1;

	while(1)
	{
		if(IRQ_Flag)
		{

			IRQ_Flag = 0;
		}


	}
}

