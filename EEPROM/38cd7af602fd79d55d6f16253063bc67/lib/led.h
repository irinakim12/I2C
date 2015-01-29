
#ifndef __LED_H
#define __LED_H

typedef enum
{
	ledUserCore = 0x00,
	ledCoreMax
} bsp_led_core_type;

typedef enum
{
	ledUserBottom1 = 0x00,
#ifdef M128_MIDDLE_HW_VER1		
	ledUserBottom2,
#endif	
	ledBottomMax
} bsp_led_bottom_type;


// cpu modue led
#define USER_CORE_LED_DDR			DDRE
#define USER_CORE_LED_PORT			PORTE
#define USER_CORE_LED_PIN			PINE
#define USER_CORE_LED_PIN_NO		PE3

// bottom modue led1
#define USER_BOTTOM_LED1_DDR		DDRC
#define USER_BOTTOM_LED1_PORT		PORTC
#define USER_BOTTOM_LED1_PIN		PINC
#define USER_BOTTOM_LED1_PIN_NO		PC1

#ifdef M128_MIDDLE_HW_VER1
// bottom modue led2
#define USER_BOTTOM_LED2_DDR		DDRE
#define USER_BOTTOM_LED2_PORT		PORTE
#define USER_BOTTOM_LED2_PIN		PINE
#define USER_BOTTOM_LED2_PIN_NO		PE2
#endif

void bsp_led_gpio_init(void);
void bsp_led_core_on(bsp_led_core_type led);
void bsp_led_core_off(bsp_led_core_type led);
void bsp_led_core_toggle(bsp_led_core_type led);

void bsp_led_bottom_on(bsp_led_bottom_type led);
void bsp_led_bottom_off(bsp_led_bottom_type led);
void bsp_led_bottom_toggle(bsp_led_bottom_type led);

#endif
