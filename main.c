
#include "tm4c123gh6pm.h"
#include "ObjectDetectionSensor.h"
#include "Bluetooth.h"
#include "PWM.h"

void SystemInit(void){}
	
unsigned long In;
	
	
void GPIOE_Handler(void)
{
	if(GPIO_PORTE_RIS_R & 0x08) // Check if interrupt reason is PE3     ***eh el far2 ben RIS (Raw interrupt status) we MIS (Masked interrupt status) ???
	{ 
			GPIO_PORTE_ICR_R = 0x08; // Acknowledge that the interrupt is handled [interrupt clear register]
		
			PWM0_ENABLE_R = 0x00;
			Set_Hnibble(GPIO_PORTB_DATA_R); // Stop all motors
			while(OD_Sensor_ObjectDetected()) // Wait till object is moved
			{
				if(Bluetooth_Available())
				{
					In = Bluetooth_Read();
					if(In == 'B')backward();
					else if(In == 'J')backward_right();
					else if(In == 'H')backward_left();
					else stop();
				}
			}
	 }
}


int main(void)
{
	PORTB_INIT();
	PWM_INIT();
	OD_Sensor_Init();
	
	while(1)
	{
		Bluetooth_Init();
		if(Bluetooth_Available()) In = Bluetooth_Read();

		
		switch(In)
		{
			case 'F':
				forward();
				break;
			
			case 'B':
				backward();
				break;
			
			case 'L':
				left();
				break;
			
			case 'R':
				right();
				break;
			
			case 'G':
				forward_left();
				break;
			
			case 'I':
				forward_right();
				break;
			
			case'J':
				backward_right();
				break;
			
			case'H':
				backward_left();
				break;
			
			default:
				stop();
				break;	
		}
	}
}
