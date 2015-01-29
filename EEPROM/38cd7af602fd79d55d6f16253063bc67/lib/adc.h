
#ifndef __ADC_H
#define __ADC_H

typedef enum
{
	adChannel0 = 0x00,
	adChannel1 = 0x01,
	adChannelMax
} bsp_adc_channel_define_type;

// adc0
#define ADC_CH0_DDR			DDRF
#define ADC_CH0_PORT		PORTF
#define ADC_CH0_PIN_NO		PF0

// adc1
#define ADC_CH1_DDR			DDRF
#define ADC_CH1_PORT		PORTF
#define ADC_CH1_PIN_NO		PF1

void bsp_adc_gpio_init(bsp_adc_channel_define_type channel);
u16 adc_get_value(bsp_adc_channel_define_type channel);

#endif