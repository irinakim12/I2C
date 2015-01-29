#ifndef __LCD12864_H
#define __LCD12864_H

// ST7920 LCD driver 12864 driver, 3-wire serial mode

/*
Pin Definition: RS (CS )=====> PG0
          RW (SID )====> PG1
          EN (SCLK )===> PG2
          PSB ========> PG3 / / low level for the serial mode
*/

#define LCD12864_DDR			DDRG
#define LCD12864_PORT			PORTG

#define LCD12864_RS_PIN_NO		PG0
#define LCD12864_RW_PIN_NO		PG1
#define LCD12864_EN_PIN_NO		PG2
#define LCD12864_PSB_PIN_NO		PG3

#define LCD12864_DATA_DDR		DDRA

#define xtal    16
#define left    0x18
#define right   0x1c

#define Set_CS()   LCD12864_DDR |= (1<<LCD12864_RS_PIN_NO);LCD12864_PORT |= (1<<LCD12864_RS_PIN_NO)
#define Set_SID()  LCD12864_DDR |= (1<<LCD12864_RW_PIN_NO);LCD12864_PORT |= (1<<LCD12864_RW_PIN_NO)
#define Set_SCLK() LCD12864_DDR |= (1<<LCD12864_EN_PIN_NO);LCD12864_PORT |= (1<<LCD12864_EN_PIN_NO)

#define Clr_CS()   LCD12864_DDR |= (1<<LCD12864_RS_PIN_NO);LCD12864_PORT &=~(1<<LCD12864_RS_PIN_NO)
#define Clr_SID()  LCD12864_DDR |= (1<<LCD12864_RW_PIN_NO);LCD12864_PORT &=~(1<<LCD12864_RW_PIN_NO)
#define Clr_SCLK() LCD12864_DDR |= (1<<LCD12864_EN_PIN_NO);LCD12864_PORT &=~(1<<LCD12864_EN_PIN_NO)

void Delay(u16 ms);
void W_1byte(byte RW, byte RS, byte W_data);
void Write_8bits(u16 W_bits);
void LCD_Init0(void);
void LCD_Init1(void);
void LCD12864_Char_Set(byte y, byte x, byte *p);
void Set_Draw(void);
void Draw_Pic(byte x, byte y, const byte *Draw);
void bsp_lcd12864_gpio_init(void);
void bsp_lcd12864_init(void);
void Lcd_flash(u16 delay_t,byte times);

#endif



