
#ifndef _AVR_CRC16_H_
#define _AVR_CRC16_H_

void IIC_init();
void IIC_start();
void IIC_wrdata(byte IIC_data);
byte IIC_redata();
byte IIC_redataack();
void IIC_stop();
void IIC_wrbyte(byte IIC_data,byte IIC_add);
void IIC_wrpage(byte *IIC_data,byte IIC_add,byte IIC_nub);
byte IIC_rebyte(byte IIC_add);
void IIC_rese(byte *IIC_data,byte IIC_add,byte IIC_nub);

#endif