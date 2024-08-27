// mpu6050_i2c.c
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050_i2c.h" // Include its own header file

void mpu6050_reset()
{
    uint8_t reset[] = {REG_PWR_MGMT_1, 0x80};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, reset, 2, false);
    sleep_ms(200);
    uint8_t wake[] = {REG_PWR_MGMT_1, 0x00};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, wake, 2, false);
    sleep_ms(200);
}

void mpu6050_configure()
{
    // Set accelerometer range
    uint8_t accel_config[] = {REG_ACCEL_CONFIG, ACCEL_CONFIG_VALUE};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, accel_config, 2, false);

    // Set gyroscope range
    uint8_t gyro_config[] = {REG_GYRO_CONFIG, GYRO_CONFIG_VALUE};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, gyro_config, 2, false);

    // Set sample rate
    uint8_t sample_rate[] = {REG_SMPLRT_DIV, SAMPLE_RATE_DIV};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, sample_rate, 2, false);
}

void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp)
{
    uint8_t buffer[14];
    uint8_t reg = REG_ACCEL_XOUT_H;
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buffer, 14, false);

    accel[0] = (buffer[0] << 8) | buffer[1];
    accel[1] = (buffer[2] << 8) | buffer[3];
    accel[2] = (buffer[4] << 8) | buffer[5];
    *temp = (buffer[6] << 8) | buffer[7];
    gyro[0] = (buffer[8] << 8) | buffer[9];
    gyro[1] = (buffer[10] << 8) | buffer[11];
    gyro[2] = (buffer[12] << 8) | buffer[13];
}
