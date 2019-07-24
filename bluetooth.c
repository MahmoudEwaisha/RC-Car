
#include "Bluetooth.h"
#include "tm4c123gh6pm.h"

void Bluetooth_Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;	// Provide clock to UART module 3
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;	// Enable clock to PORTC
	UART3_CTL_R &= ~UART_CTL_UARTEN;       		// Disable UART
  UART3_IBRD_R = 104;                    		// IBRD = int(16,000,000 / (16 * 9,600)) = int(104.16666666666667)
  UART3_FBRD_R = 11;                     		// FBRD = int(0.16666666666667 * 64 + 0.5) = 11
	
																						// 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART3_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);// Set bits 5 and 6 to indecate 8bit transition ,set bit 4 to enable fifo
	UART3_CTL_R |= UART_CTL_UARTEN;        		// Enable UART
  GPIO_PORTC_AFSEL_R |= 0xC0;            		// Enable alt funct on PC7 and PC6
	GPIO_PORTC_DEN_R |= 0xC0;              		// Enable digital I/O on PC7 and PC6
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000; 	// configure PC7 and PC6 as UART
  GPIO_PORTC_AMSEL_R &= ~0xC0;           		// Disable analog functionality on PC7 and PC6
}

/* return 1 if there a char recieved and 0 if no character is recieved */
unsigned char Bluetooth_Available(void){
	return !(UART3_FR_R&UART_FR_RXFE); 				// Make mask to see the empty flag in the flag register
	/* When RXFE is low, means fifo buffer is not empty ---> there is new data recieved waiting to be read from the data register */
}

unsigned char Bluetooth_Read(void){
  return((unsigned char)(UART3_DR_R&0xFF));
	/* Return data in the data register */
}


