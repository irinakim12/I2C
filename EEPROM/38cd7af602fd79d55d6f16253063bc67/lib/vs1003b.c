/*******************************************************************/
/*          VS1003 diriver for  Mega8 MP3 Player                   */
/*                                                                 */
/* Platform   : AVRStudio4.13 b528 + WinAVR20070122                */
/*              optimize -0s                                       */
/* Author     : bozai(Zhang Qibo)                                  */
/* E-mail     : sudazqb@163.com                                    */
/* MSN        : zhangqibo_1985@hotmail.com                         */
/* Date       : 2006-05-09                                         */
/*******************************************************************/
/*2007-10-19: use new delay function                               */
/*2007-05-04: add slow start up code, and add enough delay         */
/*2007-04-21:                                                      */


#include "hw_config.h"
#include "vs1003b.h"


#define uchar unsigned char
#define uint  unsigned int

#if 0
	// also need to set SS as output
	SPI_DDR |= (1<<SPI_CS_PIN_NO);

	SPCR = (1<<MSTR)|(1<<SPE);	// enable SPI interface
	SPSR = (1<<SPI2X);  // SPI Double speed
#endif	
	
//以最低速度运行	//low speed
void VS1003B_SPI_Low(void)
{
	SPCR =   _BV(SPE)|_BV(MSTR)|_BV(SPR1)|_BV(SPR0);
	SPSR &= ~_BV(SPI2X);
}

//以FCK/4速度运行	//full speed
void VS1003B_SPI_High(void)
{
	//SPCR =  _BV(SPE)|_BV(MSTR);
	//SPSR |= _BV(SPI2X);

	SPCR = (1<<MSTR)|(1<<SPE);	// enable SPI interface
	SPSR = (1<<SPI2X);  // SPI Double speed	
}

//延时		//delay
void VS1003B_Delay( unsigned int n)
{
	while(n--)asm("nop");
}

//write one byte to vs1003
unsigned char VS1003B_WriteByte(unsigned char CH)
{   
	SPDR = CH;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}

//从VS1003读一字节		//read one byte from vs1003
unsigned char VS1003B_ReadByte()
{
	SPDR = 0xff;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}

//写寄存器，参数，地址和数据	//config register
void VS1003B_WriteCMD(unsigned char addr, unsigned int dat)
{
	VS1003B_XDCS_H();
	VS1003B_XCS_L();
	VS1003B_WriteByte(0x02);
	VS1003B_WriteByte(addr);
	VS1003B_WriteByte(dat>>8);
	VS1003B_WriteByte(dat);
	VS1003B_XCS_H();
}

//读寄存器，参数 地址 返回内容	//read register
unsigned int VS1003B_ReadCMD(unsigned char addr)
{
	unsigned int temp;
	VS1003B_XDCS_H();
	VS1003B_XCS_L();
	VS1003B_WriteByte(0x03);
	VS1003B_WriteByte(addr);
	temp = VS1003B_ReadByte();
	temp <<= 8;
	temp += VS1003B_ReadByte();
	VS1003B_XCS_H();
	return temp;
}

//写数据，音乐数据		//write data (music data)
void VS1003B_WriteDAT(unsigned char dat)
{
	VS1003B_XDCS_L();
	VS1003B_WriteByte(dat);
	VS1003B_XDCS_H();
	VS1003B_XCS_H();
}

unsigned char VS1003B_NeedData(void)   
{   
    if(VS1003B_PIN & (1<<VS1003B_DREQ))
		return 1;   
    else 
		return 0;   
} 

/* fill 2048 zero */   
void VS1003B_Fill2048Zero()   
{   
    unsigned char i,j;   
    for(i=0;i<64;i++)   
    {   
        VS1003B_XDCS_L();   
        while(VS1003B_NeedData()==0);   
        for(j=0;j<32;j++)   
        {   
            VS1003B_WriteByte(0x00);   
        }   
        VS1003B_XDCS_H();   
    }   
}   
   
/* Write 32bytes data */   
void VS1003B_Write32B(unsigned char * buf)   
{   
    unsigned char n = 32;   
    VS1003B_XDCS_L();   
    while(n--)   
    {   
        VS1003B_WriteByte(*buf++);   
    }   
    VS1003B_XDCS_H();   
}   

// 1 means fail, 0 OK!
unsigned char VS1003B_Init()
{
	unsigned char retry;
	
	PORT_INI();
	VS1003B_DDR &=~_BV(VS1003B_DREQ);
	
	VS1003B_XCS_H();
	VS1003B_XDCS_H();
	VS1003B_XRESET_L();
	_delay_ms(40);
	VS1003B_XRESET_H();//chip select
	VS1003B_SPI_Low();//low speed
	_delay_ms(40);//delay

	retry=0;

#if 1

	while(VS1003B_ReadCMD(0x03) != CLOCK_REG)//set PLL register
	{
		VS1003B_WriteCMD(0x03,CLOCK_REG);
		if(retry++ >10 )return 1;
	}
#endif	

	_delay_ms(20);

#if 0	
	VS1003B_WriteCMD(0x05,0x000a);
	
	retry=0;
	while(VS1003B_ReadCMD(0x0b) != 0xfefe)//set Volume
	{
		VS1003B_WriteCMD(0x0b,0xfefe);
		if(retry++ >10 )return 1;
	}


	VS1003B_WriteCMD(0x05,0xac45);
#endif	

	retry=0;
	while(VS1003B_ReadCMD(0x0b) != DefaultVolume)//set Volume
	{
		VS1003B_WriteCMD(0x0b,DefaultVolume);
		if(retry++ >10 )return 1;
	}

#if 1
	retry=0;
	while(VS1003B_ReadCMD(0x00) != 0x0800)//set mode register
	{
		VS1003B_WriteCMD(0x00, 0x0800);
		if(retry++ >10 )return 1;//
	}
#endif	



#if 0
    VS1003B_WriteCMD(0x00,0x0800);     //NEW MODE       
//  vs1003_cmd_write(0x02,0X1fff);       //BASS     
    VS1003B_WriteCMD(0x03,0X6000);     //CLOCK F   
 VS1003B_WriteCMD(0x0b,0x2020);  //
#endif

	_delay_ms(20);

	VS1003B_SoftReset();

	_delay_ms(20);

	VS1003B_SPI_High();
	
	return 0;
}

void VS1003B_Reset()
{
	VS1003B_XRESET_L();
	_delay_ms(100);
	VS1003B_WriteByte(0xff);
	VS1003B_XCS_H();   							//xCS = 1
	VS1003B_XDCS_H();     								//xDCS = 1	
	VS1003B_XRESET_H();//chip select

	_delay_ms(100);
	while(VS1003B_NeedData()==0);
	_delay_ms(100);

	VS1003B_SoftReset();
}


//VS1003软件复位	//VS1003 soft reset
void VS1003B_SoftReset()
{
	VS1003B_SPI_High();   
	VS1003B_WriteCMD(0x00,0x0804);//写复位		//reset
//	VS1003B_Delay(0xffff);//延时，至少1.35ms //wait at least 1.35ms
	_delay_ms(20);
}

void VS1003B_SetVolume (unsigned char leftchannel, unsigned char rightchannel) 
{ 
	u16 vol;

	VS1003B_SPI_High();   
	vol = leftchannel | (u16)rightchannel<<8;
	VS1003B_WriteCMD(SPI_VOL, DefaultVolume);
}

void VS1003B_SineTest()
{
	VS1003B_XRESET_L();

	VS1003B_Reset();

	_delay_ms(100);

	VS1003B_WriteByte(0xff);      

	VS1003B_XCS_L();   							//xCS = 1
	VS1003B_XDCS_H();     								//xDCS = 1	
	VS1003B_XRESET_H();//chip select	
	
	VS1003B_Reset();
	_delay_ms(100);

	VS1003B_WriteCMD(0x0b,DefaultVolume);

	VS1003B_WriteCMD(SPI_MODE,0x0820);

	_delay_ms(200);

	
	while(VS1003B_NeedData()==0);

	VS1003B_XDCS_L();   	
 	// to vs1003 transmission sine test order: 0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
 	// n = 0x24, establishes the sine wave frequency value which vs1003 produces, the concrete computational method sees vs1003 datasheet VS1003B_WriteByte(0x53);      
 	VS1003B_WriteByte(0x53);      
	VS1003B_WriteByte(0xef);      
	VS1003B_WriteByte(0x6e);      
	VS1003B_WriteByte(0x24);      
	VS1003B_WriteByte(0x00);      
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
// OSTimeDly(OS_TICKS_PER_SEC/2);
	_delay_ms(500);
	VS1003B_XDCS_H();     // program execution here, should be able from the sole frequency sound
  	
    // withdrawal sine test				 
	VS1003B_XDCS_L();     
	VS1003B_WriteByte(0x45);
	VS1003B_WriteByte(0x78);
	VS1003B_WriteByte(0x69);
	VS1003B_WriteByte(0x74);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
// OSTimeDly(OS_TICKS_PER_SEC/2);
	_delay_ms(500);
	VS1003B_XDCS_H();     

    // enters the sine to test and to establish the n value is 0x44 once more, soon the sine wave frequency establishes as other value VS1003B_XDCS_L();     
	VS1003B_WriteByte(0x53);      
	VS1003B_WriteByte(0xef);      
	VS1003B_WriteByte(0x6e);      
	VS1003B_WriteByte(0x44);      
	VS1003B_WriteByte(0x00);      
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
// OSTimeDly(OS_TICKS_PER_SEC/2);
	_delay_ms(500);
	VS1003B_XDCS_H();     

	// withdrawal sine test
	VS1003B_XDCS_L();     
	VS1003B_WriteByte(0x45);
	VS1003B_WriteByte(0x78);
	VS1003B_WriteByte(0x69);
	VS1003B_WriteByte(0x74);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
	VS1003B_WriteByte(0x00);
// OSTimeDly(OS_TICKS_PER_SEC/2);
	_delay_ms(500);
	VS1003B_XDCS_H();     
}

