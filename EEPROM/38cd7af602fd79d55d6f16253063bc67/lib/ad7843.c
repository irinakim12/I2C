
#include "hw_config.h"
#include "ad7843.h"

#ifndef USE_AVR_STUDIO
#pragma interrupt_handler INT7_vect:iv_EXT_INT7
#endif

void bsp_touch_gpio_init(void)
{

	// set port for input
	cbi(TOUCH_INT_DDR, TOUCH_INT_PIN_NO);

}

void bsp_key_interrupt_init(void)
{


	// INT4가 인터럽트가 발생 하도록 설정
	sbi(EIMSK, INT7);

	// INT4에 falling edge가 되는 순간 인터럽트 발생
	EICRB = (1<<ISC71) | (0<<ISC70);


}

#ifdef USE_AVR_STUDIO
ISR(INT7_vect)
#else
void INT7_vect(void)
#endif
{

	int a;

	a = 1;

}
