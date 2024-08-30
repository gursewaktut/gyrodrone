// kalman.h
#ifndef KALMAN_H
#define KALMAN_H

typedef struct {
    float angle;    // The angle calculated by the Kalman filter - part of the 2x1 state matrix
    float bias;     // The gyro bias calculated by the Kalman filter - part of the 2x1 state matrix
    float rate;     // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
    float P[2][2];  // Error covariance matrix - This is a 2x2 matrix
} Kalman;

void kalman_init(Kalman *kalman);
float kalman_get_angle(Kalman *kalman, float new_angle, float new_rate, float dt);

#endif // KALMAN_H
