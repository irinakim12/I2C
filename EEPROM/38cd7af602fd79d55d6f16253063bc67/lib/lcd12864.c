
#include "hw_config.h"
#include "lcd12864.h"


void LCD_Init0(void)
{
	byte cmd;
	cmd=0x30;   // function set 8-bit data, the basic instructions
	W_1byte(0,0,cmd);	// write command
	Delay(2);
	cmd=0x0C;   // display status ON, cursor OFF, highlight OFF
	W_1byte(0,0,cmd); 
	Delay(2);
	cmd=0x01;   // clear display
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x02;   // address of homing
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x80;   // Set DDRAM address
	W_1byte(0,0,cmd);
	Delay(2);
	// Char_Set_XY(0,1,"LCD initializing");
	// Char_Set_XY(0,2,"Please wait a moment.");
	Delay(200); 
	//Delay(2500); 
}

void LCD_Init1(void)
{
	byte cmd;
	cmd=0x30;   //  function set 8-bit data, the basic instructions
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x0C;   // display status ON, cursor OFF, highlight OFF
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x01;   // clear display
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x02;   // address of homing
	W_1byte(0,0,cmd);
	Delay(2);
	cmd=0x80;   // Set DDRAM address
	W_1byte(0,0,cmd);
	Delay(2);
}

/************************************************* ******************
	Entry parameters: RW, RS, W_data
	Export parameters: None
	Function effect: to write a byte of data to the 12864, including instruction and data
	Description: RW = 1, read data from the LCD to the MCU; RW = 0, write data to the LCD;
		(RW are usually set to 0, that is, only write data to the LCD, do not read data)
		RS = 1, write the data; RS = 0, write the instructions;
		General pattern: RW = 0, RS = 1; write data
		RW = 0, RS = 0; written instructions
************************************************** ******************/
void W_1byte(byte RW, byte RS, byte W_data)
{
	u16 H_data,L_data,S_ID = 0xf8;  //11111RWRS0
	if(RW == 0)
	{
		S_ID &=~ 0x04;
	}
	else     //if(RW==1)
	{
		S_ID |= 0X04;
	}
	
	if(RS == 0)
	{
		S_ID &=~ 0x02;
	}
	else     //if(RS==1)
	{
		S_ID |= 0X02;
	}
	
	H_data = W_data;
	H_data &= 0xf0;   // lower 4 bits of data mask
	L_data = W_data;     // xxxx0000 format
	L_data &= 0x0f;   // 4 bits of data mask
	L_data <<= 4;   // xxxx0000 format
	Set_CS();
	
	Write_8bits(S_ID);   // send S_ID
	Write_8bits(H_data); // send H_data
	Write_8bits(L_data); // send L_data
	Clr_CS(); 
}

/********************************************************************
Function of the role: Responsible for serial output 8 bit digital
********************************************************************/
void Write_8bits(u16 W_bits)
{
	u16 i,Temp_data;
	for(i=0; i<8; i++)
	{
		Temp_data = W_bits;
		Temp_data <<= i;
		if((Temp_data&0x80)==0)
		{
			Clr_SID();
		}
		else
		{
			Set_SID();
		} 
		nop();
		Set_SCLK();
		
		nop();
		nop();
		
		Clr_SCLK();
		nop();
		
		Clr_SID();
	}
}

/********************************************************************
Function role: millisecond delay procedure, when the crystal is 12Mhz when, xtal = 12
********************************************************************/
void Delay(u16 ms) 
{ 
    u16 i; 
    while(ms--)    
   { 
     for(i=1;i<(u16)(xtal*143-2);i++) 
         ; 
   }   
}


void LCD12864_Char_Set(byte y, byte x, byte *p) 
{ 
	if(y == 0)
	{
		W_1byte(0,0,(0x80+x)); 
	}
	
	if(y == 1)
	{
		W_1byte(0,0,(0x90+x));
	}
	
	if(y == 2)
	{
		W_1byte(0,0,(0x88+x));
	}
	
	if(y == 3)
	{
		W_1byte(0,0,(0x98+x));
	}
	
	while(*p != 0)
	{
		W_1byte(0,1,*p++);
	}
}


void Set_Draw(void)
{
	W_1byte(0,0,0x01);   // clear the screen
	Delay(20);     //ÑÓÊ±
	W_1byte(0,0,0x34);   // 8BIT control interface, expanded instruction set, graphics OFF
	Delay(20);     //ÑÓÊ±
}


void Draw_Pic(byte x, byte y, const byte *Draw)
{
	byte i, j, temp_x, temp_y;
	temp_x = x;
	temp_y = y;
	temp_x |= 0x80;
	temp_y |= 0x80;
	
	for(i=0;i<32;i++ )
	{
		W_1byte(0,0,temp_y++);  // set the drawing area of ??the Y address coordinates
		W_1byte(0,0,temp_x);  // set the drawing area coordinates of the X address
		for(j=0;j<16;j++)
		{
			W_1byte(0,1,*Draw);
			Draw++;
		}
	}

	temp_x = 0x88;
	temp_y = 0x80;
	j = 0;

	for(;i<64;i++ )
	{
		W_1byte(0,0,temp_y++);  // set the drawing area of ??the Y address coordinates
		W_1byte(0,0,temp_x);   // set the drawing area coordinates of the X address
		for(j=0;j<16;j++)
		{
			W_1byte(0,1,*Draw);
			Draw++;
		}
	}
 
}


void Lcd_flash(u16 delay_t, byte times)
{
	byte j;
	
	for(j=0;j<times;j++)
	{
		W_1byte(0,0,0x08);  // turn off the display
		Delay(delay_t);
		
		W_1byte(0,0,0x0c);  // open display
		Delay(delay_t);
	}
}

/*
//========= LCD internal address =============
// Line1 80H 81H 82H 83H 84H 85H 86H 87H
// Line2 90H 91H 92H 93H 94H 95H 96H 97H
// Line3 88H 89H 8AH 8BH 8CH 8DH 8EH 8FH
// Line4 98H 99H 9AH 9BH 9CH 9DH 9EH 9FH
// Because the LCD of defects, so the display will move the ugly
*/  
void Move(byte step,byte dirction,u16 time)
{
	byte i;
	for(i=0;i<step;i++)       // move steps
	{
		 W_1byte(0,0,dirction);      // Text direction of movement
		 Delay(time);             // move time control
	}
}

void bsp_lcd12864_gpio_init(void)
{

	sbi(LCD12864_DDR, LCD12864_RS_PIN_NO);
	sbi(LCD12864_DDR, LCD12864_RW_PIN_NO);
	sbi(LCD12864_DDR, LCD12864_EN_PIN_NO);
	sbi(LCD12864_DDR, LCD12864_PSB_PIN_NO);

	sbi(LCD12864_PORT, LCD12864_RS_PIN_NO);
	sbi(LCD12864_PORT, LCD12864_RW_PIN_NO);
	sbi(LCD12864_PORT, LCD12864_EN_PIN_NO);
	
	cbi(LCD12864_PORT, LCD12864_PSB_PIN_NO);	

	LCD12864_DATA_DDR |= 0xFF;

 }

void bsp_lcd12864_init(void)
{
	//LCD12864_DDR |= _BV(LCD12864_PSB_PIN_NO);
	//LCD12864_PORT &= ~(_BV(LCD12864_PSB_PIN_NO));
	
	Clr_CS();
	Clr_SID();
	Clr_SCLK();
	
	//W_1byte(0,0,0x01);   // clear the screen
	
	LCD_Init0();
	Delay(1000);
	LCD_Init1();  // key, otherwise the LCD power-on re-starting will not be displayed
	
	//Delay(2000);
}

