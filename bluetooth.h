

#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

void Bluetooth_Init(void);

unsigned char Bluetooth_Available(void);

unsigned char Bluetooth_Read(void);

void Bluetooth_Write(unsigned char data);

#endif // end of __DC_MOTOR_H__
