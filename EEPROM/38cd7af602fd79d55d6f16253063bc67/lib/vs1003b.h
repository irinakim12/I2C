/*******************************************************************/
/*          Head file of VS1003B.c  for  Mega8 MP3 Player          */
/*                                                                 */
/* Platform   : AVRStudio4.13 b528 + WinAVR20070525                */
/*              optimize -0s                                       */
/* Author     : bozai(Zhang Qibo)                                  */
/* E-mail     : sudazqb@163.com                                    */
/* MSN        : zhangqibo_1985@hotmail.com                         */
/* Date       : 2006-05-09                                         */
/*******************************************************************/
/*2007-05-04: add slow start up code, and add enough dealy         */
/*2007-04-21:                                                      */
/*******************************************************************/

#ifndef __VS1003B_H__
#define __VS1003B_H__

#define DEFAULT_MODE   0
#define MP3 1
#define WMA 2
#define MID 3

#define VS_WRITE_COMMAND 	0x02
#define VS_READ_COMMAND 	0x03		 		 

#define SPI_MODE        	0x00   
#define SPI_STATUS      	0x01   
#define SPI_BASS        	0x02   
#define SPI_CLOCKF      	0x03   
#define SPI_DECODE_TIME 	0x04   
#define SPI_AUDATA      	0x05   
#define SPI_WRAM        	0x06   
#define SPI_WRAMADDR    	0x07   
#define SPI_HDAT0       	0x08   
#define SPI_HDAT1       	0x09   
#define SPI_AIADDR      	0x0a   
#define SPI_VOL         	0x0b   
#define SPI_AICTRL0     	0x0c   
#define SPI_AICTRL1     	0x0d   
#define SPI_AICTRL2     	0x0e   
#define SPI_AICTRL3     	0x0f   
#define SM_DIFF         	0x01   
#define SM_JUMP         	0x02   
#define SM_RESET        	0x04   
#define SM_OUTOFWAV     	0x08   
#define SM_PDOWN        	0x10   
#define SM_TESTS        	0x20   
#define SM_STREAM       	0x40   
#define SM_PLUSV        	0x80   
#define SM_DACT         	0x100   
#define SM_SDIORD       	0x200   
#define SM_SDISHARE     	0x400   
#define SM_SDINEW       	0x800   
#define SM_ADPCM        	0x1000   
#define SM_ADPCM_HP     	0x2000 


#define MP3CMD_InitVS1003		0x11
#define MP3CMD_Play				0x12
#define MP3CMD_Pause			0x13
#define MP3CMD_Stop				0x14
#define MP3CMD_Next				0x15
#define MP3CMD_TestVS1003		0x16


#define DefaultVolume   0x4444
#define CLOCK_REG      0xc000 //0x1c00 //0x1800 //0x1000 //0x4400 //0x0800 //0x1000 //0x2800 //0x0000 // 0x2000 //0x4000 //0x6000 //0xa000 //0xe000  // 0x0000

#define VS1003B_PORT    		PORTC
#define VS1003B_DDR      		DDRC
#define VS1003B_PIN      		PINC

#define VS1003B_XCS     		PC5
#define VS1003B_XRESET  		PC3
#define VS1003B_DREQ    		PC2
#define VS1003B_XDCS    		PC4


#define PORT_INI()        		VS1003B_DDR |= _BV(VS1003B_XCS)|_BV(VS1003B_XRESET)|_BV(VS1003B_XDCS)

#define VS1003B_XCS_H()    	VS1003B_PORT |=  _BV(VS1003B_XCS)
#define VS1003B_XCS_L()    	VS1003B_PORT &= ~_BV(VS1003B_XCS)

#define VS1003B_XRESET_H()    VS1003B_PORT |=  _BV(VS1003B_XRESET)
#define VS1003B_XRESET_L()    	VS1003B_PORT &= ~_BV(VS1003B_XRESET)

#define VS1003B_XDCS_H()    	VS1003B_PORT |=  _BV(VS1003B_XDCS)
#define VS1003B_XDCS_L()    	VS1003B_PORT &= ~_BV(VS1003B_XDCS)

extern void VS1003B_SPI_Low(void);
extern void VS1003B_SPI_High(void);
extern unsigned char VS1003B_WriteByte(unsigned char CH);
extern unsigned char VS1003B_ReadByte();
extern void VS1003B_WriteCMD(unsigned char addr, unsigned int dat);
extern unsigned int VS1003B_ReadCMD(unsigned char addr);
extern void VS1003B_WriteDAT(unsigned char dat);
extern unsigned char VS1003B_NeedData(void);
extern void VS1003B_Fill2048Zero();
extern void VS1003B_Write32B(unsigned char * buf);
extern unsigned char VS1003B_Init();
extern void VS1003B_SoftReset();
extern void VS1003B_SineTest();
#endif

