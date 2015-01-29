
#include "hw_config.h"
#include "timer.h"
#include "timer80.h"



void timer80_rtc_enable(void)
{
	sbi(ASSR, AS0);
}

void timer80_rtc_disable(void)
{
	cbi(ASSR, AS0);
}

void timer80_interrupt_oc_enable(void)
{
	sbi(TIMSK, OCIE0);
}

void timer80_interrupt_oc_disable(void)
{
	cbi(TIMSK, OCIE0);
}

void timer80_interrupt_ov_enable(void)
{
	sbi(TIMSK, TOIE0);
}

void timer80_interrupt_ov_disable(void)
{
	cbi(TIMSK, TOIE0);
}

void timer80_interrupt_ovf_clear(void)
{
	cbi(TIFR, TOV0);
}

void timer80_interrupt_ocf_clear(void)
{
	cbi(TIFR, OCF0);
}

void timer80_init(byte a_WaveFormMode, byte a_ComOutMode, byte a_Clk)
{
	/*-------------------------------------------------------------------
	   8-bit Timer/Counter Register Description
	   TCCR0 (Timer/Counter Control Register define)
	=====================================================================
	Bit 	7 	6 	5 	4 	3 	2 	1 	0
	FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00 TCCR0
	Read/Write W R/W R/W R/W R/W R/W R/W R/W
	Initial Value 0 0 0 0 0 0 0 0
	-------------------------------------------------------------------*/

	// Waveform Generation Mode Bit
	switch(a_WaveFormMode)
	{
		case WAVE_NOR:	 // Normal 
						cbi(TCCR0,WGM00);
						cbi(TCCR0,WGM01);	
						break;
							
		case WAVE_PWM: // PWM,Phase Correct
						sbi(TCCR0,WGM00);
						cbi(TCCR0,WGM01);									
						break;

		case WAVE_CTC:	// CTC
						cbi(TCCR0,WGM00);
						sbi(TCCR0,WGM01);							
						break;
	
		case WAVE_FPWM:	// Fast PWM
						sbi(TCCR0,WGM00);
						sbi(TCCR0,WGM01);	
	                    break;
}

	//Compare Output Mode(Normal, CTC)
	switch(a_ComOutMode)
{
		case OC_NORMAL:	 // Normal port operation, OC0 disconnected.
						cbi(TCCR0,COM00);
						cbi(TCCR0,COM01);	
						break;
	
		case OC_TOG: // Toggle OC0 on compare match
						sbi(TCCR0,COM00);
						cbi(TCCR0,COM01);									
						break;
	
		case OC_CLE:	// Clear OC0 on compare match
						cbi(TCCR0,COM00);
						sbi(TCCR0,COM01);							
						break;

		case OC_SET:	// Set OC0 on compare match
						sbi(TCCR0,COM00);
						sbi(TCCR0,COM01);	
	                    break;
	}
	
    // CS02:0: Clock Select
	switch(a_Clk)
	{
		case CLK_STOP:	 // No clock source (Timer/Counter stopped).
						cbi(TCCR0,CS00);
						cbi(TCCR0,CS01);
						cbi(TCCR0,CS02);
						break;

		case CLK_NO:    // clkI/O/(No prescaling)
						sbi(TCCR0,CS00);
						cbi(TCCR0,CS01);
						cbi(TCCR0,CS02);									
						break;

		case CLK_8:	    // clkI/O/8 (From prescaler)
						cbi(TCCR0,CS00);
						sbi(TCCR0,CS01);
						cbi(TCCR0,CS02);							
						break;
	
		case CLK_64:	// clkI/O/64 (From prescaler)
						sbi(TCCR0,CS00);
						sbi(TCCR0,CS01);
						cbi(TCCR0,CS02);	
	                    break;
	    case CLK_256:	// clkI/O/256 (From prescaler)
						cbi(TCCR0,CS00);
						cbi(TCCR0,CS01);
						sbi(TCCR0,CS02);	
						break;

		case CLK_1024:  // clkI/O/1024 (From prescaler)
						sbi(TCCR0,CS00);
						cbi(TCCR0,CS01);
						sbi(TCCR0,CS02);									
						break;
	
		case CLK_EXT_F:	// External clock source on T0 pin. Clock on falling edge.
						cbi(TCCR0,CS00);
						sbi(TCCR0,CS01);
						sbi(TCCR0,CS02);							
						break;
	
		case CLK_EXT_R:	// External clock source on T0 pin. Clock on rising edge.
						sbi(TCCR0,CS00);
						sbi(TCCR0,CS01);
						sbi(TCCR0,CS02);	
	                    break;
	}

}
