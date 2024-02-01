/*
 * mpu6050.h
 *
 *  Created on: Jan 30, 2024
 *      Author: erhangok
 *
 *      This header file contains reigster adresses of MPU6050 sensor
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32g0xx.h"

#define MPU6050_ADDRESS 0x68

#define MPU6050_WHO_AM_I 0x75
#define MPU6050_POWER_MGMT_1 0x6B

// ACCELEROMETER REGISTER ADDRESS
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C

#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E

#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

// GYRO REGISTER ADDRESS
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44

#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46

#define MPU6050_GYRO_ZOUT_H 0x47
#define MPU6050_GYRO_ZOUT_L 0x48

#define SMOOTHING_FACTOR 0.001

typedef struct{
	float accelx;
	float accely;
	float accelz;
	float gyrox;
	float gyroy;
	float gyroz;

	float accelx_smooth;
	float accely_smooth;
	float accelz_smooth;
	float gyrox_smooth;
	float gyroy_smooth;
	float gyroz_smooth;
}MPU6050;

void printReadings(MPU6050 readings);

#endif /* MPU6050_H_ */
