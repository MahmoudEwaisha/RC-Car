

#ifndef __PWM_H__
#define __PWM_H__

/* Macros */
#define Clr_Bit(reg,bit_no)       				reg&=~(1<<bit_no)
#define Set_Hnibble(reg)                  reg|=0xF0
#define Clr_Hnibble(reg)               	  reg&=0x0F

void PWM_INIT(void);
void PORTB_INIT(void);
void forward(void);
void backward(void);
void right(void);
void left(void);
void forward_left(void);
void forward_right(void);
void backward_right(void);
void backward_left (void);
void stop(void);

		
#endif
