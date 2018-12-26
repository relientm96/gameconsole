/*------Program Interrupts---------*/

#include "game_console.h"
#include "function_prototypes.h"

//Button Register
volatile byte buttonFlag = OFF;
//Time Variable (16 bits)
unsigned short time = TIMER_INIT;
//Battery Health Global Variable
unsigned short BatteryHealth;
//Battery Low Flag
volatile byte batteryLowFlag = OFF;

/*---Interrupts---*/

//Interrupts for Button
//Flags high when button is pressed
ISR(INT0_vect){
	buttonFlag = ON;
}

//A one second general use timer (always running in background)
ISR(TIMER1_OVF_vect){

	//Timer has reached 10 seconds
	//(TARGET = 0)
	if(time == TARGET){
		//Reset the timer (TIMER_INIT = 9)
		time = TIMER_INIT;
	}
	//Else Decrement time 
	else time--;
	
	//Reset to amount to start from 
	TCNT1 = TICKS_INIT;
}

//Return External Interrupt if Called by Bat Low Led external interrupt
//This is due to me connecting my Bat Low Led to an external interrupt pin
ISR(INT2_vect){
	//Return Straight away 
	return;
}

//Interrupt when ADC conversion is done
ISR(ADC_vect){
	
	//Read Value from adc when conversion finishes
	BatteryHealth = ADC;
	
	//Set Battery LOW  LED according to battery threshold
	/* Calculated using: Battery Health = (Vbatt/2.56)*1024 */
	if(BatteryHealth < VBATT_LEVEL){
		BAT_LOW_LED(ON);
		batteryLowFlag = ON;
	}
	else{
		BAT_LOW_LED(OFF);
		batteryLowFlag = OFF;
	}
}

//External Interrupt from Button Press Event
//Interrupt is coming from PD2
void init_ButtonInterrupt(){
	
	//Set as Input pin                    
	BTN_INTERRUPT_DIR(IN); 
	
	// General Interrupt Control Register: GICR
	//---Enable Interrupt on PD2: INT0 = 1
	//---Enable Interrupt on PB4: INT2 = 1 (used as my BattLow Led comes from external interrupt pin)
	GICR = _BV(INT0)|_BV(INT2);
	
	//MCU Control Register: MCUCR
	//---Rising Edge of INT0 generates Interrupt: ISC01,ISC00 = 1,1
	//----Interrupt input is from a NAND gate (high when one input is zero)
	//----Thus the button interrupt pin would see a rising edge, indicating button is pressed
	MCUCR = _BV(ISC01)|_BV(ISC00);
	
	//MCU Control and Status Register: MCUCSR (FOR INT2)
	//---Interrupt Sense Control: ISC2 = 0
	//--->Activates External Interrupt INT2 on Falling Edge 
	//Not written in code as it is already 0
	
}

//Initialize a Timer Interrupt to poll and check Battery Health
void init_TimerInterrupt(){
	
	//16 Bit Counter
	
	/*--Start Counter--*/
	//TCCR1B: Timer Control Register 1 (B)
	//---Set clk/1024 pre-scaling: CS12,CS10 = 1,1
	TCCR1B |= _BV(CS12)|_BV(CS10);
	
	//TCNT1: Timer/Counter 1 Register (16 bit register)
	//-----Clock is now : 8000kHz/1024 = 7812 Ticks Per second 
	//-----implying 128us per tick
	//-----We need 7812 ticks to count as one second
	//-----16 Bit counter counts from 0 -> 65535,
	//-----We need an interval of 7812 ticks
	//-----Thus, we use 65535-7812 = 57723 as our starting count
	//-----TICKS_INIT is defined as 57723 in game console header file
	TCNT1 = TICKS_INIT;
	
	//TIMSK: Timer Interrupt Mask Register
	//---Enable Timer Overflow Interrupt: TOIE0 = 1
	//----runs TIMER1_OVF_vect when TCNT1 overflows
	TIMSK |= _BV(TOIE1);
	
}






