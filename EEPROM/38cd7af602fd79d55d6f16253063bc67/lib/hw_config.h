

#ifndef __HWCONFIG_H
#define __HWCONFIG_H

#ifdef __ICC_VERSION
	  #define USE_ICC_AVR
#else
	  #define USE_AVR_STUDIO
#endif

#ifdef USE_AVR_STUDIO
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nop()  __asm__ __volatile__ ("nop" ::)

#define CLI() cli()
#define SEI() sei()

/* program memory space abstraction */ 
#define FLASH_DECLARE(x) x __attribute__((__progmem__)) 
#define FLASH_STRING(x) PSTR(x) 
#define FLASH_STRING_T  PGM_P 
#define PGM_READ_BYTE(x) pgm_read_byte(x) 
#define PGM_READ_WORD(x) pgm_read_word(x) 
#define PGM_READ_BLOCK(dst, src, len) memcpy_P((dst), (src), (len)) 
#define PGM_STRLEN(x) strlen_P(x) 
#define PGM_STRCPY(dst, src) strcpy_P((dst), (src)) 
 
#else

#include <iom128v.h>
#include<macros.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nop()  asm("nop");
#define _BV(bit) (1 << (bit))

/* program memory space abstraction */ 
#define FLASH_DECLARE(x) __flash x 
#define FLASH_STRING(x) ((__flash const char *)(x)) 
#define FLASH_STRING_T  char const __flash * 
#define PGM_READ_BYTE(x) *(x) 
#define PGM_READ_WORD(x) *(x) 
#define PGM_READ_BLOCK(dst, src, len) memcpy_P((dst), (src), (len)) 
#define PGM_STRLEN(x) strlen_P(x) 
#define PGM_STRCPY(dst, src) strcpy_P((dst), (src)) 


/* Interrupt Vector Numbers */
/*
#define iv_RESET        1
#define iv_INT0         2
#define iv_EXT_INT0     2
#define iv_INT1         3
#define iv_EXT_INT1     3
#define iv_INT2         4
#define iv_EXT_INT2     4
#define iv_INT3         5
#define iv_EXT_INT3     5
#define iv_INT4         6
#define iv_EXT_INT4     6
#define iv_INT5         7
#define iv_EXT_INT5     7
#define iv_INT6         8
#define iv_EXT_INT6     8
#define iv_INT7         9
#define iv_EXT_INT7     9
#define iv_TIMER2_COMPA 10
#define iv_TIMER2_COMP  10
#define iv_TIM2_COMP    10
#define iv_TIMER2_OVF   11
#define iv_TIM2_OVF     11
#define iv_TIMER1_CAPT  12
#define iv_TIM1_CAPT    12
#define iv_TIMER1_COMPA 13
#define iv_TIM1_COMPA   13
#define iv_TIMER1_COMPB 14
#define iv_TIM1_COMPB   14
#define iv_TIMER1_OVF   15
#define iv_TIM1_OVF     15
#define iv_TIMER0_COMPA 16
#define iv_TIMER0_COMP  16
#define iv_TIM0_COMP    16
#define iv_TIMER0_OVF   17
#define iv_TIM0_OVF     17
#define iv_SPI_STC      18
#define iv_USART0_RX    19
#define iv_USART0_RXC   19
#define iv_USART0_DRE   20
#define iv_USART0_UDRE  20
#define iv_USART0_TX    21
#define iv_USART0_TXC   21
#define iv_ADC          22
#define iv_EE_RDY       23
#define iv_EE_READY     23
#define iv_ANA_COMP     24
#define iv_ANALOG_COMP  24
#define iv_TIMER1_COMPC 25
#define iv_TIM1_COMPC   25
#define iv_TIMER3_CAPT  26
#define iv_TIM3_CAPT    26
#define iv_TIMER3_COMPA 27
#define iv_TIM3_COMPA   27
#define iv_TIMER3_COMPB 28
#define iv_TIM3_COMPB   28
#define iv_TIMER3_COMPC 29
#define iv_TIM3_COMPC   29
#define iv_TIMER3_OVF   30
#define iv_TIM3_OVF     30
#define iv_USART1_RX    31
#define iv_USART1_RXC   31
#define iv_USART1_DRE   32
#define iv_USART1_UDRE  32
#define iv_USART1_TX    33
#define iv_USART1_TXC   33
#define iv_TWI          34
#define iv_TWSI         34
#define iv_SPM_RDY      35
#define iv_SPM_READY    35
*/

#endif

#include "util.h"


#ifndef F_CPU
//#define F_CPU 16000000UL
#define F_CPU 7372800UL
//#define F_CPU 8000000UL
#endif

#ifndef __AVR_ATmega128__
#define __AVR_ATmega128__
#endif


//#define M128_MIDDLE_HW_VER1
#define M128_MIDDLE_HW_VER2

#define DEBUG_PORT_UART0
//#define DEBUG_PORT_UART1






typedef struct
{
	u16 *ddr;
	u16 *port;
	u16 *pin;
	u16 pin_no;
} bsp_port_group_type;

#endif
