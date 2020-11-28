

#include "definitions.h"
#include "peripheral/gpio/plib_gpio.h"

void CORE_TIMER_InterruptHandler( void );



void __ISR(_CORE_TIMER_VECTOR, ipl1SOFT) CORE_TIMER_Handler (void)
{   
    LATDINV= (1<<2);
    CORE_TIMER_InterruptHandler();
}

