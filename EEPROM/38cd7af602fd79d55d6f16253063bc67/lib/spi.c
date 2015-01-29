

#include "hw_config.h"
#include "spi.h"

void bsp_spi_gpio_init() 
{
	// setup I/O ports 

	SPI_PORT &= ~((1 << SPI_SCK_PIN_NO) | (1 << SPI_MOSI_PIN_NO));	// low bits
	SPI_PORT |= (1 << SPI_MISO_PIN_NO);						// high bits
	SPI_DDR  |= (1<<SPI_SCK_PIN_NO) | (1<<SPI_MOSI_PIN_NO);	// direction

	SPI_PORT |= (1 << SPI_CS_PIN_NO);	// Initial level is high	
	SPI_DDR  |= (1 << SPI_CS_PIN_NO);	// Direction is output	
}

#if 0
void bsp_spi_init() 
{
	// also need to set SS as output
	SPI_DDR |= (1<<SPI_CS_PIN_NO);

	SPCR = (1<<MSTR)|(1<<SPE);	// enable SPI interface
	SPSR = (1<<SPI2X);  // SPI Double speed
}


// SPI speed setting function
void bsp_set_spi_speed (spi_speed_define_type speed)
{
	if( speed == SPI_SPEED_HIGH )
	{
		SPCR =  _BV(SPE)|_BV(MSTR);
		SPCR &= ~_BV(SPR1);	
		SPCR &= ~_BV(SPR0);		
		SPSR |= _BV(SPI2X);	
	}
	else
	{
		if( F_CPU == 16000000UL )
		{
			SPCR =   _BV(SPE)|_BV(MSTR)|_BV(SPR1)|_BV(SPR0);
			SPSR &= ~_BV(SPI2X);	
		}
		else if( F_CPU == 7372800UL )
		{
			SPCR =   _BV(SPE)|_BV(MSTR)|_BV(SPR1);
			SPCR &= ~_BV(SPR0);		
			SPSR &= ~_BV(SPI2X);	
		
		}
		else
		{
			SPCR =   _BV(SPE)|_BV(MSTR)|_BV(SPR1)|_BV(SPR0);
			SPSR &= ~_BV(SPI2X);	
		
		}		
	}
}
#endif

void bsp_spi_init() 
{
	// also need to set SS as output
	SPI_DDR |= (1<<SPI_CS_PIN_NO);

	SPCR = (1<<MSTR)|(1<<SPE);	// enable SPI interface
	SPSR = (1<<SPI2X);  // SPI Double speed
}

// SPI speed setting function
void bsp_set_spi_speed (spi_speed_define_type speed)
{
	if( speed == SPI_SPEED_HIGH )
	{
		SPCR =  _BV(SPE)|_BV(MSTR);
		SPSR |= _BV(SPI2X);	
	}
	else
	{
		SPCR =   _BV(SPE)|_BV(MSTR)|_BV(SPR1)|_BV(SPR0);
		SPSR &= ~_BV(SPI2X);	
	}
}

u8 bsp_readwritebyte_spi (u8 tx_data)
{
	SPDR = tx_data;
	while(!(SPSR & (1<<SPIF)))
	{}
	return SPDR;
}

