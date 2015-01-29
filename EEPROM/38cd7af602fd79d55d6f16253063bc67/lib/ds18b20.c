
#include "hw_config.h"
#include "ds18b20.h"



/*******************************************
Function name: ds18b20_init
Function: Reset DS18B20
Parameters: None
Return Value: None
********************************************/
void ds18b20_init(void)
{
	DS18B20_DDR|=(1<<DS18B20_PIN_NO);			// configure output
	DS18B20_PORT&=~(1<<DS18B20_PIN_NO);			// delay_us
	delay_us(600*2);
	DS18B20_PORT|=(1<<DS18B20_PIN_NO);			// release bus
	delay_us(60*2);
	DS18B20_DDR&=~(1<<DS18B20_PIN_NO);			// configured for input
	while((DS18B20_PIN&(1<<DS18B20_PIN_NO)));	// wait down DS18B20
	while(!(DS18B20_PIN&(1<<DS18B20_PIN_NO))); // wait for the release of the bus DS18B20
}

/*******************************************
Function name: ds18b20_readB
Function: read a byte of data
Parameters: None
Return Value: retd - a byte of data returned
********************************************/
byte ds18b20_readB(void)
{
	byte i,retd=0;
	
	for(i=0;i<8;i++)	 			// bit count
	{
		retd>>=1;						// right, ready to accept new data bits
		DS18B20_DDR|=(1<<DS18B20_PIN_NO);			// configure output
		DS18B20_PORT&=~(1<<DS18B20_PIN_NO);			// down, start reading data bits
		DS18B20_PORT|=(1<<DS18B20_PIN_NO);			// release bus
		delay_us(5*2);
		DS18B20_DDR&=~(1<<DS18B20_PIN_NO);			// configured as inputs, starts reading the data bits
		
		if(DS18B20_PIN&(1<<DS18B20_PIN_NO))			// This bit is high
		{
			retd|=0x80;					// this location is high on
		}
			delay_us(50*2);					// Wait 50 microseconds
	}
	return retd;					// will return one byte read
	
}

/*******************************************
Function name: B20_writeB
Function: write a byte of data
Parameters: wrd - data to be written
Return Value: None
********************************************/
void ds18b20_writeB(byte wrd)
{
	byte i;
	for(i=0;i<8;i++)	  	        // bit count
	{
		DS18B20_DDR|=(1<<DS18B20_PIN_NO);			// configure output
		DS18B20_PORT&=~(1<<DS18B20_PIN_NO);			// down, start writing data bits
		delay_us(1*2);
		
		if(wrd&0x01)					// this bit is high
		{
			DS18B20_PORT|=(1<<DS18B20_PIN_NO);			// is a single bus will be pulled high
		}
		else
		{
			DS18B20_PORT&=~(1<<DS18B20_PIN_NO);		// is a low-down will be a single bus
		}
		
		delay_us(50*2);
		DS18B20_PORT|=(1<<DS18B20_PIN_NO); // release bus
		wrd>>=1;						// right, to write the new data bit in preparation
	}
	delay_us(50);
}

u16 read_ds18b20_temperature(void)
{
	byte templ,temph;
	u16 tempcount;
	
	ds18b20_init();	      // initialize, initialize each write command from the beginning
	ds18b20_writeB(0xcc); 	  // skip ROM
	ds18b20_writeB(0x44); 	  // start temperature conversion
	ds18b20_init();	   	  // initialize each write command from the beginning
	ds18b20_writeB(0xcc); 	  // skip ROM
	ds18b20_writeB(0xbe); 	  // read register
	templ=ds18b20_readB();	  // read temperature low byte
	temph=ds18b20_readB();	  // read temperature high byte
	tempcount=(temph<<8)|templ; // calculate the specific temperature
	
	return(tempcount);
} 


void bsp_ds18b20_gpio_init(void)
{ 
	sbi(DS18B20_DDR, DS18B20_PIN_NO);
	sbi(DS18B20_PORT, DS18B20_PIN_NO);
}


