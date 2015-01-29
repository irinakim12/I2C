
#include "hw_config.h"
#include "led.h"

#if 0
// define led port and pin for core module
bsp_port_group_type led_core_group[ledCoreMax]=
{
	{(u16*)&DDRE, (u16*)&PORTE, (u16*)&PINE, PE3 }
};

// define led port and pin for bottom board
bsp_port_group_type led_bottom_group[ledBottomMax]=
{
	{(u16*)&DDRC, (u16*)&PORTC, (u16*)&PINC, PC1 },
	{(u16*)&DDRE, (u16*)&PORTE, (u16*)&PINE, PE2 }
};
#endif

void bsp_led_gpio_init(void)
{
	// Output
	//sbi(*led_core_group[ledUserCore].ddr, led_core_group[ledUserCore].pin_no);

	//sbi(*led_core_group[ledUserBottom1].ddr, led_core_group[ledUserBottom1].pin_no);
	//sbi(*led_core_group[ledUserBottom2].ddr, led_core_group[ledUserBottom2].pin_no);

	sbi(USER_CORE_LED_DDR, USER_CORE_LED_PIN_NO);

	sbi(USER_BOTTOM_LED1_DDR, USER_BOTTOM_LED1_PIN_NO);
#ifdef M128_MIDDLE_HW_VER1		
	sbi(USER_BOTTOM_LED2_DDR, USER_BOTTOM_LED2_PIN_NO);	
#endif
}

void bsp_led_core_on(bsp_led_core_type led)
{
	if( led >= ledCoreMax )
		return;

	//sbi(*led_core_group[led].port, led_core_group[led].pin_no);
	sbi(USER_CORE_LED_PORT, USER_CORE_LED_PIN_NO);
}

void bsp_led_core_off(bsp_led_core_type led)
{
	if( led >= ledCoreMax )
		return;

	// cbi(*led_core_group[led].port, led_core_group[led].pin_no);
	cbi(USER_CORE_LED_PORT, USER_CORE_LED_PIN_NO);
}

void bsp_led_core_toggle(bsp_led_core_type led)
{
	u16 pins;

	if( led >= ledCoreMax )
		return;

	/*
	pins = (u16)(inp((u16)*led_core_group[ledUserCore].pin, led_core_group[ledUserCore].pin_no));
	if ((pins & led_core_group[led].pin_no) == 0)
	{
		sbi(*led_core_group[led].port, led_core_group[led].pin_no);
	}
	else
	{
		cbi(*led_core_group[led].port, led_core_group[led].pin_no);
	}	
	*/

	pins = inp(USER_CORE_LED_PIN, USER_CORE_LED_PIN_NO);
	if ((pins & 1<<USER_CORE_LED_PIN_NO) == 0)
	{
		sbi(USER_CORE_LED_PORT, USER_CORE_LED_PIN_NO);
	}
	else
	{
		cbi(USER_CORE_LED_PORT, USER_CORE_LED_PIN_NO);
	}
}

void bsp_led_bottom_on(bsp_led_bottom_type led)
{
	if( led >= ledBottomMax )
		return;

	//cbi(*led_bottom_group[led].port, led_bottom_group[led].pin_no);

	if( led == ledUserBottom1 )
		sbi(USER_BOTTOM_LED1_PORT, USER_BOTTOM_LED1_PIN_NO);
#ifdef M128_MIDDLE_HW_VER1	
	else if( led == ledUserBottom2 )
		sbi(USER_BOTTOM_LED2_PORT, USER_BOTTOM_LED2_PIN_NO);
#endif	
}

void bsp_led_bottom_off(bsp_led_bottom_type led)
{
	if( led >= ledBottomMax )
		return;

	//sbi(*led_bottom_group[led].port, led_bottom_group[led].pin_no);

	if( led == ledUserBottom1 )
		cbi(USER_BOTTOM_LED1_PORT, USER_BOTTOM_LED1_PIN_NO);
#ifdef M128_MIDDLE_HW_VER1	
	else if( led == ledUserBottom2 )
		cbi(USER_BOTTOM_LED2_PORT, USER_BOTTOM_LED2_PIN_NO);
#endif	
}

void bsp_led_bottom_toggle(bsp_led_bottom_type led)
{
	u16 pins;

	if( led >= ledBottomMax )
		return;

	if( led == ledUserBottom1 )
	{
		pins = inp(USER_BOTTOM_LED1_PIN, USER_BOTTOM_LED1_PIN_NO);
		if ((pins & 1<<USER_BOTTOM_LED1_PIN_NO) == 0)
		{
			sbi(USER_BOTTOM_LED1_PORT, USER_BOTTOM_LED1_PIN_NO);
		}
		else
		{
			cbi(USER_BOTTOM_LED1_PORT, USER_BOTTOM_LED1_PIN_NO);
		}
	}
}
