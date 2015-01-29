
#ifndef __7SEGMENT_H
#define __7SEGMENT_H



// fnd1
#define FND1_DDR				DDRD
#define FND1_PORT				PORTD
#define FND1_PIN					PIND
#define FND1_PIN_NO				PD4

// fnd2
#define FND2_DDR				DDRD
#define FND2_PORT				PORTD
#define FND2_PIN					PIND
#define FND2_PIN_NO				PD5

// fnd3
#define FND3_DDR				DDRD
#define FND3_PORT				PORTD
#define FND3_PIN					PIND
#define FND3_PIN_NO				PD6

// fnd4
#define FND4_DDR				DDRD
#define FND4_PORT				PORTD
#define FND4_PIN					PIND
#define FND4_PIN_NO				PD7

#define FND_DATA_DDR			DDRA
#define FND_DATA_PORT			PORTA

void bsp_fnd_gpio_init(void);
void fnd_puts(u16 num_data, u16 delay_ms);
void fnd_puts_temperature(u16 num_data, u16 delay_ms);
void fnd_puts_voltage(u16 num_data, u16 delay_ms);

#endif
