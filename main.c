#include <stdio.h>
#include <stdlib.h>



#define GPIO_INPUTS_MAX  20
#define GPIO_OUTPUTS_MAX 20

#include "plib_next.h"

spec_input pull_non  = { PIN_PULL_NON };
spec_input pull_up   = { PIN_PULL_UP };
spec_input pull_down = { PIN_PULL_DOWN };

int main()
{
	
        pin led_red ={{'A',1},TYP_OUT} ;
	pin button_blue = { { 'A',2 },TYP_IN,&pull_non };

	//
	

	pin_setup(&led_red);
	pin_setup(&button_blue);

	printf("pp:%d\n", pin_get_pull(&button_blue));
//	pin_set_pull(&button_blue,&pull_up);
        printf("pp:%d\n", pin_get_pull(&button_blue));



    pin_get(&led_red);
    pin_toggel(&led_red);
    pin_get(&led_red);
    pin_reset(&led_red);
    pin_get(&led_red);

//    pin_get(&button_blue);

    printf("Hello world!\n");
	//system("PAUSE");
    return 0;
}
