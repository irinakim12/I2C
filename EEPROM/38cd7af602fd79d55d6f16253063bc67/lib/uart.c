
#ifdef USE_AVR_STUDIO
#include<avr/io.h>
#include<avr/interrupt.h>
#include <string.h>
#endif

#include "hw_config.h"
#include "uart.h"
#include "queue.h"

//#define USART_BAUDRATE 9600
//#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#ifndef USE_AVR_STUDIO
#pragma interrupt_handler USART0_RX_vect:iv_USART0_RX
#pragma interrupt_handler USART1_RX_vect:iv_USART1_RX
#endif

static char usart_format_buff[80];

uart_register_function uart0_register_fn = NULL;
uart_register_function uart1_register_fn = NULL;

// setting USART
#define USART_TX_BUFF_CNT	2
#define USART_RX_BUFF_CNT	2

#define USART_TX_DMA_SIZ    2
#define USART_RX_DMA_SIZ    2

q_list_type gbl_qlist_usart0_tx;
q_list_type gbl_qlist_usart0_tx_free;

q_node_type gbl_qdata_usart0_tx[USART_TX_BUFF_CNT];
q_node_type gbl_qdata_usart0_tx_free[USART_TX_BUFF_CNT];

char gbl_usart0_tx_buff[USART_TX_BUFF_CNT][USART_TX_DMA_SIZ];
char gbl_usart0_tx_buff_dma[USART_TX_DMA_SIZ];

q_list_type gbl_qlist_usart0_rx;
q_list_type gbl_qlist_usart0_rx_free;

q_node_type gbl_qdata_usart0_rx[USART_RX_BUFF_CNT];
q_node_type gbl_qdata_usart0_rx_free[USART_RX_BUFF_CNT];

char gbl_usart0_rx_buff[USART_RX_BUFF_CNT][USART_RX_DMA_SIZ];
// char gbl_usart0_rx_buff_dma[USART_RX_DMA_SIZ];

static u16 s_usart0_tx_q_free_cnt = 0;
static u16 s_usart0_tx_q_send_cnt = 0;

typedef struct
{
	u16 wr_idx;
	u16 rd_idx;
	char buffer[USART_RX_DMA_SIZ];
}usart_rx_type;

usart_rx_type gbl_usart0_rx_buff_proc;

#ifdef USE_AVR_STUDIO
ISR(USART0_RX_vect)
#else
void USART0_RX_vect(void)
#endif
{
#ifdef DEBUG_PORT_UART0
	u16 data_len;
	q_node_type* q_usart_pkt_ptr;
	s8 data[1];
	
	{

		data_len = 1;

		if( q_get_count(&gbl_qlist_usart0_rx_free) > 0 )
		{
			if( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_rx_free)) != NULL )
			{
				data[0] = UDR0;
				memcpy(q_usart_pkt_ptr->data, data, data_len);
				q_usart_pkt_ptr->len = data_len;
				q_add_tail(&gbl_qlist_usart0_rx, q_usart_pkt_ptr);

			}
		}	

	}

	// uart0_rx_event(data[0]);
	if( uart0_register_fn != NULL )
		uart0_register_fn(data[0]);
#else
	s8 data[1];

	data[0] = UDR0;

	//usart0_format_puts("\r\n uart0 data input : %x", data);

	if( uart0_register_fn != NULL )
		uart0_register_fn(data[0]);
#endif
}

#ifdef USE_AVR_STUDIO
ISR(USART1_RX_vect)
#else
void USART1_RX_vect(void)
#endif
{
#ifdef DEBUG_PORT_UART0
	s8 data[1];

	data[0] = UDR1;

	//usart0_format_puts("\r\n uart1 data input : %x", data);
	//usart0_puts("\r\n uart1 data input");
	//usart1_puts("\r\n uart1 data input");

	if( uart1_register_fn != NULL )
		uart1_register_fn(data[0]);
#else
	u16 data_len;
	q_node_type* q_usart_pkt_ptr;
	s8 data[1];
	
	{

		data_len = 1;

		if( q_get_count(&gbl_qlist_usart0_rx_free) > 0 )
		{
			if( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_rx_free)) != NULL )
			{
				data[0] = UDR1;
				memcpy(q_usart_pkt_ptr->data, data, data_len);
				q_usart_pkt_ptr->len = data_len;
				q_add_tail(&gbl_qlist_usart0_rx, q_usart_pkt_ptr);

			}
		}	

	}

	//usart0_format_puts("\r\n uart1 data input : %x", data);

	// uart1_rx_event(data[0]);
	if( uart1_register_fn != NULL )
		uart1_register_fn(data[0]);
#endif
}

void init_usart0_buffer(void)
{
	int i;

	q_remove_all(&gbl_qlist_usart0_tx);
	q_remove_all(&gbl_qlist_usart0_tx_free);

	// initialize usart tx queue buffer.
	for(i=0;i<USART_TX_BUFF_CNT;i++)
	{
		gbl_qdata_usart0_tx_free[i].data = &gbl_usart0_tx_buff[i];
		q_add_tail(&gbl_qlist_usart0_tx_free, &gbl_qdata_usart0_tx_free[i]);		
	}

	q_remove_all(&gbl_qlist_usart0_rx);
	q_remove_all(&gbl_qlist_usart0_rx_free);

	// initialize usart rx queue buffer.
	for(i=0;i<USART_RX_BUFF_CNT;i++)
	{
		gbl_qdata_usart0_rx_free[i].data = &gbl_usart0_rx_buff[i];
		q_add_tail(&gbl_qlist_usart0_rx_free, &gbl_qdata_usart0_rx_free[i]);		
	}

	memset(gbl_usart0_tx_buff_dma, 0x00, sizeof(char)*USART_TX_DMA_SIZ);
//	memset(gbl_usart0_rx_buff_dma, 0x00, sizeof(char)*USART_RX_DMA_SIZ);
	memset(gbl_usart0_rx_buff_proc.buffer, 0x00, sizeof(char)*USART_RX_DMA_SIZ);	
	gbl_usart0_rx_buff_proc.rd_idx = 0;
	gbl_usart0_rx_buff_proc.wr_idx = 0;


}

void usart0_tx_proc(void)
{
	int i;
	u16 data_len;
	q_node_type* q_usart_pkt_ptr;

	{
		while( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_tx)) != NULL )
		{
			data_len = q_usart_pkt_ptr->len;
			memcpy(gbl_usart0_tx_buff_dma, q_usart_pkt_ptr->data, q_usart_pkt_ptr->len);

			for(i=0;i<data_len;i++)
			{
				usart0_putc((u16)gbl_usart0_tx_buff_dma[i]);
			}
			q_add_tail(&gbl_qlist_usart0_tx_free, q_usart_pkt_ptr);

		}
	}	
	
}

void usart0_transmit_string(const void *data) 
{
	int i;
	u16 data_len;
	int tx_count;
	/*const */char* usart_data;
	q_node_type* q_usart_pkt_ptr;

	usart_data = (char*)data;
	data_len = strlen((char*)usart_data);

	tx_count = (data_len - 1) / USART_TX_DMA_SIZ + 1;

	INTLOCK();


	if( q_get_count(&gbl_qlist_usart0_tx_free) >= tx_count )
	{
		for(i=0;i<tx_count-1;i++)
		{
			if( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_tx_free)) != NULL )
			{
				memcpy(q_usart_pkt_ptr->data, usart_data, USART_TX_DMA_SIZ);
				q_usart_pkt_ptr->len = USART_TX_DMA_SIZ;
				q_add_tail(&gbl_qlist_usart0_tx, q_usart_pkt_ptr);

				data_len = data_len - USART_TX_DMA_SIZ;
				usart_data += USART_TX_DMA_SIZ;

			}
		}

		if( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_tx_free)) != NULL )
		{
			memcpy(q_usart_pkt_ptr->data, usart_data, data_len);
			q_usart_pkt_ptr->len = data_len;
			q_add_tail(&gbl_qlist_usart0_tx, q_usart_pkt_ptr);

		}
		
		usart0_tx_proc();
			
	}	


	INTFREE();
}

void* usart0_get_data(void)
{
	u16 data_len;
	q_node_type* q_usart_pkt_ptr;

	s_usart0_tx_q_free_cnt = q_get_count(&gbl_qlist_usart0_tx_free);
	s_usart0_tx_q_send_cnt = q_get_count(&gbl_qlist_usart0_tx);	


	{

		if( (q_usart_pkt_ptr = q_remove_tail(&gbl_qlist_usart0_rx)) != NULL )
		{
			data_len = q_usart_pkt_ptr->len;
			memcpy(gbl_usart0_rx_buff_proc.buffer, q_usart_pkt_ptr->data, q_usart_pkt_ptr->len);


			q_add_tail(&gbl_qlist_usart0_rx_free, q_usart_pkt_ptr);

			return gbl_usart0_rx_buff_proc.buffer;

		}


	}

	return NULL;
}

void bsp_usart0_gpio_init()
{
	// RXD를 입력으로
	cbi(USART0_RX_DDR, USART0_RX_PIN_NO);

	// TXD를 출력으로
	sbi(USART0_TX_DDR, USART0_TX_PIN_NO);
}

void register_uart0_function(uart_register_function fn)
{
	uart0_register_fn = fn;
}

void bsp_usart1_gpio_init()
{
	// RXD를 입력으로
	cbi(USART1_RX_DDR, USART1_RX_PIN_NO);

	// TXD를 출력으로
	sbi(USART1_TX_DDR, USART1_TX_PIN_NO);
}

void register_uart1_function(uart_register_function fn)
{
	uart1_register_fn = fn;
}

void bsp_usart_init(m128_uart_reg_type uartx, u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed )
{

#if 0
	u16 wUBRR;


	//- Warning - UBBRnH 설정 후 UBBRnL를 나중에 Write 해야 한다.
	if( bDoubleSpeed == TRUE )
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		sbi(*uartx.UCSRxA,U2X); 

		wUBRR = ((float)dwFOSC/(8. * (float)nBaudRate) - 1) * 1000.;
	}
	else
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		cbi(*uartx.UCSRxA,U2X); 

		wUBRR = ((float)dwFOSC/(16. * (float)nBaudRate) - 1) * 1000.;
	}

	// 반올림
	if( wUBRR % 10000 >= 500 )
		wUBRR = (wUBRR + 500)/1000;
	else
		wUBRR = wUBRR/1000;


	// RX Complete Interrupt ON
	// TX Complete Interrupt OFF
	// USART Data Register Empty Interrupt OFF
	// Receiver Enable
	// Transmitter Enable
	// Character Size UCSZ2 = 0
	*uartx.UCSRxB = (1 << TXEN ) | (1 << RXEN )/*|(1<<RXCIE)*/;


	/*-----------------------------------
	   UART UCSZ Bits Settings
	-------------------------------------
	   UCSZ2  UCSZ1  UCSZ0    Character Size
	=====================================
	     0      0      0         5-bit
	     0      0      1         6-bit
	     0      1      0         7-bit
	     0      1      1         8-bit
	     1      0      0         Reserved
	     1      0      1         Reserved
	     1      1      0         Reserved
	     1      1      1         9-bit
	------------------------------------*/	

	// USART Mode = Asynchronous
	// Parity Mode = Disabled(0,0)
	// Stop Bit Select = 1-bit
	// Character Size UCSZ = 8Bit(0, 1, 1)
	// Clock Polarity    = Not Setting(synchronous mode only)

	if( nDataBits == EData8 )
	{
		// default 값이 8Bit 로 설정 되어 있다.
		*uartx.UCSRxC = (1 << UCSZ1) | (1 << UCSZ0);
	}

	// UCSRC(USART Control and Status Register C) Initial  
	/*-----------------------------------
	   UART UPM Bits Settings
	-------------------------------------
	   UPM1  UPM0  Parity Mode
	=====================================
	    0      0      Disabled
	    0      1      Reserved
	    1      0      Enabled, Even Parity
	    1      1      Enabled, Odd Parity
	------------------------------------*/
	if( nParity == EParNone )
	{
		cbi(*uartx.UCSRxC,UPM1); // UART UPM Bits Setting Disabled	
		cbi(*uartx.UCSRxC,UPM0); // UART UPM Bits Setting Disabled	
	}
  
	/*-----------------------------------
	   UART USBS Bit Settings
	-------------------------------------
	   USBS  UStop Bit(s)
	=====================================
	    0      1-bit
	    1      2-bit
	------------------------------------*/
	if( nStopBits == EStop1 )
		cbi(*uartx.UCSRxC,USBS); //	USBS Bit Settings 1-bit	
	else
		sbi(*uartx.UCSRxC,USBS); //	USBS Bit Settings 2-bit	


	*uartx.UBRRxL = (unsigned char)wUBRR;
	*uartx.UBRRxH = (unsigned char)wUBRR >> 8;
#endif
}

void bsp_usart0_init(u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed )
{


#if 1

	u16 wUBRR;

	 UCSR0B = 0x00; //disable while setting baud rate
	 UCSR0A = 0x00;


	//- Warning - UBBRnH 설정 후 UBBRnL를 나중에 Write 해야 한다.
	if( bDoubleSpeed == TRUE )
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		sbi(UCSR0A,U2X0); 

		wUBRR = ((float)dwFOSC/(8. * (float)nBaudRate) - 1) * 1000.;
	}
	else
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		cbi(UCSR0A,U2X0); 

		wUBRR = ((float)dwFOSC/(16. * (float)nBaudRate) - 1) * 1000.;
	}

	// 반올림
	if( wUBRR % 10000 >= 500 )
		wUBRR = (wUBRR + 500)/1000;
	else
		wUBRR = wUBRR/1000;


	// RX Complete Interrupt ON
	// TX Complete Interrupt OFF
	// USART Data Register Empty Interrupt OFF
	// Receiver Enable
	// Transmitter Enable
	// Character Size UCSZ2 = 0
	UCSR0B = (1 << TXEN0 ) | (1 << RXEN0 ); // | (1<<RXCIE);


	/*-----------------------------------
	   UART UCSZ Bits Settings
	-------------------------------------
	   UCSZ2  UCSZ1  UCSZ0    Character Size
	=====================================
	     0      0      0         5-bit
	     0      0      1         6-bit
	     0      1      0         7-bit
	     0      1      1         8-bit
	     1      0      0         Reserved
	     1      0      1         Reserved
	     1      1      0         Reserved
	     1      1      1         9-bit
	------------------------------------*/	

	// USART Mode = Asynchronous
	// Parity Mode = Disabled(0,0)
	// Stop Bit Select = 1-bit
	// Character Size UCSZ = 8Bit(0, 1, 1)
	// Clock Polarity    = Not Setting(synchronous mode only)

	if( nDataBits == EData8 )
	{
		// default 값이 8Bit 로 설정 되어 있다.
		UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	}

	// UCSRC(USART Control and Status Register C) Initial  
	/*-----------------------------------
	   UART UPM Bits Settings
	-------------------------------------
	   UPM1  UPM0  Parity Mode
	=====================================
	    0      0      Disabled
	    0      1      Reserved
	    1      0      Enabled, Even Parity
	    1      1      Enabled, Odd Parity
	------------------------------------*/
	if( nParity == EParNone )
	{
		cbi(UCSR0C,UPM01); // UART UPM Bits Setting Disabled	
		cbi(UCSR0C,UPM00); // UART UPM Bits Setting Disabled	
	}
  
	/*-----------------------------------
	   UART USBS Bit Settings
	-------------------------------------
	   USBS  UStop Bit(s)
	=====================================
	    0      1-bit
	    1      2-bit
	------------------------------------*/
	if( nStopBits == EStop1 )
		cbi(UCSR0C,USBS0); //	USBS Bit Settings 1-bit	
	else
		sbi(UCSR0C,USBS0); //	USBS Bit Settings 2-bit	


#ifdef USE_AVR_STUDIO
	UBRR0L = (unsigned char)wUBRR;
	UBRR0H = (unsigned char)wUBRR >> 8;
#else
	// ICCAVR은baudrate가 수식으로 잘 안되네요.
	// 나중에 보완 필요
	if( F_CPU == 16000000UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR0L= 25;
			UBRR0H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR0L= 8;
			UBRR0H= 0x00;
		}			
	}
	else if( F_CPU == 7372800UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR0L= 11;
			UBRR0H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR0L= 3;
			UBRR0H= 0x00;
		}	
	}
	else if( F_CPU == 8000000UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR0L= 12;
			UBRR0H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR0L= 3;
			UBRR0H= 0x00;
		}	
	}
#endif	 
	
#endif


}


void bsp_usart0_interrupt_enable() 
{
	sbi(UCSR0B, RXCIE0);
}

void bsp_usart0_interrupt_disable() 
{
	cbi(UCSR0B, RXCIE0);
}

void usart0_putc(char ch)
{

#if 1
    while (((UCSR0A>>UDRE0)&0x01) == 0) ;  // UDRE, data register empty
        
    UDR0 = ch;
#endif   


#if 0

	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
#endif
}

// 버퍼를 사용하지 않고 전송
void usart0_puts(char *data) 
{
  int len, count;
  
  len = strlen(data);
  for (count = 0; count < len; count++) 
    usart0_putc(*(data+count));
}

void usart0_format_puts(/*const */char * szFormat, ... ) 
{
	va_list varpars;
	int nLen;

	va_start(varpars, szFormat);
	nLen = vsprintf( (char*)usart_format_buff, szFormat, varpars);
	va_end(varpars);

	usart_format_buff[nLen] = 0x00;

	usart0_puts(usart_format_buff);	
}

char usart0_getc() 
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;

	/* Get and return received data from buffer */
	return UDR0;
}


void bsp_usart1_init(u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed )
{


	u16 wUBRR;


	//- Warning - UBBRnH 설정 후 UBBRnL를 나중에 Write 해야 한다.
	if( bDoubleSpeed == TRUE )
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		sbi(UCSR1A,U2X1); 

		wUBRR = ((float)dwFOSC/(8. * (float)nBaudRate) - 1) * 1000.;
	}
	else
	{
		// UCSRA(USART Control and Status Register A) Initial 
		// U2X: Double the USART Transmission Speed
		cbi(UCSR1A,U2X1); 

		wUBRR = ((float)dwFOSC/(16. * (float)nBaudRate) - 1) * 1000.;
	}

	// 반올림
	if( wUBRR % 10000 >= 500 )
		wUBRR = (wUBRR + 500)/1000;
	else
		wUBRR = wUBRR/1000;


	// RX Complete Interrupt ON
	// TX Complete Interrupt OFF
	// USART Data Register Empty Interrupt OFF
	// Receiver Enable
	// Transmitter Enable
	// Character Size UCSZ2 = 0
	UCSR1B = (1 << TXEN1 ) | (1 << RXEN1 ); // | (1<<RXCIE);


	/*-----------------------------------
	   UART UCSZ Bits Settings
	-------------------------------------
	   UCSZ2  UCSZ1  UCSZ0    Character Size
	=====================================
	     0      0      0         5-bit
	     0      0      1         6-bit
	     0      1      0         7-bit
	     0      1      1         8-bit
	     1      0      0         Reserved
	     1      0      1         Reserved
	     1      1      0         Reserved
	     1      1      1         9-bit
	------------------------------------*/	

	// USART Mode = Asynchronous
	// Parity Mode = Disabled(0,0)
	// Stop Bit Select = 1-bit
	// Character Size UCSZ = 8Bit(0, 1, 1)
	// Clock Polarity    = Not Setting(synchronous mode only)

	if( nDataBits == EData8 )
	{
		// default 값이 8Bit 로 설정 되어 있다.
		UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
	}

	// UCSRC(USART Control and Status Register C) Initial  
	/*-----------------------------------
	   UART UPM Bits Settings
	-------------------------------------
	   UPM1  UPM0  Parity Mode
	=====================================
	    0      0      Disabled
	    0      1      Reserved
	    1      0      Enabled, Even Parity
	    1      1      Enabled, Odd Parity
	------------------------------------*/
	if( nParity == EParNone )
	{
		cbi(UCSR1C,UPM11); // UART UPM Bits Setting Disabled	
		cbi(UCSR1C,UPM10); // UART UPM Bits Setting Disabled	
	}
  
	/*-----------------------------------
	   UART USBS Bit Settings
	-------------------------------------
	   USBS  UStop Bit(s)
	=====================================
	    0      1-bit
	    1      2-bit
	------------------------------------*/
	if( nStopBits == EStop1 )
		cbi(UCSR1C,USBS1); //	USBS Bit Settings 1-bit	
	else
		sbi(UCSR1C,USBS1); //	USBS Bit Settings 2-bit	


#ifdef USE_AVR_STUDIO
	UBRR1L = (unsigned char)wUBRR;
	UBRR1H = (unsigned char)wUBRR >> 8;
#else	
	// ICCAVR은baudrate가 수식으로 잘 안되네요.
	// 나중에 보완 필요
	if( F_CPU == 16000000UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR1L= 25;
			UBRR1H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR1L= 8;
			UBRR1H= 0x00;
		}			
	}
	else if( F_CPU == 7372800UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR1L= 11;
			UBRR1H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR1L= 3;
			UBRR1H= 0x00;
		}	
	}
	else if( F_CPU == 8000000UL )
	{
		if( nBaudRate == EBaud38400 )
		{
			UBRR1L= 12;
			UBRR1H= 0x00;
		}
		else if( nBaudRate == EBaud115200 )	
		{
			UBRR1L= 3;
			UBRR1H= 0x00;
		}	
	}
#endif	 


}


void bsp_usart1_interrupt_enable() 
{
	sbi(UCSR1B, RXCIE1);
}

void bsp_usart1_interrupt_disable() 
{
	cbi(UCSR1B, RXCIE1);
}

void usart1_putc(char ch)
{

	while (!(UCSR1A & (1<<UDRE1)));
	UDR1 = ch;
}

// 버퍼를 사용하지 않고 전송
void usart1_puts(char *data) 
{
  int len, count;
  
  len = strlen(data);
  for (count = 0; count < len; count++) 
    usart1_putc(*(data+count));
}

// 메모리 부족으로 0 버퍼를 같이 사용한다.
void usart1_format_puts(/*const */char * szFormat, ... ) 
{
	va_list varpars;
	int nLen;

	va_start(varpars, szFormat);
	nLen = vsprintf( (char*)usart_format_buff, szFormat, varpars);
	va_end(varpars);

	usart_format_buff[nLen] = 0x00;

	usart1_puts(usart_format_buff);	
}

char usart1_getc() 
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;

	/* Get and return received data from buffer */
	return UDR1;
}

// 메모리 부족으로 0 버퍼를 같이 사용한다.
void usart1_transmit_string(const void *data) 
{
	usart0_transmit_string(data);
}

// 메모리 부족으로 0 버퍼를 같이 사용한다.
void* usart1_get_data(void)
{
	return usart0_get_data();
}

