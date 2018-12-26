//Battery Analog to Digital Conversion

#include "game_console.h"

void init_BattCheck(){
	
	//Set VBATT I/Os as input.
	VBATT_DIR(IN);

	//AADC Multiplexer Selection Register – ADMUX
	//---Use Internal 2.56V reference: (REFS1,REFS0) = (1,1)
	//---Right Adjusted Result: ADLAR = 0
	//---channel ADC2, pin A2: MUX4:0 = (00010)
	ADMUX = _BV(REFS1)|_BV(REFS0)|_BV(MUX1);

	//ADC Control and Status Register A – ADCSRA 
	//---enable ADC: ADEN = 1
	//---ADC prescaler 64 (ADPS2:0) = (110)
	//ADC prescaler is 64 because 8000MHz/64=125kHz 
	//For maximum resolution (within 50kHz to 200kHZ range)
	//---Enable Interrupt: ADIE = 1
	//---Enable Auto Triggering: ADATE = 1
	ADCSRA = _BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADIE)|_BV(ADATE);

	//Special Function IO Register, SFIOR
	//---Set Trigge for ADATE every 1 second (when TIMER1 overflows): 
	//---ADTS1,ADTS2 = 1,1
	SFIOR |= _BV(ADTS1)|_BV(ADTS2);
}



