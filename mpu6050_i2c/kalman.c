// kalman.c
#include "kalman.h"
#include "math.h"

// Define and initialize Kalman filter tuning parameters
static float Q_angle;   // Process noise covariance for the angle
static float Q_bias;    // Process noise covariance for the gyroscope bias
static float R_measure; // Measurement noise covariance

void kalman_init(Kalman *kalman)
{
    kalman->angle = 0.0;
    kalman->bias = 0.0;
    kalman->rate = 0.0;
    kalman->P[0][0] = 0.0;
    kalman->P[0][1] = 0.0;
    kalman->P[1][0] = 0.0;
    kalman->P[1][1] = 0.0;
}

float kalman_get_angle(Kalman *kalman, float new_angle, float new_rate, float dt)
{
    // Predict the rate
    kalman->rate = new_rate - kalman->bias;
    kalman->angle += dt * kalman->rate;

    // Update the estimation error covariance - Project the error covariance ahead
    kalman->P[0][0] += dt * (dt * kalman->P[1][1] - kalman->P[0][1] - kalman->P[1][0] + Q_angle);
    kalman->P[0][1] -= dt * kalman->P[1][1];
    kalman->P[1][0] -= dt * kalman->P[1][1];
    kalman->P[1][1] += Q_bias * dt;

    // Calculate Kalman gain - Compute the Kalman gain
    float S = kalman->P[0][0] + R_measure;
    float K[2]; // Kalman gain - This is a 2x1 vector
    K[0] = kalman->P[0][0] / S;
    K[1] = kalman->P[1][0] / S;

    // Update the angle and bias - Update estimate with measurement zk (new_angle)
    float y = new_angle - kalman->angle; // Angle difference
    kalman->angle += K[0] * y;
    kalman->bias += K[1] * y;

    // Update the estimation error covariance - Update the error covariance
    float P00_temp = kalman->P[0][0];
    float P01_temp = kalman->P[0][1];

    kalman->P[0][0] -= K[0] * P00_temp;
    kalman->P[0][1] -= K[0] * P01_temp;
    kalman->P[1][0] -= K[1] * P00_temp;
    kalman->P[1][1] -= K[1] * P01_temp;

    return kalman->angle;
}
