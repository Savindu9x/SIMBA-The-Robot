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
#define SPEED 80
#define SYNC 10
#define L_DEGREE 13250
#define R_DEGREE 16250
#define PUCK_END_ZONE 96000
#define GAP 40000
#define CAPTURE_ZONE 35
#define WALL_ALLIGNMENT 25     //**CONFIGURE
#define OPPONENT 15
//Define Global Variables.
int8 state=0;
int Base;
int countL;int countR;
int8 speedL;int speedR;
int8 obstacle1 = 0;int8 obstacle2 = 0;
int8 obstacle3 = 0;int8 obstacle4 = 0;
int S1_distance=OPPONENT;int S2_distance=OPPONENT;
int S3_distance=OPPONENT;int S4_distance=OPPONENT;
int8 puckdetected;
uint16_t iFreq = 0;
int dataReady = 0;
char string1[20];
int position =0;


//Define Function Declarations.
void encode_sync(char Move);
void move_straight(char direction,int distance);
void motorcontrl(char opt);
void move_straight(char direction,int distance);
void turn(char direction,int degree);
void wall_allignment();
void start_measure();
int color_sense();
int get_frequency(int color_sense);
void select_color(int color_to_sense);
void compass();
void side_allignment(char side);

void baseRoute(int Base);
void searchPuck();
void grabPuck();
void back2Base(int Base);
void sortPuck();
void back2Zone(int Base,int counter);

//Interrupts for Obstacle Aviodance
CY_ISR(S1_handler) {//Front LEFT(S1) Ultrasonic Sensor 
	float range1;
	S1_Timer_ReadStatusRegister();
	range1 = (65535 - S1_Timer_ReadCounter()) / 58;
	if (range1 <S1_distance) {
		obstacle1 = 1;
	}
	else if (range1 > S1_distance) {
		obstacle1 = 0;
	}
}
CY_ISR(S2_handler) {//Front RIGHT (S2) Ultrasonic Sensor 
	float range2;
	S2_Timer_ReadStatusRegister();
	range2 = (65535 - S2_Timer_ReadCounter()) / 58;
	if (range2 < S2_distance) {
		obstacle2 = 1;
	}
	else if (range2 > S2_distance) {
		obstacle2 = 0;
	}
}
CY_ISR(S3_handler) {//Side Right (S3) Ultrasonic Sensor
	float range3;
	S3_Timer_ReadStatusRegister();
	range3 = (65535 - S3_Timer_ReadCounter()) / 58;
	if (range3 < S3_distance) {
		obstacle3 = 1;
		
	}
	else if (range3 > S3_distance) {
		obstacle3 = 0;
		
	}
}
CY_ISR(S4_handler) {//Side Left (S4) Ultrasonic Sensor 
	float range4;
	S4_Timer_ReadStatusRegister();
	range4 = (65535 - S4_Timer_ReadCounter()) / 58;
	//sprintf(string1,"%d\n",(int)range4);
	//UART_PutString(string1);
	if (range4 < S4_distance) 
    {
		obstacle4 = 1;
		//move_straight('B',10000);
	}
	else if (range4 >S4_distance) 
    {
		obstacle4 = 0;
		
	}
}

//Interrupts for IR senosr- Puck Detecting
CY_ISR(interrupt5_handler)
{ 
    if (IR_Out_Read() ==1){
    puckdetected=0;
    IR_Out_ClearInterrupt();
    }
    else if (IR_Out_Read()==0){
        puckdetected=1;
        IR_Out_ClearInterrupt();
    }
}
//Interrupts for Color Detection
CY_ISR(interrupt6_handler) {
	Color_Counter_Stop();
	Color_Timer_Stop();
	Color_LED_Write(0);
	Color_Timer_ReadStatusRegister();
	isr_6_ClearPending();
	iFreq = Color_Counter_ReadCounter();
	dataReady = 1;
}

//Initializing Code Blocks
void Initialize(void)
{
	PWM_Motor_Start();
	QuadDec_L_Start();
	QuadDec_R_Start();
	S1_Timer_Start();
	S2_Timer_Start();
	S3_Timer_Start();
	S4_Timer_Start();
	Flicker_Servo_Start();
	RobotArm_Servo_Start();
	start_measure();
	isr_1_StartEx(S1_handler);
	isr_2_StartEx(S2_handler);
	isr_3_StartEx(S3_handler);
	isr_4_StartEx(S4_handler);
    //isr_5_StartEx(interrupt5_handler);
	UART_Start();
    I2C_Start();
    RobotArm_Servo_WriteCompare2(500);//Gripper Closes Up
    RobotArm_Servo_WriteCompare1(2200); //tower up
    Flicker_Servo_WriteCompare(900);//flicker in position
    
}
int main(void)
{
   CyGlobalIntEnable; /* Enable global interrupts. */
   Initialize();

  
   int counter=0;

   if (Base_Selector_Read()==1)//Button not Pressed
        {
         Base =1;   
        }
   else if (Base_Selector_Read() ==0) //Button pressed
        {
         Base =2;  
        }
        
   for(;;)
   {
    switch(state){
        case 0:
        
        baseRoute(Base);
        //state++;
        break;
        case 1:
        searchPuck();
        //state++;
        break;
        case 2:
        grabPuck();
        //state++;
        break;
        case 3:
        back2Base(Base);
        break;
        case 4:
        sortPuck();
        break;
        case 5:
        back2Zone(Base,counter);
        counter++;
        //state =1;
        break;
        default:
        break;
    }
    
   //Triggers for Obstacle Detection  
//     while (S1_Echo_Read() == 0){
//		S1_Trigger_Write(1);
//		CyDelayUs(10);
//		S1_Trigger_Write(0);
//	    }
//	    CyDelay(10);
//	while (S2_Echo_Read() == 0) {
//		S2_Trigger_Write(1);
//		CyDelayUs(10);
//		S2_Trigger_Write(0);
//	     }
//        CyDelay(10);
	
//////////	CyDelay(10);
//	while (S3_Echo_Read() == 0) {
//		S3_Trigger_Write(1);
//		CyDelayUs(10);
//		S3_Trigger_Write(0);
//	}
//	CyDelay(10);
//	while (S4_Echo_Read() == 0) {
//		S4_Trigger_Write(1);
//		CyDelayUs(10);
//		S4_Trigger_Write(0);
//	}
	CyDelay(10);
}
}

//Syncronize the Speeds
void encode_sync(char Move) {
    
        countL = QuadDec_L_GetCounter();
        countR = QuadDec_R_GetCounter();
   if(Move=='F')
    {
	if ((countL - countR >= SYNC) || (countL - countR == 0)) {
		speedL = SPEED-40;
		speedR = SPEED;  
	}
	else if (countR - countL >= SYNC) {
		speedL = SPEED+10;     //should increase
		speedR = SPEED;
	}
    }
   if(Move=='B')
    {
      if ((countL - countR >= SYNC) || (countL - countR == 0)) {
		speedL = SPEED+10;
		speedR = SPEED;  
	}
	else if (countR - countL >= SYNC) {
		speedL = SPEED-40;     //should increase
		speedR = SPEED;
	}
    }
}

// Control Inputs For Motors
void motorcontrl(char opt) {
	switch (opt) //opt==>option
	{
	case 'F': //Forward - high speed motion
		encode_sync('F');
		Forward_L_Write(1);
		Backward_L_Write(0);
		Forwad_R_Write(1);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(speedL);
		PWM_Motor_WriteCompare2(speedR);
		break;
    case 'f': //Forward - low speed motion
		encode_sync('F');
		Forward_L_Write(1);
		Backward_L_Write(0);
		Forwad_R_Write(1);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(SPEED);
		PWM_Motor_WriteCompare2(SPEED);
		break;
	case 'B': //Backward - high speed motion
	    encode_sync('B');
		Forward_L_Write(0);
		Backward_L_Write(1);
		Forwad_R_Write(0);
		Backward_R_Write(1);
		PWM_Motor_WriteCompare1(speedL);
		PWM_Motor_WriteCompare2(speedR);
		break;
    case 'b'://Back - low speed motion
        encode_sync('B');
        Forward_L_Write(0);
		Backward_L_Write(1);
		Forwad_R_Write(0);
		Backward_R_Write(1);
		PWM_Motor_WriteCompare1(speedL-20);
		PWM_Motor_WriteCompare2(speedR-20);
        break;
	case 'S': //Stop
		Forward_L_Write(0);
		Backward_L_Write(0);
		Forwad_R_Write(0);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(0);
		PWM_Motor_WriteCompare2(0);
		QuadDec_L_SetCounter(0);
		QuadDec_R_SetCounter(0);
		break;
	case 'L': //Left
		Forward_L_Write(0);
		Backward_L_Write(1);
		Forwad_R_Write(1);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(SPEED);
		PWM_Motor_WriteCompare2(SPEED);
		break;
	case 'R': //Right
		Forward_L_Write(1);
		Backward_L_Write(0);
		Forwad_R_Write(0);
		Backward_R_Write(1);
		PWM_Motor_WriteCompare1(SPEED);
		PWM_Motor_WriteCompare2(SPEED);
		break;
	case 'C': //Callibrate
		Forward_L_Write(1);
		Backward_L_Write(0);
		Forwad_R_Write(1);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(SPEED);
		PWM_Motor_WriteCompare2(SPEED);
		break;
	case 'X': // Reverse Left
		Forward_L_Write(0);
		Backward_L_Write(1);
		Forwad_R_Write(0);
		Backward_R_Write(0);
		PWM_Motor_WriteCompare1(SPEED);
		PWM_Motor_WriteCompare2(0);
		break;
	case 'Y': //Reverse Right
		Forward_L_Write(0);
		Backward_L_Write(0);
		Forwad_R_Write(0);
		Backward_R_Write(1);
		PWM_Motor_WriteCompare1(0);
		PWM_Motor_WriteCompare2(SPEED);
		break;
	default:
		break;
	}
}

//To move forward/Backward a certain distance
void move_straight(char direction,int distance){
    int8 command=0;
	while (command == 0) 
    {
		QuadDec_L_SetCounter(0);
		QuadDec_R_SetCounter(0);
		countL = 0;
		countR = 0;
		command = 1;
	}
    while(command==1)
    {
        countL = QuadDec_L_GetCounter();
        countR = QuadDec_R_GetCounter();
//        sprintf(string1,"Left Counter Value = %d\n",countR);
//        UART_PutString(string1);
        if(direction == 'F')
        {
	      if ((countR <= distance) || (countL <= distance))
	        {
		     motorcontrl('F');
	        }
	      else
	       {
		     motorcontrl('S');
		     countL = 0;
		     countR = 0;
		     command = 0;
	       }
        }
        else if (direction == 'B')
        {
            if ((countR >= -1 * distance) || (countL >= -1 * distance))
	            {
		          motorcontrl('B');
	            }
	        else
	            {
		         motorcontrl('S');
		         countL = 0;
		         countR = 0;
		         command = 0;
	            }
        }
    }
}

//To Turn 90 Degree Angles.
void turn(char direction,int degree){
    int8 command=0;
	while (command == 0) 
    {
		QuadDec_L_SetCounter(0);
		QuadDec_R_SetCounter(0);
		countL = 0;
		countR = 0;
		command = 1;
	}
    while(command ==1)
    {
        countL = QuadDec_L_GetCounter();
        countR = QuadDec_R_GetCounter();
        
         if (direction =='L')
          {
            if (countR <= degree)
	          {
		       motorcontrl('L');
	          }
	        else
            {
		      motorcontrl('S');
		      countL = 0;
		      countR = 0;
              command=0;
	         }
          }
         else if(direction=='R')
          {
            if (countL <= degree)
	          {
		      motorcontrl('R');
	          }
	        else {
		      motorcontrl('S');
		      countL = 0;
		      countR = 0;
              command=0;
	             }
          }
    }
    
}

//Wall Allignment
void wall_allignment(){
    int wall_detected=0;
    
    while (wall_detected == 0)
    {
        if(limitSW_1_Read()==1 && limitSW_2_Read()==1)
            {
              CyDelay(200);
              motorcontrl('B');
             }
        else  if (limitSW_1_Read()==1 && limitSW_2_Read() ==0 )
            {
                CyDelay(200);
                motorcontrl('Y');
            }
        else if (limitSW_1_Read()==0 && limitSW_2_Read()==1)
            {
                CyDelay(200);
                motorcontrl('X');                
            }
        else //robot has reached the wall.
            {
                motorcontrl('S');
                CyDelay(500);
                wall_detected = 1;
            }
    }   
}

//allignment using side Ultrasonic Sensors
void side_allignment(char side)
{
    S3_distance=S4_distance=WALL_ALLIGNMENT;
    int temp=0;
    while(temp==0)
    {
        
    if (side == 'L')
    {
    while (S3_Echo_Read() == 0) {
		S3_Trigger_Write(1);
		CyDelayUs(10);
		S3_Trigger_Write(0);
	}
    CyDelay(10);
    if (obstacle3==1)
    {
        motorcontrl('S');
        temp=1;
    }
    if (obstacle3==0)
    {
        motorcontrl('R');
    }
    }
    if(side=='R')
    {
        while (S4_Echo_Read() == 0) {
		S4_Trigger_Write(1);
		CyDelayUs(10);
		S4_Trigger_Write(0);
        }
        CyDelay(10);
        
    if (obstacle4==1)
    {
        motorcontrl('S');
        temp=1;
    }
    if (obstacle4==0)
    {
        motorcontrl('L');
    }
   }
 }
   S3_distance=S4_distance=OPPONENT; 
}
//Initiate the Interrupt for color sensor
void start_measure() {
	Color_LED_Write(1);
	Control_Reg_Color_Write(1);
	CyDelay(1);
	Control_Reg_Color_Write(0);
	dataReady = 0;
	Color_Counter_Start();
	isr_6_StartEx(interrupt6_handler);
	Color_Timer_Start();
}

//Color Sensing
int color_sense() {
	uint freq = 0;
	int RGB_freq[4];

	for (int color_sense = 0; color_sense < 4; color_sense++)
	{
		freq = get_frequency(color_sense);
		RGB_freq[color_sense] = freq;
	}
	// Color Choice
	if (RGB_freq[0] > RGB_freq[1])
	{
		if (RGB_freq[0] > RGB_freq[3]) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else if (RGB_freq[1] > RGB_freq[3])
	{
		return 3;
	}
	else {
		return 2;
	}
}

//Calling from Color_sense
int get_frequency(int color_sense) {
	select_color(color_sense);
	Color_S0_Write(1);
	Color_S1_Write(0);
	start_measure();
	while (!dataReady) 
    {
		;
	}
	return iFreq;
}

//Calling from get_frequency
void select_color(int color_to_sense) {
	switch (color_to_sense) {
	case 0://RED
		Color_S2_Write(0);
		Color_S3_Write(0);
		break;
	case 1: //BLUE
		Color_S2_Write(0);
		Color_S3_Write(1);
		break;
	case 2: //NO FILTER
		Color_S2_Write(1);
		Color_S2_Write(0);
		break;
	case 3: //GREEN
		Color_S2_Write(1);
		Color_S3_Write(1);
		break;
	default:
		break;
	}
}

//For compass 
void compass(){
            //UART_PutString("hi\n");
    
    
    int16 array[6]; //create an array to get x,y,z coordinates
    //int16 x;
    int16 y;
    int16 z;
    double orientation;
    int temp =0;
    
    I2C_MasterSendStart(DeviceID,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x0B);
    I2C_MasterWriteByte(0X01);
    I2C_MasterSendStop();
    CyDelay(100);
    
    I2C_MasterSendStart(DeviceID,I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(0x09);
    I2C_MasterWriteByte(0X1D);
    I2C_MasterSendStop();
    CyDelay(100);
    
    //for (;;)
    while (temp==0)
    {
        //motorcontrl('F');
        //UART_PutString("hi\n");
        I2C_MasterSendStart(DeviceID,I2C_WRITE_XFER_MODE);
        I2C_MasterWriteByte(0x00);
        I2C_MasterSendStop();
        
        //Send read Data.
        I2C_MasterSendStart(DeviceID,I2C_READ_XFER_MODE);
        array[0] = I2C_MasterReadByte(I2C_ACK_DATA);
        array[1] = I2C_MasterReadByte(I2C_ACK_DATA);
        array[2] = I2C_MasterReadByte(I2C_ACK_DATA);
        array[3] = I2C_MasterReadByte(I2C_ACK_DATA);
        array[4] = I2C_MasterReadByte(I2C_ACK_DATA);
        array[5] = I2C_MasterReadByte(I2C_NAK_DATA);
        I2C_MasterSendStop();
        
        //x = array[1]<<8|array[0]; //x-value //shift to left by 8 bits 
	    y = array[3]<<8|array[2]; //z-value //shift to left by 8 bits 
	    z = array[5]<<8|array[4]; //y-value //shift to left by 8 bits
        orientation = atan2(z,y);
        if (orientation>2*3.14)
        {
        orientation -= 2*3.14;
        }
        else if (orientation<0)
        {
        orientation += 2*3.14;
        }
        orientation = orientation*(180/3.14) ;//To get the angle
        sprintf(string1,"%d \n",(int)orientation);
        UART_PutString(string1);
        CyDelay(200);
        if (orientation>180 && orientation<360)
        {
           motorcontrl('R');
        }
        if (orientation<180 && orientation>28)
        {
            motorcontrl('L');
        }
          if (orientation>0 && orientation<22)
        {
           motorcontrl('R');
        }
        if (orientation<28 && orientation>22) 
        {
            motorcontrl('S');
            temp =1;
        }
    }
}
//Route for Base to Puck Collection Zone
void baseRoute(int Base){
    if(Base==1) // Base 01 - Upper Left Corner & Lower Right Corner
    {
        move_straight('F',45000);//Come out of the base
        turn('R',R_DEGREE);
        move_straight('F',12000);
        turn('L',L_DEGREE);
    }
    else if (Base ==2) // Base 02 - Upper Right Corner & Lower Left Corner
    {
        move_straight('F',45000);
        turn('L',L_DEGREE);
        move_straight('F',12000);
        turn('R',L_DEGREE);
    }
  state++;  
}

//Searching the within the Zone.
void searchPuck(){ //This function needs reconstruction.
   
    QuadDec_L_SetCounter(0);
    QuadDec_R_SetCounter(0);
    countL=0;
    countR=0;
    countL = QuadDec_L_GetCounter();
    S1_distance=S2_distance=OPPONENT;
    
    RobotArm_Servo_WriteCompare2(500);//Gripper Closes Up
    //CyDelay(1000);
    RobotArm_Servo_WriteCompare1(700);//Tower Goes Down
    CyDelay(500);
    RobotArm_Servo_WriteCompare2(950);//Gripper Opens Up
    CyDelay(500);
   
   int reverse=0;
   int temp=0;
   while(temp==0)
   {
   if(IR_Out_Read()==1)
    {   
      if((obstacle1==0)||(obstacle2==0))
        {
          motorcontrl('F');
        }
     if ((obstacle2==1)||(obstacle1==1)) //What to do if confront another robot or the wall.
        {
            motorcontrl('S');
            reverse=countL;
            move_straight('B',countL);
       if(Base ==1&&(position%2)==1) //Horizantal
         {
        turn('L',L_DEGREE);
        move_straight('F',20000);
        turn('R',R_DEGREE);
         }
        if(Base ==1&&(position%2)==0)//Vertical
         {
        turn('R',R_DEGREE);
        move_straight('F',20000);
        turn('L',L_DEGREE);
         }
        if(Base ==2 &&(position%2)==1 )//Horizantal
        {
        turn('R',R_DEGREE);
        move_straight('F',20000);
        turn('L',L_DEGREE);
        } 
        if(Base ==2 &&(position%2)==0 )//Vertical
        {
        turn('L',L_DEGREE);
        move_straight('F',20000);
        turn('R',R_DEGREE);
        } 
            temp=1;
        }
//        if ((obstacle3==1)||(obstacle4==1))
//        {
//            move_straight('B',10000);
//        }
        if((countL > PUCK_END_ZONE)  || (countR> PUCK_END_ZONE))
        {
           motorcontrl('S');
           reverse=countL;
           move_straight('B',countL);
        
        if(Base ==1&&(position%2)==1) //Horizantal
         {
        turn('L',L_DEGREE);
        move_straight('F',10000);
        turn('R',R_DEGREE);
         }
        if(Base ==1&&(position%2)==0)//Vertical
         {
        turn('R',R_DEGREE);
        move_straight('F',10000);
        turn('L',L_DEGREE);
         }
        if(Base ==2 &&(position%2)==1 )//Horizantal
        {
        turn('R',R_DEGREE);
        move_straight('F',10000);
        turn('L',L_DEGREE);
        } 
        if(Base ==2 &&(position%2)==0 )//Vertical
        {
        turn('L',L_DEGREE);
        move_straight('F',10000);
        turn('R',R_DEGREE);
        } 
        }
   }
    if (IR_Out_Read() ==0)//Depends on the position you place the IR sensor, move the robot.
     {
       motorcontrl('S');
       temp=1;
       move_straight('F',4000);
       state++;
     }
     while (S1_Echo_Read() == 0){
		S1_Trigger_Write(1);
		CyDelayUs(10);
		S1_Trigger_Write(0);
	    }
	    CyDelay(10);
    while (S2_Echo_Read() == 0) {
		S2_Trigger_Write(1);
		CyDelayUs(10);
		S2_Trigger_Write(0);
	     }
        CyDelay(10);
   while (S3_Echo_Read() == 0) {
		S3_Trigger_Write(1);
		CyDelayUs(10);
		S3_Trigger_Write(0);
	}
	CyDelay(10);
	while (S4_Echo_Read() == 0) {
		S4_Trigger_Write(1);
		CyDelayUs(10);
		S4_Trigger_Write(0);
	}
	CyDelay(10);
   }
}

//Collecting Puck using Gripper and Tower.
void grabPuck(){
    
    RobotArm_Servo_WriteCompare2(500);//Gripper Closes Up
    CyDelay(500);
//    RobotArm_Servo_WriteCompare1(700);//Tower Goes Down
//    CyDelay(1000);
    RobotArm_Servo_WriteCompare1(2400);//Tower Goes Up
    CyDelay(500);
//    GripperRobotArm_Servo_WriteCompare1(2300); //Gripper Opens Up
    
    
   state++;
}

//Goes to Puck Sorting Zone.
void back2Base(int Base){
    
    int temp=0;
    S1_distance=S2_distance=CAPTURE_ZONE;
    if ((position%2)==0)//Vertical
    {
    if(Base ==1)
     {
        turn('R',R_DEGREE);
     }
    else if (Base == 2)
     {
        turn('L',L_DEGREE);
     }
    }
    position++;
    wall_allignment();
    move_straight('F',20000); //30cm forward            **CONFIGURE 
    
    if(Base ==1)
    {
        turn('R',R_DEGREE);
    }
    if (Base == 2)
    {
        turn('L',L_DEGREE);
    }
    
    while(temp == 0)
      {
        if (obstacle1==0||obstacle2==0)
        {
        motorcontrl('F');
        }
        else if (obstacle1==1||obstacle2==0)
        {
         motorcontrl('S');
         temp =1;
        }
        
        while (S1_Echo_Read() == 0){
		S1_Trigger_Write(1);
		CyDelayUs(10);
		S1_Trigger_Write(0);
	    }
	    CyDelay(10);
        while (S2_Echo_Read() == 0){
		S2_Trigger_Write(1);
		CyDelayUs(10);
		S2_Trigger_Write(0);
	    }
	    CyDelay(10);
    }
    
    //move_straight('B',4000);
    state++;
}

//Sorting the Puck Based On the color
void sortPuck(){
    int color; //1-RED,2-GREEN,3-BLUE
    color =color_sense();
    RobotArm_Servo_WriteCompare2(700);//Release the Gripper
    CyDelay(1000);
    RobotArm_Servo_WriteCompare2(500);//Close the Gripper
    move_straight('B',4000);
    switch(color){
        case 1://RED
          RED_LED_Write(1);
          CyDelay(1000);
          RED_LED_Write(0);
          Flicker_Servo_WriteCompare(2500); 
          CyDelay(500);
          Flicker_Servo_WriteCompare(900);
        break;
        case 2://Green
        
          Flicker_Servo_WriteCompare(1600);
          CyDelay(500);
          Flicker_Servo_WriteCompare(900);
        break;
        case 3://Blue
          BLUE_LED_Write(1);
          CyDelay(1000);
          BLUE_LED_Write(0);
          Flicker_Servo_WriteCompare(1800);
          CyDelay(500);
          Flicker_Servo_WriteCompare(900);
        break;
        default:
        break;
    }
    state++;
}

//Goes Back to Puck Collecting Zone
void back2Zone(int Base,int counter){
    int temp=0;
    int dist_increament=0;
    counter++;
    if ((position%2)==1) //Horizantal
    {
        turn('L',L_DEGREE*2);
        //side_allignment('L');
        move_straight('F',50000); //X Distance
        //side_allignment('L');
        move_straight('F',(dist_increament));
        dist_increament +=GAP;
        if(Base ==1)
        {
        turn('R',R_DEGREE);
        }
        else if (Base == 2)
        {
        turn('L',L_DEGREE);
        }
        wall_allignment();
        move_straight('F',35000);
    }
    if ((position%2)==0) //Vertical
    {
    move_straight('B',5000);
       if(Base ==1)
    {
        turn('L',L_DEGREE);
    }
    else if (Base == 2)
    {
        turn('R',R_DEGREE);
    }
    wall_allignment();
    move_straight('F',85000);//X Distance
    //side_allignment('R');
    move_straight('F',dist_increament);
    //side_allignment('R');
    if(Base ==1)
      {
        turn('L',L_DEGREE);
      }
    else if (Base == 2)
     {
        turn('R',R_DEGREE);
      }
    move_straight('F',35000);//X Distance
    
    }
    state=1;
}
/* [] END OF FILE */