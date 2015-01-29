
#include "hw_config.h"
#include "at24c02.h"
#include "iic.h"

void bsp_at24c02_gpio_init() 
{
	sbi(IIC_SCL_DDR, IIC_SCL_PIN_NO);
	sbi(IIC_SDA_DDR, IIC_SDA_PIN_NO);

	sbi(IIC_SCL_PORT, IIC_SCL_PIN_NO);
	sbi(IIC_SDA_PORT, IIC_SDA_PIN_NO);	
}

void bsp_at24c02_init() 
{
	IIC_init();
}

