
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config(void);
void GPIO_Config(void);
void DAC1_Config(void);
void delay(uint32_t);

int i;
uint16_t dac_value;

int main(void)
{
	CLK_Config();
	GPIO_Config();
	DAC1_Config();
  while (1)
  {
	  for(i = 0; i < 4096; i++)
	  {
		  DAC->DHR12R1 = i;							// DAC set channel1 data
		  dac_value = DAC->DOR1;					// we can see variable in the dac1 using this
		  delay(16800);
	  }
  }
}


void CLK_Config() // Clock speed for 168MHz
{
	RCC->CR |= 0x00010000;                 // HSEON ENABLE
	while(!(RCC->CR & 0x00020000));        // HSEON Ready Flag wait
	RCC->CR |= 0x00080000;              // CSS ENABLE
	RCC->CR |= 0x01000000;				// PLL ON
	RCC->PLLCFGR |= 0x00400000;        // PLL SRC HSE is selected
	RCC->PLLCFGR |= 0x00000004;       // PLL M 4
	RCC->PLLCFGR |= 0x00005A00;        // PLL N 168
	RCC->PLLCFGR |= 0x00000000;       // PLL P 2
	RCC->CFGR |= 0x00000000;          // AHB PRESCALER 1
	RCC->CFGR |= 0x00080000;          // APB2 PRESCALER 2
	RCC->CFGR |= 0x00001400;          // APB1 PRESCALER 4
	RCC->CIR |= 0x00080000;             // HSE READY FLAG CLEAR
	RCC->CIR |= 0x00800000;             // CSS FLAG CLEAR
}


void GPIO_Config(void)
{
	RCC->AHB1ENR |= 0x1U << 0U; 		// A port clock enable

	GPIOA->MODER |= 3U << 0U; 			// pin A0 is selected analog mode
	GPIOA->OSPEEDR |= 3U << 0U; 		// very high speed is selected
	GPIOA->PUPDR |= 0U << 0U; 			// no pull up, pull down
}


void DAC1_Config(void)
{
	RCC->APB1ENR |= 0x1U << 29U;		// DAC clock bus enable

	DAC->CR |= 0x1U << 0U;				// DAC channel1 enable
	DAC->CR |= 0x0U << 1U;				// DAC channel1 output buffer enabled
	DAC->CR |= 0x0U << 2U;				// DAC channel1 trigger disabled
	DAC->CR |= 0x0U << 6U;				// wave generation disabled
	DAC->SWTRIGR |= 0x0U << 0U;			// Software trigger disabled
	DAC->DHR12R1 = 0x00000000;			// clear buffer
}


void delay(uint32_t time)
{
	while(time--);
}



/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
