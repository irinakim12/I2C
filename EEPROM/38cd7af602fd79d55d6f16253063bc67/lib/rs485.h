

#ifndef __RS485_H
#define __RS485_H

#define BAUDRATE_485 9600

// rs485
#define RS485_MODE_DDR			DDRF
#define RS485_MODE_PORT		PORTF
#define RS485_MODE_PIN_NO		PF3

//void bsp_usart1_rs485_9600bps_init();
void bsp_rs485_gpio_init();
void rs485_set_rx();
void rs485_set_tx();
void bsp_rs485_init(void);
void bsp_rs485_interrupt_enable();
void rs485_puts(char *data);

//void usart_init(void);
//void usart_out(unsigned char *datas,unsigned char n);



#endif

