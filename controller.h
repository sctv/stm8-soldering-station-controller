
#define get_flag(flagvar) (flags>>flagvar) & 1

//#define set_flag(flagvar) flags |= (1<<flagvar)
//#define reset_flag(flagvar) flags &= ~(1<<flagvar)
#define set_flag(flagvar) disableInterrupts(); flags |= (1<<flagvar); enableInterrupts()
#define reset_flag(flagvar) disableInterrupts(); flags &= ~(1<<flagvar); enableInterrupts()


#define CHECK_SWITCH_PERIOD 5
#define TEMP_LEVELS 8

#define HEAT_IDLE_CYCLES 10

typedef enum {
    FLAG_PREHEAT,
    FLAG_BLINK_ON,
    FLAG_ZERO_REACHED,
    FLAG_SWITCH_PRESSED,
    FLAG_HEATER_ENABLED,
    FLAG_END_TEMP_MEASURE,		//for processing in interrut
    FLAG_END_ADC_CONV			//for main-loop processing
} FLAGS;

