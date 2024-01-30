/*
 * THIS CODE HAS NOT BEEN TESTED AND MAY NOT WORK!
 */

#include "stm32g0xx.h"
#include "i2c.h"
#include "uart.h"
#include "mpu6050.h"
#include "timer.h"

#define TIM_PSC 0
#define TIM_ARR 16000000/2

void IMU_sensor_read(void);

uint8_t sendFlag = 0;

MPU6050 sensorData;

int main()
{
	int16_t data;
	UART_Init();
	I2C_Init();
	Timer2Init(TIM_PSC, TIM_ARR);
	EnableTimer(TIM2);

	data = I2C_Read(MPU6050_ADDRESS, MPU6050_WHO_AM_I);
	data = I2C_Read(MPU6050_ADDRESS, MPU6050_POWER_MGMT_1);
	I2C_Write(MPU6050_ADDRESS, MPU6050_POWER_MGMT_1, 0x00);

	data = I2C_Read(MPU6050_ADDRESS, MPU6050_POWER_MGMT_1);

	while(1)
	{
		IMU_sensor_read();
		if(sendFlag)
		{
			printReadings(sensorData);
			sendFlag = 0;
		}

	}
	return 0;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~(1<<0); // Clear UIF update interrupt flag
	sendFlag = 1;
}

void IMU_sensor_read(void){
	int16_t accelx;
	int16_t gyrox;
	int16_t accely;
	int16_t gyroy;
	int16_t accelz;
	int16_t gyroz;

	accelx = I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_L);
	accelx = accelx | (I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H) << 8);
	sensorData.accelx = (float)(accelx) / 16384;
	sensorData.accelx_smooth += SMOOTHING_FACTOR * (sensorData.accelx - sensorData.accelx_smooth);

	accely = I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_L);
	accely = accely | (I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_H) << 8);
	sensorData.accely = (float)(accely) / 16384;
	sensorData.accely_smooth += SMOOTHING_FACTOR * (sensorData.accely - sensorData.accely_smooth);

	accelz = I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_L);
	accelz = accelz | (I2C_Read(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_H) << 8);
	sensorData.accelz = (float)(accelz) / 16384;
	sensorData.accelz_smooth += SMOOTHING_FACTOR * (sensorData.accelz - sensorData.accelz_smooth);

	gyrox = I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_XOUT_L);
	gyrox = gyrox | (I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_XOUT_H) << 8);
	sensorData.gyrox = (float)(gyrox) / 131;
	sensorData.gyrox_smooth += SMOOTHING_FACTOR * (sensorData.gyrox - sensorData.gyrox_smooth);

	gyroy = I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_YOUT_L);
	gyroy = gyroy | (I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_YOUT_H) << 8);
	sensorData.gyroy = (float)(gyroy) / 131;
	sensorData.gyroy_smooth += SMOOTHING_FACTOR * (sensorData.gyroy - sensorData.gyroy_smooth);

	gyroz = I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_L);
	gyroz = gyroz | (I2C_Read(MPU6050_ADDRESS, MPU6050_GYRO_ZOUT_H) << 8);
	sensorData.gyroz = (float)(gyroz) / 131;
	sensorData.gyroz_smooth += SMOOTHING_FACTOR * (sensorData.gyroz - sensorData.gyroz_smooth);

}


