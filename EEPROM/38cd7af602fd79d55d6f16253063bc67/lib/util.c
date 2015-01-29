
#include "hw_config.h"
#include "util.h"

void delay_us(u16 us)		  
{
	u16 i;
	for( i=0;i<us;i++)
		asm("nop"); 
}

#ifndef USE_AVR_STUDIO
/* This delay is very rough - don't use it for precise delays */
void _delay_ms(unsigned int millisec)
{
	u16 i;
    
	while (millisec--)
 		for (i=0; i<625; i++) nop(); //asm volatile ("nop"::);
}
#endif

byte crc8(byte *ptr, byte len) 
{ 
	unsigned char i; 
	unsigned char crc=0; 

	while(len--!=0) 
	{ 
		for(i=1; i!=0; i*=2) 
		{ 
			if((crc&1)!=0) 
			{
				crc/=2; crc^=0x8C;
			} 
			else 
			{
				crc/=2; 
			}
			if((*ptr&i)!=0) 
				crc^=0x8C; 
		} 
		ptr++; 
	} 
	return(crc); 
}

/*******************************************
Function name: bcd2ascii
Function: to convert the compressed BCD code ascii code
Parameters: BCD - BCD to be converted code compression
ptasc - converted pointer to an array of ASCII code
Return Value: None
********************************************/
void bcd2ascii(byte BCD,byte ptasc[])
{ 	
	ptasc[0]= (BCD>>4) | 0x30;	 // convert ten
	ptasc[1] = BCD & 0x0F | 0x30;  // convert bits
}


void __ftoa(float f, unsigned char *buf, char DecPoint)

{
   unsigned int rem;
   unsigned char *s,length=0;
   int i;

   i = (int)((float)f*10);

   s = buf;
   if (i == 0)                //print 0.0 with null termination here
   {
      *s++ = '0';
      *s++ = '.';
      *s++ = '0'; 
      *s=0;                   //null terminate the string
   } 
   else 
   {   
      if (i < 0) 
      {
         *buf++ = '-';
         s = buf;
         i = -i;
      }
      //while-loop to "decode" the long integer to ASCII by append '0', string in reverse manner
      //If it is an integer of 124 -> string = {'4', '2', '1'}
      while (i) 
      {
         ++length;
         rem = i % 10;
         *s++ = rem + '0';
         i /= 10;
      }
      //reverse the string in this for-loop, string became {'1', '2', '4'} after this for-loop
      for(rem=0; ((unsigned char)rem)<length/2; rem++) 
      {
         *(buf+length) = *(buf+((unsigned char)rem));
         *(buf+((unsigned char)rem)) = *(buf+(length-((unsigned char)rem)-1));
         *(buf+(length-((unsigned char)rem)-1)) = *(buf+length);
      }

      /* Take care of the special case of 0.x if length ==1*/   
      if(length==1) 
      {
         *(buf+2) = *buf;
         *buf = '0';
         *(buf+1) = '.';

         *(s+2)=0;                //null terminate
      } 
      else 
      {
            *(buf+length) = *(buf+length-1); ///== cai nay MOT dec point ==///
            *(buf+length-1)='.';
            *(s+1)=0;                   //null terminate
      }
   }
}



