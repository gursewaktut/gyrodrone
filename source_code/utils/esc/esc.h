/******************************************************************************

esc.h
TB6612FNG H-Bridge Motor Driver for gyro drone

Resources:
TB6612 SparkFun Library

Developed for pico-sdk
******************************************************************************/


#ifndef esc_h
#define esc_h

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255  

typedef struct{
    int input_pin1;
    int input_pin2;
    int pwm_pin;
    int stdby_pin;
    int offset;
}Motor;

/*
 * initialize the pins for motor
 */
void esc_init(Motor *motor, int input_pin1, int input_pin2, int pwm_pin, int stdby_pin, int offset);

/* Drive in direction given by sign, at speed given by magnitude of the 
 *parameter.
 */
void drive(Motor *motor, int speed);

/*
 * drive(), but with a delay(duration)
 */
void drive(Motor *motor, int speed, int duration);  


/*
 * Stops motor by setting both input pins high
 */
void brake(Motor *motor); 

/*
 *set the chip to standby mode.  The drive function takes it out of standby 
 *forward, back, left, and right all call drive)
 */
void standby(Motor *motor);	


/*
 * functions that spin the motor CC and CCW
 *
 */
void fwd(Motor *motor, int speed);
void rev(Motor *motor, int speed);


#endif
