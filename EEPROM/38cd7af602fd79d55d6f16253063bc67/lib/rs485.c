

#include "hw_config.h"
#include "uart.h"
#include "rs485.h"


#if 0
/*
	2400, 2800, 9600, 14.4K, 28.8K, 38.4K, 57.6K, 76.8K, 115.2K, 230.4K, 250K, 500K, 1M, 2M
	832, 416, 207, 138, 103, 68, 51, 34, 25, 16, 8, 7, 3, 1, 0
*/
void bsp_usart1_rs485_9600bps_init()
{
	// 9600bps, 8 Data Bit, 1 Stop Bit, Parity None
	UBRR1H = (207) >> 8;
	UBRR1L = (207);	

	UCSR1A = 0X02;
	UCSR1B = 0X18;	
	UCSR1C = 0X06;		
	// UCSR1C=0xB6;

	//sbi(UCSR1C,UPM1); // UART UPM Bits Setting Disabled	
	//sbi(UCSR1C,UPM0); // UART UPM Bits Setting Disabled		

	// cbi(UCSR1C,USBS); //	USBS Bit Settings 1-bit		
}
#endif

void bsp_rs485_gpio_init()
{
	// RXD를 입력으로
	cbi(USART1_RX_DDR, USART1_RX_PIN_NO);

	// TXD를 출력으로
	sbi(USART1_TX_DDR, USART1_TX_PIN_NO);

	sbi(RS485_MODE_DDR, RS485_MODE_PIN_NO);	// output mode
	
	rs485_set_rx(); 	// make the MAX485 in the receiving state	
}

void rs485_set_rx()
{
	cbi(RS485_MODE_PORT, RS485_MODE_PIN_NO); 	// make the MAX485 in the receiving state	
}

void rs485_set_tx()
{
	sbi(RS485_MODE_PORT, RS485_MODE_PIN_NO); 	// make the MAX485 in the sending state	
}

// 9600 baud / 8 data bits / 1 stop bit / odd parity / send on / receive interrupt / Asynchronous Operation
void bsp_rs485_init(void) 
{ 
	
	UCSR1A=0x00;	// MPCM Disable	
	// UCSR1A=0x01;	// MPCM Enable
	
	// UCSR1B=0x9C; 
	UCSR1B = (1 << TXEN1 ) | (1 << RXEN1 ) | (1 << UCSZ12 );
	
	UCSR1C=0xB6; 

	// Clock Polarity
	cbi(UCSR1C, UCPOL1);
	
	// Data 8Bit
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

	// 1 Stop bit
	cbi(UCSR1C, USBS1); //	USBS Bit Settings 1-bit		

	// 1      1      Enabled, Odd Parity
	sbi(UCSR1C,UPM11); // UART UPM Bits Setting Disabled	
	sbi(UCSR1C,UPM10); // UART UPM Bits Setting Disabled	

	// Asynchronous Operation
	cbi(UCSR1C,UMSEL1); //	USBS Bit Settings 1-bit	
	
	UBRR1L= (F_CPU/BAUDRATE_485/16-1)%256;
	UBRR1H= (F_CPU/BAUDRATE_485/16-1)/256; 
	
} 

void bsp_rs485_interrupt_enable() 
{
	sbi(UCSR1B, RXCIE1);
}


void delay_nus(u16 n)
{
	u16 i=0;
	for (i=0;i<n;i++)
		asm("nop");
}

void rs485_puts(char *data) 
{ 

	int len, count;

	//rs485_set_rx();
	//delay_nus(10);	
	rs485_set_tx();
	delay_nus(10);

	len = strlen(data);
	for (count = 0; count < len; count++) 
	{
		if(count == 0)
			// UCSR1B |= 0x01;   // TXB8 Transmit Data Bit 8
			sbi(UCSR1B, TXB81);	// Set TXB8 Transmit Data Bit 8
		else 
			//UCSR1B &= 0xfe;   // TXB8 Transmit Data Bit 8
			cbi(UCSR1B, TXB81);	// Clear TXB8 Transmit Data Bit 8

		UDR1 = *(data+count);

		while((UCSR1A&(1<<TXC1))==0); // wait for the end of the transmission
		
		// UCSR1A |= 0x40; // Clear To Send end marker		
		sbi(UCSR1A, TXC1);

		delay_nus(200);// must be sent each time interval, this is the minimum, the actual situation may be even greater
	}

	rs485_set_rx();	
	
} 



