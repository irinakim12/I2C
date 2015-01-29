


#ifndef __DS18B20_H
#define __DS18B20_H

#ifdef USE_DS18B20_MODULE

#define DS18B20_PIN_NO   	PC4
#define DS18B20_PORT 		PORTC
#define DS18B20_PIN  		PINC
#define DS18B20_DDR  		DDRC

#else

#define DS18B20_PIN_NO   	PG4
#define DS18B20_PORT 		PORTG
#define DS18B20_PIN  			PING
#define DS18B20_DDR  		DDRG

#endif

void bsp_ds18b20_gpio_init(void);
void ds18b20_init(void);
byte ds18b20_readB(void);
void ds18b20_writeB(byte wrd);
u16 read_ds18b20_temperature(void);


#endif

