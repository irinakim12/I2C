
#include "hw_config.h"
#include "uart.h"
#include "at24c02.h"




void main(void)
{
	CLI();

	bsp_usart0_gpio_init();

	init_usart0_buffer();
	if( F_CPU == 8000000UL ) 	
	{
		bsp_usart0_init(F_CPU, EBaud38400, EData8, EParNone, EStop1, FALSE );
	}
	else
	{
		bsp_usart0_init(F_CPU, EBaud115200, EData8, EParNone, EStop1, FALSE );	
	}
	
	//register_uart0_function(uart0_rx_event);
	bsp_usart0_interrupt_enable();

	SEI();	// all interrupt enable

	bsp_at24c02_gpio_init();
	bsp_at24c02_init();

	_delay_ms (500);

	usart0_puts("\r\nWait. Writing data.\r\n");	

	IIC_wrbyte (0x01, 0x12); // byte write
	_delay_ms (500);
	IIC_wrbyte (0x02, 0x13); // byte write
	_delay_ms (500);
	IIC_wrbyte (0x03, 0x14); // byte write
	_delay_ms (500);
	usart0_format_puts("\r\nwritten data 0x%x, 0x%x, 0x%x.\r\n", 0x01, 0x02, 0x03);	

	_delay_ms (500);
	_delay_ms (500);
	_delay_ms (500);
	_delay_ms (500);

	usart0_format_puts("0x%x, 0x%x, 0x%x readed.\r\n", IIC_rebyte (0x12), IIC_rebyte (0x13), IIC_rebyte (0x14));


	while(1)
	{
		
	}

}
