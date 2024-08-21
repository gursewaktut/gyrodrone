/* 
 * MPU6050.h
 *
 * Created on Aug 20, 2024
 * 	Author: Pardeep
 *
 * Description:
 * 	6 DOF(3 axis Gyro + 3 axis Accelerometer) sensor Module
 *
 * Model:
 * 	GY-521
 *
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------*/
#include "main.h"

/* Global Variables ----------------------------------------------------*/



/* Global Function Prototypes ------------------------------------------*/

extern void MPU6050_Init();
extern void MPU6050_AccelGetXYZ(int8_t *pData);
extern void MPU6050_GyroGetXYZ(int8_t *pData);



#ifdef __cplusplus
}
#endif


#endif /* INC_MPU6050_H_
