#include <stm32f4xx.h>
#include <stdint.h>
#include <lcd.h>


void adc_init(void)
{
	RCC->AHB1ENR|=(1<<2); //Enable GPIO Clock in AHB1ENR for PortC
	GPIOC->MODER|=(1<<4); //Set PC2 to Analog Mode
	GPIOC->MODER|=(1<<5);
	RCC->APB2ENR|=(1<<8);//Enable clock access to ADC in APB2ENR
	ADC1->SQR3|=(0x0c<<0); //ADC channel & sequence selection PC2 at channel 12
	//ADC1->CR1 =(1<<8); //Enable Scan Mode
	ADC1->CR2|=(1<<1);  //Enable Continuous Conversion Mode
	ADC1->CR2|=(1<<0);  //Enable ADC module
}


uint16_t adc_read(void)
{
    ADC1->CR2|=(1<<30); //Start Conversion
	while(!(ADC1->SR&(1<<1))){}  //Wait till conversion is over
	return(ADC1->DR);
}


