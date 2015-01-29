
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


	// INT4�� ���ͷ�Ʈ�� �߻� �ϵ��� ����
	sbi(EIMSK, INT7);

	// INT4�� falling edge�� �Ǵ� ���� ���ͷ�Ʈ �߻�
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
