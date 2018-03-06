#ifndef PLIB_NEXT_H_INCLUDED
#define PLIB_NEXT_H_INCLUDED

typedef struct PIN_s                  pin;

typedef struct PIN_ADDRESS_s          pin_address;
typedef enum   PIN_TYPE_e             pin_type;


typedef struct FNC_OF_INPUTS_s        fnc_input;
typedef struct FNC_OF_OUTPUTS_s       fnc_output;
//....

typedef struct SPEC_SETTINGS_INPUT_s  spec_input;
typedef struct SPEC_SETTINGS_OUTPUT_s spec_output;
//....

typedef enum   PIN_SET_PULL_e        pin_pull;
//....


int pin_setup(pin *pin);
int pin_free(pin *pin);

int pin_put(pin *pin, int value);
int pin_set(pin *pin);
int pin_reset(pin *pin);
int pin_get(pin *pin);
int pin_toggel(pin *pin);


int pin_set_pull(pin *pin, pin_pull * pull_conf);
int pin_get_pull(pin *pin);


//
// Not interesting for lib usage
//





struct PIN_ADDRESS_s
{
    int PORT;
    int PIN;
};

enum PIN_TYPE_e
{
	TYP_OUT  	= 0,
	TYP_IN  	= 1,
	TYP_ADC  	= 2,
	TYP_DAC  	= 3,
	TYP_UART_RX = 4,
	TYP_UART_TX = 5,

	TYP_NOTINIT = 97,
	TYP_FREED   = 98,
	TYP_NON     = 99

};

struct PIN_s
{

                    pin_address addr;
                    pin_type    typ;
    const           void *      spec_setings;
    const           void *      fnc;
                    int         id;
};


struct FNC_OF_INPUTS_s
{
	int (*get)			 ( pin *self );
	int (*set_pull_conf) (pin *self, pin_pull * pull_conf);
	int (*get_pull_conf) (pin *self);
	pin * self;
};

struct FNC_OF_OUTPUTS_s
{
    int (*put)   ( pin *self, int a);
	int (*set)   ( pin *self);
	int (*reset) ( pin *self);
	int (*get)   ( pin *self);
	int (*toggel)( pin *self);
	pin * self;
};

enum PIN_SET_PULL_e
{
    PIN_PULL_NON=0,
    PIN_PULL_UP=1,
    PIN_PULL_DOWN=2
};

struct SPEC_SETTINGS_INPUT_s
{
    pin_pull pull_config;
};
struct SPEC_SETTINGS_OUTPUT_s
{
    int blank;
};

//spec_input bbsic = { PIN_PULL_DOWN };
#endif // PLIB_NEXT_H_INCLUDED
