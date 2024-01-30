/*
 * mpu6050.c
 *
 *  Created on: Jan 31, 2024
 *      Author: erhangok
 */

#include "mpu6050.h"
#include "uart.h"
#include "stdlib.h"

/*
 * 	float accelx_smooth;
	float accely_smooth;
	float accelz_smooth;
	float gyrox_smooth;
	float gyroy_smooth;
	float gyroz_smooth;
 */

void printReadings(MPU6050 readings)
{
    char buffer[20]; // Adjust the size as needed

    // Print each reading
    print("accelx: ");
    itoa((int)readings.accelx_smooth, buffer, 10);
    println(buffer);

    print("accely: ");
    itoa((int)readings.accely_smooth, buffer, 10);
    println(buffer);

    print("accelz: ");
    itoa((int)readings.accelz_smooth, buffer, 10);
    println(buffer);

    print("gyrox: ");
    itoa((int)readings.gyrox_smooth, buffer, 10);
    println(buffer);

    print("gyroy: ");
    itoa((int)readings.gyroy_smooth, buffer, 10);
    println(buffer);

    print("gyroz: ");
    itoa((int)readings.gyroz_smooth, buffer, 10);
    println(buffer);
}






