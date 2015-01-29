
#ifndef __UTIL_H
#define __UTIL_H




/*-------------------------------------------------------------------
*	Common Typedef part
*------------------------------------------------------------------*/
//typedef unsigned char 	BOOL;
//typedef signed 	char 	BYTE;
//typedef unsigned char 	UBYTE;
//typedef unsigned int 	WORD;
//typedef unsigned long 	DWORD;
//typedef signed int 		SWORD;

// GCC	 , 			바이트수, 		표현범위
// int8_t, 				   1,  		-128 ~ +127
// typedef signed char			char;
typedef signed char			s8;
 
// uint8_t,				   1, 		 0 ~ 255
// typedef unsigned char		bool;
typedef unsigned char		byte;
typedef unsigned char		u8;

 
// int16_t, 			   2,		 -32768 ~ +32767
typedef signed int			s16;
 
// uint16_t,			   2,		 0 ~ 65535
typedef unsigned int		u16;

 
// int32_t,				   4,		 -2147483648 ~ +21474783647
typedef signed long			s32;
 

// uint32_t, 			   4,		 0 ~ 4294967295
typedef unsigned long		u32;
 
// int64_t, 			   8,		 -9.22×10^18 ~ +9.22×10^18
typedef signed long long	s64;
 

// uint64_t, 			   8,		 0 ~ 1.844×10^19
typedef unsigned long long 	u64;



#define TRUE			( 1 )
#define FALSE			( 0 )

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef signed char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

typedef unsigned char 	BOOL;

/* Boolean type */
//typedef enum { FALSE = 0, TRUE } BOOL;

typedef enum
{
	BIT0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7
}  enumBIT;

#define sbi(port, bit) 				(port |= (1<<bit))
#define cbi(port, bit) 				(port &= (~(1<<bit)))

#define inp(port, bit) 				(port & (1<<bit))

#define BIT0_MASK 					( 0x01 )
#define BIT1_MASK 					( 0x02 )
#define BIT2_MASK 					( 0x04 )
#define BIT3_MASK 					( 0x08 )
#define BIT4_MASK 					( 0x10 )
#define BIT5_MASK 					( 0x20 )
#define BIT6_MASK 					( 0x40 )
#define BIT7_MASK 					( 0x80 )



#define INTLOCK()					CLI()
#define INTFREE()					SEI()

/*------------------------------------------------------------------*/

void delay_us(u16 us);
#ifndef USE_AVR_STUDIO
void _delay_ms(unsigned int millisec);
#endif
byte crc8(byte *ptr, byte len);
void bcd2ascii(byte BCD,byte ptasc[]);
void __ftoa(float f, unsigned char *buf, char DecPoint);

/*------------------------------------------------------------------*/



#endif
