
#include "hw_config.h"
#include "buzzer.h"


void bsp_buzzer_gpio_init() 
{
	sbi(BUZZER_DDR, BUZZER_PIN_NO);
}

void buzzer_on() 
{
	cbi(BUZZER_PORT, BUZZER_PIN_NO);
}

void buzzer_off() 
{
	sbi(BUZZER_PORT, BUZZER_PIN_NO);
}

