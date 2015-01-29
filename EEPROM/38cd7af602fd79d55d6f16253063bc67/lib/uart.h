
#ifndef __UART_H
#define __UART_H

typedef enum
{
	uart0 = 0x00,
	uart1,
	uartMax
} bsp_uart_type;

// uart0
#define USART0_RX_DDR			DDRE
#define USART0_RX_PORT			PORTE
#define USART0_RX_PIN_NO		PE0

#define USART0_TX_DDR			DDRE
#define USART0_TX_PORT			PORTE
#define USART0_TX_PIN_NO		PE1

// uart1
#define USART1_RX_DDR			DDRD
#define USART1_RX_PORT			PORTD
#define USART1_RX_PIN_NO		PD2

#define USART1_TX_DDR			DDRD
#define USART1_TX_PORT			PORTD
#define USART1_TX_PIN_NO		PD3

typedef struct
{
	u16* UCSRxA;
	u16* UCSRxB;
	u16* UCSRxC;
	u16* UBRRxL;
	u16* UBRRxH;
} m128_uart_reg_type;

typedef            void     (*uart_register_function)(char data);

// Baudrate
typedef enum
{
	EBaudUnknown = -1,			// Unknown
	EBaud4800    = 4800,	// 4800 bits/sec
	EBaud9600    = 9600,	// 9600 bits/sec
	EBaud14400   = 14400,	// 14400 bits/sec
	EBaud19200   = 19200,	// 19200 bits/sec (default)
	EBaud28800   = 28800,	// 28800 bits/sec
	EBaud38400   = 38400,	// 38400 bits/sec
	EBaud57600   = 57600,	// 57600 bits/sec
	EBaud76800   = 76800,	// 76800 bits/sec
	EBaud115200  = 115200,	// 115200 bits/sec
	EBaud230400  = 230400,	// 230400 bits/sec
	EBaud256000  = 256000,	// 256000 bits/sec
	EBaud460000  = 460000,	// 460000 bits/sec
	EBaud920000  = 920000,	// 920000 bits/sec
	EBaud921600  = 921600,	// 921600 bits/sec
} enumBaudrate;

// Data bits (5-8)
typedef enum
{
	EDataUnknown = -1,	// Unknown
	EData5       =  5,	// 5 bits per byte
	EData6       =  6,	// 6 bits per byte
	EData7       =  7,	// 7 bits per byte
	EData8       =  8	// 8 bits per byte (default)
} enumDataBits;

// Parity scheme
typedef enum
{
	EParUnknown = -1,	// Unknown
	EParNone    = 0,	// No parity (default)
	EParOdd     = 1,	// Odd parity
	EParEven    = 2,	// Even parity
} enumParity;

// Stop bits
typedef enum
{
	EStopUnknown = -1,	// Unknown
	EStop1       = 1,	// 1 stopbit (default)	
	EStop2       = 2	// 2 stopbits
} enumStopBits;

void init_usart0_buffer(void);
void usart0_transmit_string(const void *data);
void* usart0_get_data(void);
void usart0_tx_proc(void);


void bsp_usart_init(m128_uart_reg_type uartx, u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed );

void bsp_usart0_gpio_init(void);
void register_uart0_function(uart_register_function fn);
void bsp_usart0_init(u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed );
void usart0_putc(char ch);
void usart0_puts(char *data);
void usart0_format_puts(/*const */char * szFormat, ... );
char usart0_getc(void);
void bsp_usart0_interrupt_enable(void);
void bsp_usart0_interrupt_disable(void);

void bsp_usart1_gpio_init(void);
void register_uart1_function(uart_register_function fn);
void bsp_usart1_init(u32 dwFOSC, enumBaudrate nBaudRate, enumDataBits nDataBits, enumParity nParity, enumStopBits nStopBits, byte bDoubleSpeed );
void usart1_putc(char ch);
void usart1_puts(char *data);
void usart1_format_puts(/*const */char * szFormat, ... );
char usart1_getc();
void bsp_usart1_interrupt_enable(void);
void bsp_usart1_interrupt_disable(void);
void usart1_transmit_string(const void *data);
void* usart1_get_data(void);

#endif
