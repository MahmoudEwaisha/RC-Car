

#include "ObjectDetectionSensor.h"
#include "tm4c123gh6pm.h"

/* Initialize PE3 as digital input */
void OD_Sensor_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= 0x00000010;  //Enable clock to PORTE
  delay = SYSCTL_RCGCGPIO_R;        // Delay
	GPIO_PORTE_DIR_R &= ~0x08;        // Set direction on PE3 to input (0)
	GPIO_PORTE_DEN_R |= 0x08;         // Enable digital functionality for PE3
	GPIO_PORTE_AFSEL_R &= ~0x08;      // Diable alternate funcion on PE3
  GPIO_PORTE_AMSEL_R &= ~0x08;      // Disable analog function on PE3
  GPIO_PORTE_PCTL_R &= ~0x08;       // No alternate function [Port control register]
	
	/* PortE Interrupts Enable */
	GPIO_PORTE_IS_R &= ~0x08;      		// Interrupt on PE3 is edge sensitive (0 = edge) [interrupt sense register]
	GPIO_PORTE_IBE_R &= ~0x08;     		// Clear bit in interrupt both edges register so that interrupt is from one edge only (IEV decides) [interrupt both edges]
	GPIO_PORTE_IEV_R &= ~0x08;     		// 0 --> falling edge, 1 --> rising edge.... since 0 means object detected so we set interrupt to be triggered on negative edges [interrupt event register]
	GPIO_PORTE_ICR_R = 0x08;       		// Clear flag .. clear last interrupt request (if exists) [interrupt clear register]
	GPIO_PORTE_IM_R	|= 0x08;       		// Unmask interrupt on PE3 (Enable it)
	NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFFF00F) | 0x00000020;  // Set the priority of interrupt to 1... portE has interrupt 4, so we set bit 5 to one (1<<5)
	NVIC_EN0_R = 0x00000010;       		// Enable interrupt 4 (PortE) -- PORTE has IRQ#4 (interrupt request #4) coresponding to bit 5
}

// return 1 if there is an object and 0 if there is no object
unsigned char OD_Sensor_ObjectDetected(void)
{
	return (unsigned char)((GPIO_PORTE_DATA_R & 0x08) ) ? 0 : 1;
}
