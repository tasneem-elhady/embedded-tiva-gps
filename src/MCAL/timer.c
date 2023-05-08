#include "TM4C123GH6PM.h"
#include "timer.h"

const double ClkFreq = 16e6; // the frequency of chip's clock
const double millisecondValue = (0.001 * ClkFreq); // higher accuracy than " - 1"

void delay_ms(long long ms) {
	SysTick -> LOAD =  ms * millisecondValue;
		//NVIC_ST_RELOAD_R = ms * millisecondValue;
	SysTick -> CTRL = 0x05;
		//NVIC_ST_CTRL_R = 0x05;
	
		while( (SysTick -> CTRL & 0x10000) == 0);
		//while( (NVIC_ST_CTRL_R & 0x10000) == 0);
}