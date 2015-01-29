
#ifndef __KEY_H
#define __KEY_H

typedef enum
{
	key1User = 0x00,
	key2User = 0x01,
	key3User = 0x02,
	keyBottomMax
} bsp_key_define_type;

// btn1
#define USER_KEY1_DDR			DDRC
#define USER_KEY1_PORT			PORTC
#define USER_KEY1_PIN			PINC
#define USER_KEY1_PIN_NO		PC7

// btn2
#define USER_KEY2_DDR			DDRE
#define USER_KEY2_PORT			PORTE
#define USER_KEY2_PIN			PINE
#define USER_KEY2_PIN_NO		PE4

// btn3
#define USER_KEY3_DDR			DDRC
#define USER_KEY3_PORT			PORTC
#define USER_KEY3_PIN			PINC
#define USER_KEY3_PIN_NO		PC0

typedef enum
{
	extiKey2ServiceFunction = 0x00,
	extiKeyServiceFunctionMAX
} exti_key_register_function_type;

typedef            void     (*exti_key_register_function)(void);

typedef struct _exti_key_service_function_type
{
	exti_key_register_function_type service_type;
	exti_key_register_function run;
} exti_key_service_function_type;

#define KEY_NONE	0x00
#define KEY_KEY1	0x01
#define KEY_KEY2	0x02
#define KEY_KEY3	0x04

void register_exti_key_function(exti_key_register_function_type exti_key_fn_type, exti_key_register_function fn);
void bsp_key_gpio_init(void);
void bsp_key_interrupt_init(void);

#endif
