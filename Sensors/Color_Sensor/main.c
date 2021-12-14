#include "project.h"
#include <stdio.h>

uint16_t iFreq = 0 ;
int dataReady = 0 ;
int col_det = 0 ;//(1 is red, 2 is green and 3 is blue)
char string1[20];

CY_ISR(counter_isr)
{
    Colour_Counter_Stop() ;
    Colour_Timer_Stop() ;
    ColSens_LED_Write(0) ;
    
    Colour_Timer_ReadStatusRegister() ;
    Colour_Counter_INT_ClearPending() ;

    iFreq = Colour_Counter_ReadCounter() ;
    dataReady = 1 ;
}

void start_measure(void)
{
    ColSens_LED_Write(1) ;
    Colour_Control_Reg_Write(1) ;
    CyDelay(1) ;
    Colour_Control_Reg_Write(0) ;
    dataReady = 0 ;
    Colour_Counter_Start() ;
    Colour_Counter_INT_StartEx(counter_isr) ;
    Colour_Timer_Start() ;
}

int select_color(int color_to_sense) 
{
    switch(color_to_sense) {
    case 0: //Red
        ColSens_S2_Write(0) ; ColSens_S3_Write(0) ; break ;
    case 1: //Blue
        ColSens_S2_Write(0) ; ColSens_S3_Write(1) ; break ;
    case 2: //no filter
       ColSens_S2_Write(1) ; ColSens_S2_Write(0) ; break ;
    case 3: //Green
        ColSens_S2_Write(1) ; ColSens_S3_Write(1) ; break ;
    default:
        break ; 
    }
    return(0) ;
}

int get_frequency(int color_sense)
{
    select_color(color_sense) ;
    //S0 and S1 Set the scale to 20%
    ColSens_S0_Write(1) ; 
    ColSens_S1_Write(0) ;
    start_measure() ;
    while(!dataReady) {
        ;
    }
    return(iFreq) ;
}

void color_sense()
{
    //Adjust colour of RGB LED
    Red_LED_Write(1);
    Green_LED_Write(1);
    Blue_LED_Write(1); 
    
    uint freq = 0;
    int RGB_freq[4];
    
    for (int color_sense = 0 ; color_sense <4  ; color_sense++ ) {
        freq = get_frequency(color_sense) ;
        RGB_freq[color_sense] = freq;
    }
    
    //Colour choice
    if (RGB_freq[0] > RGB_freq[1])
    {
        if (RGB_freq[0] > RGB_freq[3])
        col_det = 1; //red
        
        else
        col_det = 2; //green
    }
    
    else if (RGB_freq[1] > RGB_freq[3])
    col_det = 3; //blue
    
    else
    col_det = 2; //green
}

void trigger_servo()
{
        PWM_1_WriteCompare(900);
        CyDelay(1000);
        PWM_1_WriteCompare(2500);
        CyDelay(1000);
        PWM_1_WriteCompare(0);
        CyDelay(1000);
}

int main(void)
{    
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start() ;
    start_measure();
    PWM_1_Start();
    
    
    
    for(;;) {
        color_sense();
        sprintf(string1,"color = %d\n",col_det);
        UART_1_PutString(string1);
        switch (col_det)
        {
            case(1): Red_LED_Write(1);//RED
            break;
            case(2): Green_LED_Write(0);//GREEN
            break;
            case(3): Blue_LED_Write(0);//BLUE
            break;     
            default: break;
        }
        CyDelay(1000);
    }
}
/* [] END OF FILE */
