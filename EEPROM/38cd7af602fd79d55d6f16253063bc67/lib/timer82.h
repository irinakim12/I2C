 
#ifndef __TIMER82_H
#define __TIMER82_H

typedef            void     (*timer2_register_function)(void);


void timer82_rtc_enable(void);
void timer82_rtc_disable(void);
void timer82_interrupt_oc_enable(void);
void timer82_interrupt_oc_disable(void);
void timer82_interrupt_ov_enable(void);
void timer82_interrupt_ov_disable(void);
void timer82_interrupt_ovf_clear(void);
void timer82_interrupt_ocf_clear(void);
void timer82_timer_stop();
u8 timer82_init(u32 dwFOSC, u16 tick_time_ms, byte a_WaveFormMode, byte a_ComOutMode, byte a_byteDiv);
void register_timer2_function(timer2_register_function fn);






/*-------------------------------------------------------------------
   ASSR (Asynchronous Status Register define (bits 7-4 reserved )
=====================================================================
  7    6    5     4    3     2    1    0
    - reserved -      AS2 TCN2UB OCR2UB TCR2UB
-------------------------------------------------------------------*/
#define AS2     3		// Asynchronous Timer2/Counter 
#define TCN2UB  2		// TCN2UB: Timer2/Counter Update Busy
#define OCR2UB  1		// OCR2UB: Output Compare Register2 Update Busy
#define TCR2UB  0		// TCR2UB: Timer2/Counter Control Register2 Update Busy

#if 0

/*-------------------------------------------------------------------
   TIFR (Timer/Counter Interrupt Flag Register define)
=====================================================================
  7    6    5     4    3     2    1    0
OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0
-------------------------------------------------------------------*/
#define OCF2    7		// OCF2: Output Compare Flag 2		
#define TOV2    6		// TOV2: Timer/Counter2 Overflow Flag
#define ICF1    5		// ICF1: Timer/Counter1, Input Capture Flag
#define OCF1A   4		// OCF1A: Timer/Counter1, Output Compare A Match Flag
#define OCF1B   3		// OCF1B: Timer/Counter1, Output Compare B Match Flag
#define TOV1    2		// TOV1: Timer/Counter1, Overflow Flag
#define OCF0    1		// OCF0: Output Compare Flag 0
#define TOV0    0		// TOV0: Timer/Counter0 Overflow Flag

/*-------------------------------------------------------------------
   TIMSK (Timer/Counter Interrupt Mask Register define)
=====================================================================
  7     6      5      4      3     2     1     0
OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0
-------------------------------------------------------------------*/
#define OCIE2   7		// OCIE2: Timer/Counter2 Output Compare Match Interrupt Enable
#define TOIE2   6		// TOIE2: Timer/Counter2 Overflow Interrupt Enable
#define TICIE1  5		// TICIE1: Timer/Counter1, Input Capture Interrupt Enable
#define OCIE1A  4		// OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
#define OCIE1B  3		// OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable
#define TOIE1   2		// TOIE1: Timer/Counter1, Overflow Interrupt Enable
#define OCIE0   1		// OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE0   0		// TOIE0: Timer/Counter0 Overflow Interrupt Enable

#endif

#endif
