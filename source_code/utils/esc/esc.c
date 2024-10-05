/******************************************************************************

esc.h
TB6612FNG H-Bridge Motor Driver for gyro drone

Resources:
TB6612 SparkFun Library

Developed for pico-sdk
******************************************************************************/

#include "esc.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

/*
 * initialize the pins for motor
 */
void esc_init(Motor *motor, int input_pin1, int input_pin2, int pwm_pin, int stdby_pin, int offset) {

    motor->input_pin1 = input_pin1;
    motor->input_pin2 = input_pin2;
    motor->pwm_pin = pwm_pin;
    motor->stdby_pin = stdby_pin;
    motor->offset = offset;

    gpio_init(motor->input_pin1);
    gpio_init(motor->input_pin2);
    gpio_init(motor->pwm_pin);
    gpio_init(motor->stdby_pin);
    gpio_set_function(motor->pwm_pin, GPIO_FUNC_PWM);
}

/*
 * Drive in direction given by sign, at speed given by magnitude of the 
 * parameter.
 */
void drive(Motor *motor, int speed) {
    gpio_pull_up(HIGH);
    speed = speed * motor->offset;
    if (speed>=0) fwd(speed);
    else rev(-speed);
}

/*
 * drive(), but with a delay(duration)
 */
void drive(Motor *motor, int speed, int duration) {
    drive(speed);
    delay(duration);
    brake(motor);
}

/*
 * functions that spin the motor CW
 */
void fwd(Motor *motor, int speed) {
    gpio_pull_up(motor->input_pin1);
    gpio_pull_down(motor->input_pin2);
    analogWrite(PWM, speed);
}

/*
 * functions that spin the motor CCW
 */
void rev(Motor *motor, int speed) {
    digitalWrite(motor->input_pin1, LOW);
    digitalWrite(motor->input_pin2, HIGH);
    analogWrite(motor->pwm_pin, speed);
}

/*
 * Stops motor by setting both input pins high
 */
void brake(Motor *motor) {
    digitalWrite(motor->input_pin1, HIGH);
    digitalWrite(motor->input_pin2, HIGH);
    analogWrite(motor->pwm_pin,0);
}

/*
 *set the chip to standby mode.  The drive function takes it out of standby 
 *forward, back, left, and right all call drive)
 */
void standby(Motor *motor) {
    digitalWrite(motor->stdby_pin, LOW);
}

