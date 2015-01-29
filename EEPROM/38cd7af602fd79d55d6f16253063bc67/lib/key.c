
#include "hw_config.h"
#include "key.h"

#ifndef USE_AVR_STUDIO
#pragma interrupt_handler INT4_vect:iv_EXT_INT4
#endif


#if 0
const bsp_port_group_type key_bottom_group[keyBottomMax]=
{
	{(u16*)&DDRC, (u16*)&PORTC, (u16*)&PINC, PC7 },
	{(u16*)&DDRE, (u16*)&PORTE, (u16*)&PINE, PE4 },
	{(u16*)&DDRC, (u16*)&PORTC, (u16*)&PINE, PC0 }
};
#endif

exti_key_service_function_type gbl_ar_exti_key_service[extiKeyServiceFunctionMAX] = 
{
	{extiKey2ServiceFunction, NULL}
};

void register_exti_key_function(exti_key_register_function_type exti_key_fn_type, exti_key_register_function fn)
{
	gbl_ar_exti_key_service[exti_key_fn_type].run = fn;
}

void bsp_key_gpio_init(void)
{
	//sbi(*key_bottom_group[key1User].ddr, key_bottom_group[key1User].pin_no);
	//sbi(*key_bottom_group[key2User].ddr, key_bottom_group[key2User].pin_no);
	//sbi(*key_bottom_group[key3User].ddr, key_bottom_group[key3User].pin_no);

	// set port for input
	cbi(USER_KEY1_DDR, USER_KEY1_PIN_NO);
	cbi(USER_KEY2_DDR, USER_KEY2_PIN_NO);
	cbi(USER_KEY3_DDR, USER_KEY3_PIN_NO);

}

void bsp_key_interrupt_init(void)
{
	//uint8_t sreg;

	// sreg = SREG;
	//sbi_ns(MCUCR, ((1<<ISC11) | (1<<ISC01)));
	//cbi_ns(MCUCR, ((1<<ISC10) | (1<<ISC00)));

	// INT4가 인터럽트가 발생 하도록 설정
	sbi(EIMSK, INT4);

	// INT4에 falling edge가 되는 순간 인터럽트 발생
	EICRB = (1<<ISC41) | (0<<ISC40);


	/* restore status-register */
	// SREG = sreg;
}

#ifdef USE_AVR_STUDIO
ISR(INT4_vect)
#else
void INT4_vect(void)
#endif
{
	if( gbl_ar_exti_key_service[extiKey2ServiceFunction].run != NULL )
	{
		gbl_ar_exti_key_service[extiKey2ServiceFunction].run();
	}		

}


