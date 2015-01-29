
#include "hw_config.h"
#include "iic.h"

// #include<macros.h>

// Initialization
void IIC_init()
{
    // PORTD&=~0x80;
    TWBR=0x01 ;  // rate = 16M / (16 +2 * 16) = 33.3k
    TWSR=0x01 ;  // divisor = 4
}


// Start signal
void IIC_start()
{
    TWCR=0xa4 ;
    while(!(TWCR&0x80)); 
}


// Write data
void IIC_wrdata(byte IIC_data)
{
    TWDR=(IIC_data);
    TWCR=0x84 ;
    while(!(TWCR&0x80));
}


// Read data noack
byte IIC_redata()
{
    byte IIC_data ;
    TWCR=0x84 ;
    while(!(TWCR&0x80));
    IIC_data=TWDR ;
    return(IIC_data);
}

// Read data ack
byte IIC_redataack()
{
    byte IIC_data ;
    TWCR=0xc4 ;
    while(!(TWCR&0x80));
    IIC_data=TWDR ;
    return(IIC_data);
}



// Stop signal
void IIC_stop()
{
    TWCR=0x94 ;
}

// IIC write byte subroutine
void IIC_wrbyte(byte IIC_data,byte IIC_add)
{
    do 
    {
        IIC_start();
        IIC_wrdata(0xa0);
    }
    while((TWSR&0xf8)!=0x18);     // determine whether the bus can operate
    
    IIC_wrdata(IIC_add);
    IIC_wrdata(IIC_data);
    IIC_stop();
}

// IIC of the page to write a subroutine
// Parameter 1: array of pointers to be written
// Parameter 2: writing the first address
// Parameter 3: The number of array elementsÔªÊý
void IIC_wrpage(byte *IIC_data,byte IIC_add,byte IIC_nub)
{
    byte i;
    do 
    {
        IIC_start();
        IIC_wrdata(0xa0);
    }
    while((TWSR&0xf8)!=0x18);
    // Determine whether the bus can operate
    IIC_wrdata(IIC_add);
    for(i=0;i<IIC_nub;i++)
    {
        IIC_wrdata(*IIC_data++);
    }
    IIC_stop();
}

// IIC read a byte subroutine
byte IIC_rebyte(byte IIC_add)
{
	byte IIC_data ;
	do 
	{
		IIC_start();
		IIC_wrdata(0xa0);
	} while((TWSR&0xf8)!=0x18);
	
	// Determine whether the bus can operate
	IIC_wrdata(IIC_add);
	IIC_start();
	IIC_wrdata(0xa1);
	IIC_data=IIC_redata();
	IIC_stop();
	
	return(IIC_data);
}


// IIC continuous read subroutine
// Parameter 1:16 bit address
// Parameter 2: number of bytes read Note: <= 64
// Read out the data can only be obtained from the global array variable
void IIC_rese(byte *IIC_data,byte IIC_add,byte IIC_nub)
{
    byte i;
    do 
    {
        IIC_start();
        IIC_wrdata(0xa0);
    }
    while((TWSR&0xf8)!=0x18);
    // Determine whether the bus can operate
    IIC_wrdata(IIC_add);
    IIC_start();
    IIC_wrdata(0xa1);
    for(i=0;i<(IIC_nub-1);i++)              // a small circle, leaving the last issue no ack signal
    {
        *IIC_data=IIC_redataack();
		IIC_data++;
    }
    *IIC_data=IIC_redata();                 // last byte sent no ack signal
    IIC_stop();
}







