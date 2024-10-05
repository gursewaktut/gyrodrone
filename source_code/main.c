// main.c
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "math.h"
#include "mpu6050_i2c.h"
#include "kalman.h"
#include "wifi.h"
#include "esc.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef WIFI_AP_NAME
#define WIFI_AP_NAME "gyrodrone"
#define WIFI_AP_PASS "gyrodrone"
#endif

#define AIN1 20
#define AIN2 21
#define BIN1 19
#define BIN2 18
#define PWMA 8
#define PWMB 9
#define STBY 16

Motor motor1, motor2; 

int main()
{
    // Initialize chosen serial port
    stdio_init_all();

    wifi_setup();
    start_ap();

    // set up the esc motor controller
    esc_init(&motor1, AIN1, AIN2, PWMA, STBY);

    drive(&motor1, 100)


    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Reset and configure MPU6050
    mpu6050_reset();
    mpu6050_configure();

    uint8_t who_am_i = 0;
    uint8_t reg = WHO_AM_I_REG;
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, &who_am_i, 1, false);
    printf("MPU6050 WHO_AM_I: 0x%02X\n", who_am_i);

    if (who_am_i != 0x68)
    {
        printf("MPU6050 not found!\n");
        while (1)
            ;
    }

    int16_t accel[3], gyro[3], temp;
    Kalman kalman_x, kalman_y;
    kalman_init(&kalman_x);
    kalman_init(&kalman_y);

    float dt = 0.01; // Assume a fixed time step for now (10 ms)
    while (1)
    {
        mpu6050_read_raw(accel, gyro, &temp);

        // Convert raw accelerometer values to g
        float accel_g[3];
        accel_g[0] = accel[0] / ACCEL_SCALE_FACTOR;
        accel_g[1] = accel[1] / ACCEL_SCALE_FACTOR;
        accel_g[2] = accel[2] / ACCEL_SCALE_FACTOR;

        // Convert raw gyroscope values to degrees per second
        float gyro_dps[3];
        gyro_dps[0] = gyro[0] / GYRO_SCALE_FACTOR;
        gyro_dps[1] = gyro[1] / GYRO_SCALE_FACTOR;
        gyro_dps[2] = gyro[2] / GYRO_SCALE_FACTOR;

        // Calculate roll and pitch from accelerometer data
        float accel_angle_x = atan2f(accel_g[1], accel_g[2]) * 180 / M_PI;
        float accel_angle_y = atan2f(-accel_g[0], accel_g[2]) * 180 / M_PI;

        // Use Kalman filter to combine accelerometer and gyroscope data
        float kalman_angle_x = kalman_get_angle(&kalman_x, accel_angle_x, gyro_dps[0], dt);
        float kalman_angle_y = kalman_get_angle(&kalman_y, accel_angle_y, gyro_dps[1], dt);

        // Print the Kalman-filtered angles
        printf("Kalman X = %.2f° | Kalman Y = %.2f°\n", kalman_angle_x, kalman_angle_y);

        sleep_ms(10); // 10ms delay corresponds to 100Hz loop rate
    }

    return 0;
}
