//NUCLEO F103RBT6
//onboard LED on PA5

#include "stm32f10x.h"

int main(void){

	/* Enable internal clock - HSI 8MHz */
	  RCC->CR |= ((uint32_t)RCC_CR_HSION);

	  /* Wait for HSI to be ready */
	while ((RCC->CR & RCC_CR_HSIRDY) == 0){
	  }

	  /* Set HSI as the System Clock */
	RCC->CFGR = RCC_CFGR_SW_HSI;

	  /* Wait for HSI to be used for the system clock */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI){
	  }

	RCC->APB2ENR = RCC_APB2ENR_IOPAEN; //turns clock on for PORT A


	GPIOA->CRL |= GPIO_CRL_MODE5_1; //push_pull, output, 2MHz max output speed
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0;


	SysTick_Config(16000000);
	//interrupt from SysTick, led blinks in 2s intervals

	while(1);

}

__attribute__((interrupt)) void SysTick_Handler(void){
	GPIOA->ODR ^= GPIO_ODR_ODR5;
}
