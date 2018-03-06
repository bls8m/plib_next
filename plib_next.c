#include "plib_next.h"

#include <stdio.h>
#include <stdlib.h>

#include "backend/pc_fake/lib_pc.h"
//....
#define GPIO_INPUTS_MAX  20
#define GPIO_OUTPUTS_MAX 20


fnc_input  array_of_list_of_in_fnc[GPIO_INPUTS_MAX]={{0}}; // one is used per input pin
fnc_output array_of_list_of_out_fnc[GPIO_OUTPUTS_MAX]={{0}};// one is used per output pin

int inputs_used_counter=0;   //used to keep track of how many - fnc_input  array_of_list_of_in_fnc[200] - are used
int outputs_used_counter=0;   //used to keep track of how many - fnc_output array_of_list_of_out_fnc[20]] - are used

int pin_setup(pin *pin)
{
    switch(pin->typ)
    {
        case TYP_OUT     : printf("00_OUT\n");
                            {
                                array_of_list_of_out_fnc[outputs_used_counter].put=     f_pc_out_put;
                                array_of_list_of_out_fnc[outputs_used_counter].set=     f_pc_out_set;
                                array_of_list_of_out_fnc[outputs_used_counter].reset=   f_pc_out_reset;
                                array_of_list_of_out_fnc[outputs_used_counter].get=     f_pc_out_get;
                                array_of_list_of_out_fnc[outputs_used_counter].toggel=  f_pc_out_toggel;
                                array_of_list_of_out_fnc[outputs_used_counter].self=    pin;

                                pin->fnc=&array_of_list_of_out_fnc[outputs_used_counter];
                                outputs_used_counter++;


                            }
                           break;
        case TYP_IN      : printf("00_IN \n");
                            {
                                array_of_list_of_in_fnc[inputs_used_counter].get=f_pc_in_get;
							//	array_of_list_of_in_fnc[inputs_used_counter].get_pull_conf=get_pull_conf;
							//	array_of_list_of_in_fnc[inputs_used_counter].set_pull_conf=set_pull_conf;
                                array_of_list_of_in_fnc[inputs_used_counter].self=pin;
                                pin->fnc=&array_of_list_of_in_fnc[inputs_used_counter];
                                inputs_used_counter++;
                            }
                           break;
        case TYP_ADC     : printf("00_ADC\n"); break;
        case TYP_DAC     : printf("00_DAC\n"); break;
        case TYP_UART_RX : printf("00_UART_RX\n"); break;
        case TYP_UART_TX : printf("00_UART_TX\n"); break;
        default          : printf("00_ERROR_0\n"); break;
    }
    printf("00_pin %c%d has been set up\n",pin->addr.PORT,pin->addr.PIN);
    return 1;
}
int pin_free(pin *pin)
{
    switch(pin->typ)
    {
        case TYP_OUT     : printf("00_OUT\n");
                            {
                                int i=0;
                                int j=0;
                                for(i=0;i<GPIO_OUTPUTS_MAX;i++)
                                {
                                   if(array_of_list_of_out_fnc[i].self==pin)
                                   {

                                       for(j=i;i<GPIO_INPUTS_MAX;j++)
                                       {
                                           printf("01_found\n");
                                           array_of_list_of_out_fnc[j].self=0;

                                          if(j<(GPIO_OUTPUTS_MAX-1))
                                           {
                                               array_of_list_of_out_fnc[j]=array_of_list_of_out_fnc[j+1];
                                           }
                                           else
                                           {
                                               //array_of_list_of_out_fnc[j];
                                             //
                                               outputs_used_counter--;
                                               printf("01_pin %c%d has been destroyed\n",pin->addr.PORT,pin->addr.PIN);
                                               (*pin).typ=TYP_FREED;
                                             //  ((fnc_output *)(*pin).fnc).
                                               (*pin).fnc=0;
                                              // pin=0;
                                               return 1;
                                           }
                                       }

                                   }
                                }


                            }
                           break;
        case TYP_IN      : printf("00_IN \n");
                            {
                            }
                           break;
        case TYP_ADC     : printf("00_ADC\n"); break;
        case TYP_DAC     : printf("00_DAC\n"); break;
        case TYP_UART_RX : printf("00_UART_RX\n"); break;
        case TYP_UART_TX : printf("00_UART_TX\n"); break;
        default          : printf("00_ERROR_0\n"); break;
    }

    printf("01_pin %c%d has NOT been destroyed",pin->addr.PORT,pin->addr.PIN);
    return 1;
}

int pin_put(pin *pin, int value)
{
    if (pin==0||pin->typ==TYP_NON||pin->typ==TYP_FREED)
    {
        printf("pin is not setup properly or has been freed\n");
        return 0;
    }
    else if(pin->typ==TYP_OUT)
    {
        return ((fnc_output *)(*pin).fnc)->put(pin,value);
    }
    else
    {
        printf("wrong pin type _output expected\n");
        return 0;
    }

}
int pin_set(pin *pin)
{
    if (pin==0||pin->typ==TYP_NON||pin->typ==TYP_FREED)
    {
        printf("pin is not setup properly or has been freed\n");
        return 0;
    }
    else if(pin->typ==TYP_OUT)
    {
        return ((fnc_output *)(*pin).fnc)->set(pin);
    }
    else
    {
        printf("wrong pin type _output expected\n");
        return 0;
    }
}
int pin_reset(pin *pin)
{
    if (pin==0||pin->typ==TYP_NON||pin->typ==TYP_FREED)
    {
        printf("pin is not setup properly or has been freed\n");
        return 0;
    }
    else if(pin->typ==TYP_OUT)
    {
        return ((fnc_output *)(*pin).fnc)->reset(pin);
    }
    else
    {
        printf("wrong pin type _output expected\n");
        return 0;
    }
}
int pin_get(pin *pin)
{
    if (pin==0||pin->typ==TYP_NON||pin->typ==TYP_FREED)
    {
        printf("pin is not setup properly or has been freed\n");
        return 0;
    }
    else if(pin->typ==TYP_OUT)
    {
        return ((fnc_output *)(*pin).fnc)->get(pin);
    }
    else if(pin->typ==TYP_IN)
    {
        return ((fnc_input *)(*pin).fnc)->get(pin);
    }
    else
    {
        printf("wrong pin type _output or _input expected\n");
        return 0;
    }
}
int pin_toggel(pin *pin)
{
    if (pin==0||pin->typ==TYP_NON||pin->typ==TYP_FREED)
    {
        printf("pin is not setup properly or has been freed\n");
        return 0;
    }
    else if(pin->typ==TYP_OUT)
    {
        return ((fnc_output *)(*pin).fnc)->toggel(pin);
    }
    else
    {
        printf("wrong pin type _output expected\n");
        return 0;
    }
}



//more specialiced functions

int pin_set_pull(pin *pin, pin_pull * pull_conf)
{
	if (pin == 0 || pin->typ == TYP_NON || pin->typ == TYP_FREED)
	{
		printf("pin is not setup properly or has been freed\n");
		return 0;
	}
	else if (pin->typ == TYP_IN)
	{
		((spec_input*)(pin->spec_setings))->pull_config = *pull_conf;
		return (((spec_input*)(pin->spec_setings))->pull_config);
	}
	else
	{
		printf("wrong pin type _output expected\n");
		return 0;
	}
	
	return 0;
}
int pin_get_pull(pin *pin)
{
	if (pin == 0 || pin->typ == TYP_NON || pin->typ == TYP_FREED)
	{
		printf("pin is not setup properly or has been freed\n");
		return 0;
	}
	else if (pin->typ == TYP_IN)
	{
		return (((spec_input*)(pin->spec_setings))->pull_config);
	}
	else
	{
		printf("wrong pin type _output expected\n");
		return 0;
	}

	return 0;

}