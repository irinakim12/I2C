 
#ifndef __TIMER80_H
#define __TIMER80_H


void timer80_rtc_enable(void);
void timer80_rtc_disable(void);
void timer80_interrupt_oc_enable(void);
void timer80_interrupt_oc_disable(void);
void timer80_interrupt_ov_enable(void);
void timer80_interrupt_ov_disable(void);
void timer80_interrupt_ovf_clear(void);
void timer80_interrupt_ocf_clear(void);
void timer80_Init(byte a_WaveFormMode, byte a_ComOutMode, byte a_Clk);


/*-------------------------------------------------------------------
   ASSR (Asynchronous Status Register define (bits 7-4 reserved )
=====================================================================
  7    6    5     4    3     2    1    0
    - reserved -      AS0 TCN0UB OCR0UB TCR0UB
-------------------------------------------------------------------*/
#define AS0     3		// Asynchronous Timer0/Counter 
#define TCN0UB  2		// TCN0UB: Timer2/Counter Update Busy
#define OCR0UB  1		// OCR0UB: Output Compare Register2 Update Busy
#define TCR0UB  0		// TCR0UB: Timer2/Counter Control Register2 Update Busy


#if 0

/*===================================================================
*
*	Timer Register  Define
*
*==================================================================*/
/*-------------------------------------------------------------------
   8-bit Timer/Counter Register Description
   TCCR0 (Timer/Counter Control Register define)
=====================================================================
  7    6     5     4     3     2    1    0
FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
   0    0     0     0     0     0    0    0    Initial Value
-------------------------------------------------------------------*/
#define FOC0    7		// FOC0: Force Output Compare
#define WGM00   6		// WGM00: Waveform Generation Mode
#define COM01   5		// COM01: Compare Match Output Mode
#define COM00   4		// COM00: Compare Match Output Mode
#define WGM01   3		// WGM01: Waveform Generation Mode
#define CS02    2		// CS02: Clock Select
#define CS01    1		// CS01: Clock Select
#define CS00    0		// CS00: Clock Select

/*--------------------------------------------------------------------
    Waveform Generation Mode Bit Description
----------------------------------------------------------------------
Mode  WGM01   WGM00    Timer/Counter Modeof  TOP   Update of  TOV0 Flag
     (CTC0)  (PWM0)      Operation 					OCR0	   Set-on
======================================================================
 0      0      0           Normal            0xFF   Immediate	MAX
 1      0      1       PWM,Phase Correct	 0xFF	TOP			BOTTOM
 2      1      0           CTC               OCR0   Immediate   MAX
 3      1      1           Fast PWM          0xFF   TOP         MAX
--------------------------------------------------------------------*/
/*---------------------------------------------------------
    Compare Output Mode, non-PWM Mode
-----------------------------------------------------------
COM01  COM00   Description
===========================================================
 0       0       Normal port operation, OC0 disconnected.
 0       0       Toggle OC0 on compare match
 0       1       Clear OC0 on compare match
 0       1       Set OC0 on compare match
---------------------------------------------------------*/
/*---------------------------------------------------------
    Compare Output Mode, Fast PWM Mode
-----------------------------------------------------------
COM01  COM00   Description
===========================================================
 0       0       Normal port operation, OC0 disconnected.
 0       0       Reserved
 0       1       Clear OC0 on compare match, set OC0 at TOP
 0       1       Set OC0 on compare match, clear OC0 at TOP
---------------------------------------------------------*/
/*---------------------------------------------------------
    Compare Output Mode, Phase Correct PWM Mode(
-----------------------------------------------------------
COM01  COM00   Description
===========================================================
 0       0      Normal port operation, OC0 disconnected.
 0       0      Reserved
 0       1      Clear OC0 on compare match when up-counting. 
                Set OC0 on compare match when downcounting.
 0       1      Set OC0 on compare match when up-counting. 
                Clear OC0 on compare match when downcounting.
---------------------------------------------------------*/
/*--------------------------------------------------------------------------
   CS02:0: Clock Select
----------------------------------------------------------------------------
CS02  CS01   CS00     Description
============================================================================
 0      0      0      No clock source (Timer/Counter stopped).
 0      0      1      clkI/O/(No prescaling)
 0      1      0      clkI/O/8 (From prescaler)
 0      1      1      clkI/O/64 (From prescaler)
 1      0      0      clkI/O/256 (From prescaler)
 1      0      1      clkI/O/1024 (From prescaler)
 1      1      0      External clock source on T0 pin. Clock on falling edge.
 1      1      1      External clock source on T0 pin. Clock on rising edge.
--------------------------------------------------------------------------*/



/*-------------------------------------------------------------------
   TCNT0 (Timer/Counter Register define)
=====================================================================
   7     6      5      4      3     2     1     0
                    TCNT0[7:0]
-------------------------------------------------------------------*/
/*-------------------------------------------------------------------
   OCR0 (Output Compare Register define)
=====================================================================
   7     6      5      4      3     2     1     0
                    TCNT0[7:0]
-------------------------------------------------------------------*/
#endif

#endif

