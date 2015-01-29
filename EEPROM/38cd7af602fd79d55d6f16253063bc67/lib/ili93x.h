
#ifndef __ILI93X_H
#define __ILI93X_H

#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304 


#define DATA_LCD_DDR  DDRA
#define DATA_LCD_PORT PORTA
#define DATA_LCD_PIN  PINA

#define DATA_INPUT()   DATA_LCD_DDR = 0x00;
#define DATA_OUPUT()   DATA_LCD_DDR = 0xFF;

#define LCD_CS_DDR  DDRG
#define LCD_CS_PORT PORTG
#define LCD_CS_PIN  PING
#define LCD_CS_BIT  PG0

#define LCD_RS_DDR  DDRG
#define LCD_RS_PORT PORTG
#define LCD_RS_PIN  PING
#define LCD_RS_BIT  PG1

#define LCD_RD_DDR  DDRG
#define LCD_RD_PORT PORTG
#define LCD_RD_PIN  PING
#define LCD_RD_BIT  PG2

#define LCD_WR_DDR  DDRE
#define LCD_WR_PORT PORTE
#define LCD_WR_PIN  PINE
#define LCD_WR_BIT  PE6

#define LCD_RST_DDR  DDRE
#define LCD_RST_PORT PORTE
#define LCD_RST_PIN  PINE
#define LCD_RST_BIT  PE2


#define LCD_BL_DDR  DDRG
#define LCD_BL_PORT PORTG
#define LCD_BL_PIN  PING
#define LCD_BL_BIT  PG3

#define LCD_CS_H() LCD_CS_PORT |= 1<<LCD_CS_BIT
#define LCD_CS_L() LCD_CS_PORT &= ~(1<<LCD_CS_BIT)

#define LCD_RS_H() LCD_RS_PORT |= 1<<LCD_RS_BIT
#define LCD_RS_L() LCD_RS_PORT &= ~(1<<LCD_RS_BIT)

#define LCD_WR_H() LCD_WR_PORT |= 1<<LCD_WR_BIT//
#define LCD_WR_L() LCD_WR_PORT &= ~(1<<LCD_WR_BIT)//

#define LCD_RD_H() LCD_RD_PORT |= 1<<LCD_RD_BIT
#define LCD_RD_L() LCD_RD_PORT &= ~(1<<LCD_RD_BIT)

#define LCD_RST_H() LCD_RST_PORT |= 1<<LCD_RST_BIT
#define LCD_RST_L() LCD_RST_PORT &= ~(1<<LCD_RST_BIT)

#define LCD_BL_H() LCD_BL_PORT |= 1<<LCD_BL_BIT
#define LCD_BL_L() LCD_BL_PORT &= ~(1<<LCD_BL_BIT)

#if 0
#define LCD_PORT_INI(){ LCD_BL_DDR |= 1<<LCD_BL_BIT;\
						LCD_CS_DDR |= 1<<LCD_CS_BIT;\
						LCD_RS_DDR |= 1<<LCD_RS_BIT;\
						LCD_WR_DDR |= 1<<LCD_WR_BIT;\
						LCD_RD_DDR |= 1<<LCD_RD_BIT;/*\*/
						/*LCD_RST_DDR|= 1<<LCD_RST_BIT;\*/
					   }
#endif

#define LCD_PORT_INI(){ LCD_BL_DDR |= 1<<LCD_BL_BIT;\
						LCD_CS_DDR |= 1<<LCD_CS_BIT;\
						LCD_RS_DDR |= 1<<LCD_RS_BIT;\
						LCD_WR_DDR |= 1<<LCD_WR_BIT;\
						LCD_RD_DDR |= 1<<LCD_RD_BIT;\
						LCD_RST_DDR |= 1<<LCD_RST_BIT;\
					   }
	

#define ID_AM     110

// Pen color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
//GUI

#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458 

// for PANEL
#define LIGHTGREEN     	 0X841F
//#define LIGHTGRAY        0XEF5B
#define LGRAY 			 0XC618

#define LGRAYBLUE        0XA651 // light gray blue (middle layer color)
#define LBBLUE           0X2B12 // light brown blue (select the entry of anti-color)	

// Define the size of LCD
#define LCD_W 240
#define LCD_H 320

// 9320/9325 LCD register
#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R229           0xE5	

// extern u16 BACK_COLOR, POINT_COLOR ;  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear2 (u16 Color, u16 x, u16 y);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u8 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y, u16 pen_color);
// u16 LCD_ReadPoint(u16 x,u16 y);
void Draw_Circle(u8 x0,u16 y0,u8 r, u16 pen_color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 pen_color);
void LCD_DrawRectangle(u8 x1, u16 y1, u8 x2, u16 y2, u16 pen_color);		   
void LCD_Fill(u8 xsta,u16 ysta,u8 xend,u16 yend,u16 color);
void LCD_ShowChar (u8 x, u16 y, u8 num, u8 size, u8 mode, u16 back_color, u16 pen_color);
void LCD_ShowNum(u8 x,u16 y,u32 num,u8 len,u8 size, u16 back_color, u16 pen_color);
void LCD_Show2Num(u8 x,u16 y,u16 num,u8 len,u8 size,u8 mode, u16 back_color, u16 pen_color);
void LCD_ShowString(u8 x,u16 y,const u8 *p, u16 back_color, u16 pen_color);		 // display a string of 16 fonts

void LCD_WR_DATA16(u16 data);
void LCD_WR_REG16(u16 data);

void LCD_WR_REG (u16 data);
void LCD_WR_DATA(u16 data);

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);	
void Test(void);

#endif
