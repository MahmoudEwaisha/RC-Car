
/* PE3 is digital input connected to infrared detection sensor */

#ifndef __OBJECT_DETECTION_SENSOR_H__
#define __OBJECT_DETECTION_SENSOR_H__

// Initialize PE3 as digital input
void OD_Sensor_Init(void);

// return 1 if there is an object and 0 if there is no object
unsigned char OD_Sensor_ObjectDetected(void);

#endif // end of __OBJECT_DETECTION_SENSOR_H__
