

#ifndef _BUZZER_H_
#define _BUZZER_H_

#define BUZZER_DDR			DDRF
#define BUZZER_PORT			PORTF
#define BUZZER_PIN_NO		PF2

void bsp_buzzer_gpio_init();
void buzzer_on();
void buzzer_off();

#endif