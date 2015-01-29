
#include "hw_config.h"
#include "adc.h"

void bsp_adc_gpio_init(bsp_adc_channel_define_type channel) 
{
	if( channel == adChannel0 )
	{
		cbi(ADC_CH0_DDR, ADC_CH0_PIN_NO);
		cbi(ADC_CH0_PORT, ADC_CH0_PIN_NO);
	}
	else if( channel == adChannel1 )
	{
		cbi(ADC_CH1_DDR, ADC_CH1_PIN_NO);
		cbi(ADC_CH1_PORT, ADC_CH1_PIN_NO);
	}	
}

u16 adc_get_value(bsp_adc_channel_define_type channel) 
{ 
	u16 ret; 
	byte adc_l, adc_h; 
	
	ADCSRA=0x00;    

	// AVCC with external capacitor
	ADMUX=0x40 |channel;    // channel select
	
	// ADC Enable | Conversion Start | Free running Mode | 128 Division
	ADCSRA = (1<<ADEN) |(1<<ADSC) | (1<<ADFR) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	_delay_ms(5);         	// delay
	
	adc_l  = ADCL;   		// get low value
	adc_h = ADCH;   		// get high valueλֵ
	
	ret = (adc_h<<8) | adc_l;  // ADC voltage value
	
	return(ret); // return value of the voltage measured
	
} 
