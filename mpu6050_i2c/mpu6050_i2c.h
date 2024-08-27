// mpu6050_i2c.h
#ifndef MPU6050_I2C_H
#define MPU6050_I2C_H

#include <stdint.h>
#include "math.h"

// I2C defines
#define I2C_PORT i2c0
#define MPU6050_ADDR 0x68

// MPU6050 register addresses
#define REG_PWR_MGMT_1 0x6B
#define REG_ACCEL_XOUT_H 0x3B
#define REG_GYRO_CONFIG 0x1B
#define REG_ACCEL_CONFIG 0x1C
#define REG_SMPLRT_DIV 0x19
#define WHO_AM_I_REG 0x75

// Sensitivity scale factors
#define ACCEL_SCALE_FACTOR_2G 16384.0
#define ACCEL_SCALE_FACTOR_4G 8192.0
#define ACCEL_SCALE_FACTOR_8G 4096.0
#define ACCEL_SCALE_FACTOR_16G 2048.0

#define GYRO_SCALE_FACTOR_250DPS 131.0
#define GYRO_SCALE_FACTOR_500DPS 65.5
#define GYRO_SCALE_FACTOR_1000DPS 32.8
#define GYRO_SCALE_FACTOR_2000DPS 16.4

// Selected scale factors
#define ACCEL_SCALE_FACTOR ACCEL_SCALE_FACTOR_4G
#define GYRO_SCALE_FACTOR GYRO_SCALE_FACTOR_250DPS

// Corresponding configuration values
#define ACCEL_CONFIG_VALUE 0x08 // for ±4g
#define GYRO_CONFIG_VALUE 0x00  // for ±250 degrees per second
#define SAMPLE_RATE_DIV 1       // Sample rate = 1kHz / (1 + 1) = 500Hz

// Function declarations
void mpu6050_reset();
void mpu6050_configure();
void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp);

#endif // MPU6050_I2C_H
