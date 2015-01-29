
#include "hw_config.h"
#include "7segment.h"

// 케소드 공통형
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, off
// uchar LED_SEG[] ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77, 0x7C, 0x39, 0x5E, 0x78, 0x71, 0x00}; 
// uchar LED_BIT[] ={0b11101111,0b11011111,0b10111111,0b01111111};   

// 아노드 공통형
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f, off
u8 LED_SEG[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E, 0xFF}; 
u8 LED_BIT[] ={0b00011111,0b00101111,0b01001111,0b10001111};   

void bsp_fnd_gpio_init(void)
{

	sbi(FND1_DDR, FND1_PIN_NO);
	sbi(FND2_DDR, FND2_PIN_NO);	
	sbi(FND3_DDR, FND3_PIN_NO);
	sbi(FND4_DDR, FND4_PIN_NO);	


	// 초기값을 0로 하면 Off
	cbi(FND1_PORT, FND1_PIN_NO);
	cbi(FND2_PORT, FND2_PIN_NO);	
	cbi(FND3_PORT, FND3_PIN_NO);
	cbi(FND4_PORT, FND4_PIN_NO);

	// fnd data line initialize
	FND_DATA_DDR = 0xff;
	// 케소드에서는 0XFF 값이다.
	FND_DATA_PORT = 0x00;
}

void fnd_puts(u16 num_data, u16 delay_ms)
{
	u8 i;

	u16 fnd_data[] = {0,0,0,0};	
	
	fnd_data[0] = num_data/1000;
	fnd_data[1] = (num_data%1000)/100; 
	fnd_data[2] = (num_data%100)/10; 
	fnd_data[3] = num_data%10;

	for(i=0;i<4;i++) 
	{
		PORTA = LED_SEG[fnd_data[i]];
		PORTD = LED_BIT[i];
		_delay_ms(delay_ms);
	}
}		

void fnd_puts_temperature(u16 num_data, u16 delay_ms)
{
	u8 i;
	u16 fnd_data[3];	

	// usart0_format_puts("num_data=%d\r\n", num_data);

      fnd_data[0] = (num_data % 1000) / 100; 	// convert the actual temperature value into the display array BCD code
      fnd_data[1] = (num_data % 100) / 10;
      fnd_data[2] = num_data % 10;	
	
	for(i=0;i<4;i++) 
	{ 
		if(i==1)
		{  
			// 케소드 공통형
			// PORTA = LED_SEG[fnd_data[1]] | 0x80; // decimal point LED display data
			PORTA = LED_SEG[fnd_data[i]] & 0x7f;  // decimal point LED display data
			PORTD = LED_BIT[i]; // digital display allows			
		}
		else if(i==3)
		{  
			// 케소드 공통형
			// PORTA = 0x39; // digital display "C"
			PORTA = 0xc6; // digital display "C"
			PORTD = LED_BIT[i]; // digital display allows
		}
		else
		{
			PORTA = LED_SEG[fnd_data[i]]; // digital display data
			PORTD = LED_BIT[i]; // digital display allows
		} 

		_delay_ms(delay_ms); 
		
	} 

}

void fnd_puts_voltage(u16 num_data, u16 delay_ms)
{
	u8 i;

	u16 fnd_data[] = {0,0,0,0};	
	
	fnd_data[0] = num_data/1000;
	fnd_data[1] = (num_data%1000)/100; 
	fnd_data[2] = (num_data%100)/10; 
	fnd_data[3] = num_data%10;

	for(i=0;i<4;i++) 
	{
		if(i==2)
		{
			// 케소드 공통형
			// PORTA = LED_SEG[fnd_data[1]] | 0x80; // decimal point LED display data
			PORTA = LED_SEG[fnd_data[i]] & 0x7f;  // decimal point LED display data
			PORTD = LED_BIT[i]; // digital display allows	
		}
		else
		{
			PORTA = LED_SEG[fnd_data[i]];
			PORTD = LED_BIT[i];		
		}
		_delay_ms(delay_ms);
	}

}

