
/* MOTORU 0 DERECE ÝLE 180 DERECE ARASI SUREKLI DONDEREN ORNEK */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t delay_count;

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct; // PWM icin

void SysTick_Handler(void)
{
	delay_count--;
}

void delay_ms(uint32_t time)
{
	delay_count = time;
	while(time); //time 0 dan buyuk oldugu surece burada bekle
}



void GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	//MODE AF olarak kullandigimiz icin AF ayarlarini yapmamiz gerekmektedir

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // timer olarak kullanildigi icin AF olarak kullandik.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void TIM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 19999;
	TIM_InitStruct.TIM_Prescaler = 83;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4,&TIM_InitStruct);
	TIM_Cmd(TIM4,ENABLE);

	/*MOTOR OZELLIKLERI : 20ms(50Hz) PWM Periyod  1 - 2 ms duty cycle
	 *
	 *periyod = 20ms = 20000us demektir
	 *
	 * tick_freq = periyod*pwm_freq -> 20000*50 = 1MHz
	 *
	 * precaler = (timer_clk / tick_timer_freq)-1  -> (84MHz/1MHZ)-1 = 83
	 */


	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1; //PWM mod1 mod2 muhabbeti , doluluk oranlarýyla ilgili
	TIMOC_InitStruct.TIM_OutputState = ENABLE;//cikisi aktif ettik
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

	SysTick_Config(SystemCoreClock/1000); //1ms de bir kesmeye gider ve SysTick_Handler fonksiyonuna girer her 1ms de
}


int main(void)
{
	GPIO_Config();
	TIM_Config();
  while (1)
  {
	  for(int i =500; i<=2000; i++)
	  {
		  TIMOC_InitStruct.TIM_Pulse = i;
		  TIM_OC2Init(TIM4,&TIMOC_InitStruct);
		  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
		  delay_ms(2); //2ms
	  }
	  for(int i =2000; i>=500; i++)
	  {
		  TIMOC_InitStruct.TIM_Pulse = i;
		  TIM_OC2Init(TIM4,&TIMOC_InitStruct);
		  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
		  delay_ms(2); //2ms
	  }
  }
}

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
