#include <project.h>

CY_ISR(IR_ISR_Handler) //macro for interrupt handler
{
    LED_Write(1);
    CyDelay(1000);
    IR_out_ClearInterrupt();
    LED_Write(0);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_StartEx(IR_ISR_Handler);
    
    for(;;)
    {
    }
}
