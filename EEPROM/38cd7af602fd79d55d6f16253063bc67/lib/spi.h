


#ifndef __SPI_H
#define __SPI_H

typedef enum
{
	SPI_SPEED_HIGH,
	SPI_SPEED_LOW,
	SPI_SPEED_MAX
} spi_speed_define_type;

#define SPI_PORT				PORTB
#define SPI_DDR				DDRB
#define SPI_PIN				PINB


#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || \
    defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega162__) 

#define SPI_SCK_PIN_NO		PB5
#define SPI_MOSI_PIN_NO		PB3
#define SPI_MISO_PIN_NO		PB4
#define SPI_CS_PIN_NO		PB2

#elif defined(__AVR_ATmega64__)  || defined(__AVR_ATmega128__) 

#define SPI_SCK_PIN_NO		PB1
#define SPI_MOSI_PIN_NO		PB2
#define SPI_MISO_PIN_NO		PB3
#define SPI_CS_PIN_NO		PB0

#else
//
// unsupported type
//
#error "Processor type not supported in spi.h !"
#endif

void bsp_spi_gpio_init();
void bsp_spi_init();
void bsp_set_spi_speed (spi_speed_define_type speed);
u8 bsp_readwritebyte_spi (u8 tx_data);

#endif

