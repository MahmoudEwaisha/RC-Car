
#include "tm4c123gh6pm.h"
#include "PWM.h"

void PWM_INIT(void){

	/* PWM0 Generator0 [GENA(PWM0)-->PB6,   GENB(PWM1)-->PB7] */ 
	/* PWM0 Generator1 [GENA(PWM2)-->PB4,   GENB(PWM3)-->PB5] */
	
	SYSCTL_RCGCPWM_R |= 1;            // Enable clock to PWM module 0 (containg Generator 0,1,2,3 and each generator has 2 output pins)
	SYSCTL_RCC_R &= ~0x00100000;      // No predivide to pwm clock (USEPWMDIVin RCC register = 0)
	
	
	/* GENERATOR 0  GENA(PWM0 pin) ---> PB6 ... GENB(PWM1 pin) ---> PB7 */
	PWM0_0_CTL_R = 0;                 // PWM0 Generator0 (PWM0-->PB6, PWM1-->PB7) STOP COUNTER
	PWM0_0_GENA_R  = 0x0000008C;	    // M0PWM0 set when reload, clear when match CMPA while counting down
	PWM0_0_GENB_R  = 0x0000080C;      // M0PWM1 set when reload, clear when match CMPB while counting down
	PWM0_0_LOAD_R = 16000;      
  //PWM0_0_CMPA_R = 0; //PB6
	//PWM0_0_CMPB_R = 0; //PB7
	

	/* GENERATOR 1  GENA(PWM2 pin) ---> PB4 ... GENB(PWM3 pin) ---> PB5 */
	PWM0_1_CTL_R = 0;                 // PWM0 Generator1 (PWM2-->PB4, PWM3-->PB5)  STOP COUNTER
	PWM0_1_GENA_R  = 0x0000008C;	    // M0PWM2 set when reload, clear when match CMPA while counting down
	PWM0_1_GENB_R  = 0x0000080C;      // M0PWM3 set when reload, clear when match CMPB while counting down
	PWM0_1_LOAD_R = 16000;      
	//PWM0_1_CMPA_R = 0; //PB4
	//PWM0_1_CMPB_R = 0; //PB5
	
	PWM0_0_CTL_R = 1;                // PWM0 Generator 0 start counter
	PWM0_1_CTL_R = 1;                // PWM0 Generator 1 start counter
	//PWM0_ENABLE_R = 0x0C;          // Enable PWM0 channel 2&3
}

void PORTB_INIT(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x02;         // Clock to PORTB
	delay = SYSCTL_RCGCGPIO_R;         // Delay
	
	GPIO_PORTB_DIR_R |= 0xF0;          // PA4,5,6,7 ---> Output
	GPIO_PORTB_AFSEL_R = 0xF0;         // Enable alternate function to PB4,5,6,7
	GPIO_PORTB_PCTL_R &= ~0xFFFF0000;  // make PB4,5,6,7 PWM output pins
	GPIO_PORTB_PCTL_R |= 0x44440000;
	GPIO_PORTB_DEN_R |= 0xF0;          // Digital enable
	
}


void forward(void)
{     
		PWM0_0_CMPA_R = 0x00 ;					// PB6
		PWM0_1_CMPA_R = 0x00;						// PB4
		Clr_Bit(GPIO_PORTB_DATA_R,7);
		Clr_Bit(GPIO_PORTB_DATA_R,5);
		PWM0_ENABLE_R = 0x05; 					// PWM0 (PB6) & PWM2 (PB4)
}
void backward(void)
{  
		PWM0_0_CMPB_R = 0x00;						// PB7
		PWM0_1_CMPB_R = 0x00;						// PB5
		Clr_Bit(GPIO_PORTB_DATA_R,6);
		Clr_Bit(GPIO_PORTB_DATA_R,4);
		PWM0_ENABLE_R = 0x0A; 					// PWM1 (PB7) & PWM3 (PB5)
}
void right(void)
{  
		PWM0_1_CMPA_R = 0x00;						// PB4
		Clr_Bit(GPIO_PORTB_DATA_R,5);
		Clr_Bit(GPIO_PORTB_DATA_R,6);
		Clr_Bit(GPIO_PORTB_DATA_R,7);
		PWM0_ENABLE_R = 0x04; 					// PB4
}
void left(void)
{  
		PWM0_0_CMPA_R = 0x00 ;					// PB6
		Clr_Bit(GPIO_PORTB_DATA_R,4);
		Clr_Bit(GPIO_PORTB_DATA_R,5);
		Clr_Bit(GPIO_PORTB_DATA_R,7);
		PWM0_ENABLE_R = 0x01; 					// PB6
}
void forward_left(void)
{ 
		PWM0_0_CMPA_R = 0; 							// PB6
		PWM0_1_CMPA_R = 15000;					// PB4
		Clr_Bit(GPIO_PORTB_DATA_R,7);
		Clr_Bit(GPIO_PORTB_DATA_R,5);
		PWM0_ENABLE_R = 0x05; 					// PWM0 (PB6) & PWM2 (PB4)
}
void forward_right(void)
{
		PWM0_0_CMPA_R = 15000; 					// PB6
		PWM0_1_CMPA_R = 0x00;						// PB4
		Clr_Bit(GPIO_PORTB_DATA_R,7);
		Clr_Bit(GPIO_PORTB_DATA_R,5);
		PWM0_ENABLE_R = 0x05; 					// PWM0 (PB6) & PWM2 (PB4)
}
void backward_right(void)
{
		PWM0_0_CMPB_R = 15000;					// PB7
		PWM0_1_CMPB_R = 0x00;						// PB5
		Clr_Bit(GPIO_PORTB_DATA_R,6);
		Clr_Bit(GPIO_PORTB_DATA_R,4);
		PWM0_ENABLE_R = 0x0A; 					// PWM1 (PB7) & PWM3 (PB5)
}

void backward_left (void)
{
		PWM0_0_CMPB_R = 0x00;      			// PB7
		PWM0_1_CMPB_R = 15000;   				// PB5
		Clr_Bit(GPIO_PORTB_DATA_R,6);
		Clr_Bit(GPIO_PORTB_DATA_R,4);
		PWM0_ENABLE_R = 0x0A; 					// PWM1 (PB7) & PWM3 (PB5)
}

void stop(void)
{
		PWM0_ENABLE_R = 0x00; 					// Disable all PWM
		Clr_Hnibble(GPIO_PORTB_DATA_R);
}
		

