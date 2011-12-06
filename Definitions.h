// Global definitions

// Speeds are in microseconds, not degrees, for greater control
#define MIN_MOTOR_SPEED 1000
#define MAX_MOTOR_SPEED 2000

#define LEFT_FRONT_MOTOR_PIN 11
#define RIGHT_FRONT_MOTOR_PIN 3
#define LEFT_REAR_MOTOR_PIN 10
#define RIGHT_REAR_MOTOR_PIN 9

#define LEFT_FRONT_MOTOR 0
#define RIGHT_FRONT_MOTOR  1
#define LEFT_REAR_MOTOR 2
#define RIGHT_REAR_MOTOR 3

#define GYRO_ADDR 0x68
#define ACCEL_ADDR 0x53
//#define BARO_ADDR 0x77
//#define MAG_ADDR 0x1E

#define ROLL 0
#define PITCH 1
#define YAW 2

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

//#define SERIAL_RATE 1000 // How long between running the serial code, in microseconds?

// Measured raw accel values by putting the quadcopter on all 6 sides
#define MAX_ACCEL_ROLL 269
#define MAX_ACCEL_PITCH 268
#define MAX_ACCEL_YAW 0

#define MIN_ACCEL_ROLL -271
#define MIN_ACCEL_PITCH -260
#define MIN_ACCEL_YAW 510

// Receiver
//#define CHANNELS 6
//#define THROTTLE_CHANNEL 0
//#define YAW_CHANNEL 1
//#define PITCH_CHANNEL 2
//#define ROLL_CHANNEL 3
//#define GEAR_CHANNEL 4
//#define AUX_CHANNEL 5

// Battery monitor
//#define BATTERY_PIN 0 // This is the same on every arduino
//#define BATTERY_R1 14560.0 // 15k resistor measured with a multimeter, must be a float!
//#define BATTERY_R2 7390.0 // 7.5k resistor measured with a multimeter, must be a float!
//#define BATTERY_AREF 5.0 // Arduino Mega runs at 5v
//#define BATTERY_DIODE 0.9 // On-board diode, measured with a multimeter
//#define ALARM_VOLTAGE 9.0

