

#include "hw_config.h"
#include "lcd1602.h"


void bsp_lcd1602_gpio_init(void)
{
	_delay_ms(300);				// wait for the internal reset 
#if 1
	sbi(LCD1602_DDR, LCD1602_RS_PIN_NO);
	sbi(LCD1602_DDR, LCD1602_RW_PIN_NO);
	sbi(LCD1602_DDR, LCD1602_EN_PIN_NO);

	//sbi(LCD1602_PORT, LCD1602_RS_PIN_NO);
	//sbi(LCD1602_PORT, LCD1602_RW_PIN_NO);
	//sbi(LCD1602_PORT, LCD1602_EN_PIN_NO);

	// LCDa_CTRL_DDR |= _BV(LCDa_RS)|_BV(LCDa_RW)|_BV(LCDa_E);
	LCDa_DATA_DDR |= 0xFF;
#endif
#if 0
	LCDa_CTRL_DDR |= BIT(LCDa_RS)|BIT(LCDa_RW)|BIT(LCDa_E);
	LCDa_DATA_DDR |= 0xFF;
#endif	
 }

void bsp_lcd1602_init(void)
{

	
	LCD1602_sendbyte(iCmd, LCDa_FUNCTION);	// function mode setting 
	while(LCD1602_readBF());
	LCD1602_sendbyte(iCmd, LCDa_ON);		// open the show 
	while(LCD1602_readBF());
	LCD1602_clear();						// clear the screen 
	while(LCD1602_readBF());
	LCD1602_sendbyte(iCmd, LCDa_ENTRY);	// input mode setting 
}




/******************************************* 
Function name: LCD1602_readbyte 
Function: From 1602 to read one byte of data or instructions 
Parameters: DatCmd - when the data for the iDat, when instructions for the iCmd 
Return Value: dByte - read back the data or instruction 
********************************************/ 
byte LCD1602_readbyte(byte DatCmd)
{
 	byte dByte;
	if (DatCmd == iCmd)		 // Command operation 
		LCDa_CLR_RS;
	else
		LCDa_SET_RS;
		
	LCDa_SET_RW;	   	  	 // Read
	LCDa_SET_E;
	LCDa_DATA_DDR=0x00;	 // data bus is defined as the input 
	dByte=LCDa_DI;			 // read data or instructions 
	_delay_ms(2);				 // timing adjustment 
	LCDa_CLR_E;	
	LCDa_DATA_DDR|=0xff;	 // restore the output data bus 
	return dByte;
}

/******************************************* 
Function name: LCD1602_sendbyte 
Function: 1602 to write a byte of data or instructions 
Parameters: DatCmd - when the data for the iDat, when instructions for the iCmd 
dByte - 1602 for the write data or instructions 
Return Value: None 
********************************************/ 
void LCD1602_sendbyte(byte DatCmd, byte dByte)
{
	if (DatCmd == iCmd)		// Command operation 
		LCDa_CLR_RS;
	else
		LCDa_SET_RS;
		
	LCDa_CLR_RW;			// write
	LCDa_SET_E;
	LCDa_DO = dByte;		// write data
	_delay_ms(2);
	LCDa_CLR_E;	
}

/******************************************* 
Function name: LCD1602_sendstr 
Function: 1602 to the ranks assigned to write a string 
Parameters: Row - the specified line 
Col - the specified column 
ptString - string pointer 
Return Value: None 
********************************************/ 
void LCD1602_Char_Set(byte Row, byte Col, byte *ptString)
{
	switch (Row)
	{
		case 2:
			LCD1602_sendbyte(iCmd, LCDa_L2 + Col); break;	// write line 2 of the specified column 
		default:
			LCD1602_sendbyte(iCmd, LCDa_L1 + Col); break;	// write the first line of the specified column 
	}
	while((*ptString)!='\0')		 // string is not the end of 
	{
		LCD1602_sendbyte(iDat, *ptString++);
	}
}
/******************************************* 
Function name: LCD1602_clear 
Function: clear-screen LCD 1602 
Parameters: None 
Return Value: None 
********************************************/ 
void LCD1602_clear(void)
{
	LCD1602_sendbyte(iCmd,LCDa_CLS);
	_delay_ms(4); // clear the screen after the command is written, 2ms delay is necessary!!! 
}
/******************************************* 
Function name: LCD1602_readBF 
Function: clear-screen LCD 1602 
Parameters: None 
Return Value: busy - busy is 1, 0 can receive instruction 
********************************************/ 
byte LCD1602_readBF(void)
{	  
	byte busy;
	busy=LCD1602_readbyte(iCmd);		// read back to the BF flag and address 
	if(busy&0x80)						// Busy
		busy=1;
	else	   							// not busy, you can write 
		busy=0;
	return busy;
}

/******************************************* 
Function name: LCD1602_wrCGRAM 
Function: Write data to CGRAM 
Parameters: ptCGRAM - CGRAM data pointer 
Return Value: None 
********************************************/ 
void LCD1602_wrCGRAM(const byte *ptCGRAM)
{
	byte i;
	LCD1602_sendbyte(iCmd, LCDa_CGRAM_ADDR);  // write the first address of CGRAM 
	for (i = 0; i < LCDa_CGMAX; i++)		  // write the contents of 64 bytes of CGRAM 
	{
		LCD1602_sendbyte(iDat,ptCGRAM[i]);
	}
}
/******************************************* 
Function name: LCD1602_disCGRAM 
Function: display CGRAM contents of 64 bytes written on two lines of 32 bytes 
Parameters: None 
Return Value: None 
********************************************/ 
void LCD1602_disCGRAM(byte Row,byte Col)
{
	byte i;
	switch (Row)
	{
		case 2:
			LCD1602_sendbyte(iCmd, LCDa_L2 + Col); break;	// write line 2 of the specified column 
		default:
			LCD1602_sendbyte(iCmd, LCDa_L1 + Col); break;	//  write the first line of the specified column 
	}
	for (i = 0;i <4;i++)   // display the contents of the first 32 bytes 
	{	 	
		LCD1602_sendbyte(iDat, i);		
	}
}


