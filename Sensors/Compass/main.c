/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "math.h"
#define DeviceID 0x0D


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int16 array[6];//create an array
    int16 x;
	int16 y;
	int16 z;
    double orientation;
	char string[20];
    I2C_1_Start();
    UART_1_Start();
    
    //write command
    I2C_1_MasterSendStart(DeviceID,I2C_1_WRITE_XFER_MODE);
    I2C_1_MasterWriteByte(0x09);//Write the compass for continous measurement.
    I2C_1_MasterWriteByte(0x1D);
    I2C_1_MasterSendStop();
    CyDelay(100);
    for(;;)
    {
       I2C_1_MasterSendStart(DeviceID,I2C_1_WRITE_XFER_MODE);
	   I2C_1_MasterWriteByte(0x00);
	   I2C_1_MasterSendStop(); /* Place your application code here. */
       CyDelay(100);
    
       //Send read data.
    I2C_1_MasterSendStart(DeviceID,I2C_1_READ_XFER_MODE);
    array[0] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    array[1] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    array[2] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    array[3] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    array[4] = I2C_1_MasterReadByte(I2C_1_ACK_DATA);
    array[5] = I2C_1_MasterReadByte(I2C_1_NAK_DATA);
    I2C_1_MasterSendStop();
    CyDelay(100);
    x = array[1]<<8|array[0]; //x-value //shift to left by 8 bits 
	y = array[3]<<8|array[2]; //z-value //shift to left by 8 bits 
	z = array[5]<<8|array[4]; //y-value //shift to left by 8 bits
    orientation = atan2(y,x);
    if (orientation>2*3.14)
    {
        orientation -= 2*3.14;
    }
    else if (orientation<0)
    {
    orientation += 2*3.14;
    }
    orientation = orientation*(180/3.14);//To get the angle
    sprintf(string,"%d/n",(int)orientation);
    UART_1_PutString(string);
    CyDelay(100);
    }
}

/* [] END OF FILE */
