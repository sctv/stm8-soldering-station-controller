#include "main.h"


volatile uint8_t flags;
volatile uint8_t temp_lvl;

//volatile uint8_t check_switch_timer;
volatile uint8_t heat_counter;		//for caluclated heat||idle cycles


int8_t heat_cycles=30;		//pid regulated value

uint16_t temp_adc[TEMP_LEVELS] = { \
    0,			\ //OFF
    200,		\ //200C
    250,		\ //250C
    300,		\ //300C
    350,		\ //350C
    400,		\ //400C
    450,		\ //450C
    500			\ //480C (MAX)
};

extern uint8_t txbuf[UART_BUF_SIZE];	//for debug

/*
void switch_event_processing()
{
    if ( (SWITCH_PORT->IDR & SWITCH_PIN) && get_flag(FLAG_SWITCH_PRESSED) ) {			//if key is released (pull-up)
UART1->DR = '=';
	reset_flag(FLAG_SWITCH_PRESSED);
    } else if ( ((SWITCH_PORT->IDR & SWITCH_PIN) == 0) && !get_flag(FLAG_SWITCH_PRESSED) ) {	//if key is pressed
UART1->DR = '_';
	set_flag(FLAG_SWITCH_PRESSED);
	temp_lvl = (temp_lvl+1) % 8;
	LEDS_SET(temp_lvl);

//sprintf(txbuf,"LED: %d\r\n",(uint16_t)temp_lvl);
//UART_SendStr(txbuf);	//send result to uart
    }

}
*/

void zero_detection_event_processing()
{
    if ( ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN ) {
        if ( get_flag(FLAG_END_TEMP_MEASURE) ) {
	    reset_flag(FLAG_END_TEMP_MEASURE);
	    HEATER_ON;
	    set_flag(FLAG_HEATER_ENABLED);
	    heat_counter = heat_cycles;
	} else if (heat_counter == 0) {
	    if (get_flag(FLAG_HEATER_ENABLED)) {
		HEATER_OFF;
		reset_flag(FLAG_HEATER_ENABLED);
		heat_counter = HEAT_IDLE_CYCLES; 
	    } 
	} else {
		heat_counter--;
	}
    } else if ( (ZERO_DETECT_PORT->IDR & ZERO_DETECT_PIN)==0 ) {
	if ( (heat_counter == 0) && (!get_flag(FLAG_HEATER_ENABLED)) ) {
	    ADC_StartConversion();
	}
    }


}