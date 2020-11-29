
#include "definitions.h"
#include "peripheral/gpio/plib_gpio.h"
#include "stdio.h"

void CORE_TIMER_InterruptHandler( void );

#define ADC_VREF                (3.3f)
#define ADC_MAX_COUNT           (1023U)

uint16_t adc_count;
float Acc1;
uint16_t adc_count2;
float Brake;

void __ISR(_CORE_TIMER_VECTOR, ipl1SOFT) CORE_TIMER_Handler (void)
{   
        //ADC_SamplingStart();
    ADC_InputSelect(ADC_MUX_A, ADC_INPUT_POSITIVE_AN23, ADC_INPUT_NEGATIVE_VREFL);
    ADC_ConversionStart();
    while(!ADC_ResultIsReady());
    adc_count = ADC_ResultGet(ADC_RESULT_BUFFER_0);
    Acc1 = (float)adc_count * ADC_VREF / ADC_MAX_COUNT;
    
    ADC_InputSelect(ADC_MUX_A, ADC_INPUT_POSITIVE_AN29, ADC_INPUT_NEGATIVE_VREFL);
    ADC_ConversionStart();
    while(!ADC_ResultIsReady());
    adc_count2 = ADC_ResultGet(ADC_RESULT_BUFFER_0);
    Brake = (float)adc_count2 * ADC_VREF / ADC_MAX_COUNT;
    
    LATDINV = (1<<2);
    CORE_TIMER_InterruptHandler();
}

