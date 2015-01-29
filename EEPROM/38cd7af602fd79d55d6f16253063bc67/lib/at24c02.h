


#ifndef __AT24C02_H
#define __AT24C02_H

// scl
#define IIC_SCL_DDR			DDRD
#define IIC_SCL_PORT			PORTD
#define IIC_SCL_PIN_NO		PD0

// sda
#define IIC_SDA_DDR			DDRD
#define IIC_SDA_PORT			PORTD
#define IIC_SDA_PIN_NO		PD1

void bsp_at24c02_gpio_init();
void bsp_at24c02_init();

#endif
