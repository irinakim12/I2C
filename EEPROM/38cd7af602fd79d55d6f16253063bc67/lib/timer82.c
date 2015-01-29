
#include "hw_config.h"
#include "timer.h"
#include "timer82.h"
#include "uart.h"

#ifndef USE_AVR_STUDIO
#pragma interrupt_handler TIMER2_OVF_vect:iv_TIMER2_OVF
#endif


timer2_register_function timer2_register_fn = NULL;

void timer82_rtc_enable(void)
{
	sbi(ASSR, AS2);
}

void timer82_rtc_disable(void)
{
	cbi(ASSR, AS2);
}

void timer82_interrupt_oc_enable(void)
{
	sbi(TIMSK, OCIE2);
}

void timer82_interrupt_oc_disable(void)
{
	cbi(TIMSK, OCIE2);
}

void timer82_interrupt_ov_enable(void)
{
	sbi(TIMSK, TOIE2);
}

void timer82_interrupt_ov_disable(void)
{
	cbi(TIMSK, TOIE2);
}

void timer82_interrupt_ovf_clear(void)
{
	cbi(TIFR, TOV2);
}

void timer82_interrupt_ocf_clear(void)
{
	cbi(TIFR, OCF2);
}


void timer82_timer_stop()
{
	cbi(TCCR2,CS20);
	cbi(TCCR2,CS21);
	cbi(TCCR2,CS22);
}


u8 timer82_init(u32 dwFOSC, u16 tick_time_ms, byte a_WaveFormMode, byte a_ComOutMode, byte a_byteDiv)
{
	u32 reload_cnt = 0;

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
						cbi(TCCR2,WGM20);
						cbi(TCCR2,WGM21);	
						break;
							
		case WAVE_PWM: // PWM,Phase Correct
						sbi(TCCR2,WGM20);
						cbi(TCCR2,WGM21);									
						break;

		case WAVE_CTC:	// CTC
						cbi(TCCR2,WGM20);
						sbi(TCCR2,WGM21);							
						break;
	
		case WAVE_FPWM:	// Fast PWM
						sbi(TCCR2,WGM20);
						sbi(TCCR2,WGM21);	
	                    break;
}

	//Compare Output Mode(Normal, CTC)
	switch(a_ComOutMode)
{
		case OC_NORMAL:	 // Normal port operation, OC0 disconnected.
						cbi(TCCR2,COM20);
						cbi(TCCR2,COM21);	
						break;
	
		case OC_TOG: // Toggle OC0 on compare match
						sbi(TCCR2,COM20);
						cbi(TCCR2,COM21);									
						break;
	
		case OC_CLE:	// Clear OC0 on compare match
						cbi(TCCR2,COM20);
						sbi(TCCR2,COM21);							
						break;

		case OC_SET:	// Set OC0 on compare match
						sbi(TCCR2,COM20);
						sbi(TCCR2,COM21);	
	                    break;
	}

    // CS02:0: Clock Select
	switch(a_byteDiv)
	{
		case CLK_STOP:	 // No clock source (Timer/Counter stopped).
		{
						cbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						cbi(TCCR2,CS22);						
						break;
		}
		case CLK_NO:    // clkI/O/(No prescaling)
		{
						sbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						cbi(TCCR2,CS22);									
						break;
		}
		case CLK_8:	    // clkI/O/8 (From prescaler)
		{
						cbi(TCCR2,CS20);
						sbi(TCCR2,CS21);
						cbi(TCCR2,CS22);							
						break;
		}
		case CLK_64:	// clkI/O/64 (From prescaler)
		{
						sbi(TCCR2,CS20);
						sbi(TCCR2,CS21);
						cbi(TCCR2,CS22);
	                    break;
		}		
		case CLK_128:	// clkI/O/128 (From prescaler)
		{
						sbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						sbi(TCCR2,CS22);
	                    break;
		}
	    case CLK_256:	// clkI/O/256 (From prescaler)
		{
						cbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						sbi(TCCR2,CS22);	
						break;
		}
		case CLK_1024:  // clkI/O/1024 (From prescaler)
		{
						sbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						sbi(TCCR2,CS22);									
						break;
		}
		case CLK_EXT_F:	// External clock source on T0 pin. Clock on falling edge.
		{
						cbi(TCCR2,CS20);
						sbi(TCCR2,CS21);
						sbi(TCCR2,CS22);							
						break;
		}
		case CLK_EXT_R:	// External clock source on T0 pin. Clock on rising edge.
		{
						sbi(TCCR2,CS20);
						sbi(TCCR2,CS21);
						sbi(TCCR2,CS22);	
	                    break;
		}
		default:		// CLK_NO 로 설정
		{
						sbi(TCCR2,CS20);
						cbi(TCCR2,CS21);
						cbi(TCCR2,CS22);									
						break;
		}
	}

	// 16000000/1024 = 15625  --> 1초에 발생하는 클럭
	// 그러므로 1/15625 = 0.000064 --> 타이머 클럭 1번의 시간은 64usec 이다.
	// TICK_TIME = 0.01 --> 10msec 마다 오버플로어 인터럽트가 발생 하도록 
	// TIMER2가 8비트 타이머 이므로 256-1로 함, 만약 16비트 타이머 이면 65535-1
	// 16000000Hz 크리스탈
	// 1024 --> 분주비
	// (256-1) - ((TICK_TIME)*16000000/1024) = 98.75 --> TIMER2_RELOAD 값
	// 10msec 마다 한번씩 인터럽트가 발생 하도록 한다. --> UP카운트이므로 255(8비트 타이머)-98.75 = 156.25 * 64usec = 10000usec = 10msec

	

	reload_cnt = ((256. - 1.) - ((tick_time_ms/1000.)*(dwFOSC/1024.))) * 1000.; // = 98.75 --> TIMER2_RELOAD 값
	// reload_cnt = ((256. - 1.) - ((10./1000.)*(16000000L/1024.))) * 1000.; // = 98.75 --> TIMER2_RELOAD 값
	// 반올림
	if( reload_cnt % 10000 >= 500 )
		reload_cnt = (reload_cnt + 500)/1000;
	else
		reload_cnt = reload_cnt/1000;

	//usart0_format_puts("ttm=%d, osc=%d\r\n", tick_time_ms, dwFOSC);
	//usart0_format_puts("reload_cnt=%d\r\n", reload_cnt);

	return reload_cnt;
		

}


void register_timer2_function(timer2_register_function fn)
{
	timer2_register_fn = fn;
}

#ifdef USE_AVR_STUDIO
ISR(TIMER2_OVF_vect)
#else
void TIMER2_OVF_vect(void)
#endif
{
	if( timer2_register_fn != NULL )
		timer2_register_fn();
}
