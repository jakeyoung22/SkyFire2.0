#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/* The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
const UINT32 PWM_LEFT_PORT 					= 1;
const UINT32 PWM_RIGHT_PORT 				= 2;
const UINT32 PWM_FRONT_SHOOTER_MOTOR 		= 3;
const UINT32 PWM_MIDDLE_SHOOTER_MOTOR 		= 4;
const UINT32 PWM_BACK_SHOOTER_MOTOR 		= 5;

const UINT32 GPIO_LEFT_ENCODER_A 			= 7;
const UINT32 GPIO_LEFT_ENCODER_B 			= 8;
const UINT32 GPIO_RIGHT_ENCODER_A 			= 9;
const UINT32 GPIO_RIGHT_ENCODER_B 			= 10;

//8
const UINT32 GPIO_FRONT_SHOOTER_ENCODER_A 	= 1;
const UINT32 GPIO_FRONT_SHOOTER_ENCODER_B 	= 2;
//11	

const UINT32 GPIO_PRESSURE 					= 14;

const UINT32 SOL_GEAR_SHIFT_LOW 			= 1;
const UINT32 SOL_GEAR_SHIFT_HIGH 			= 2;
const UINT32 SOL_PUSHER_SHOOT 				= 3;
const UINT32 SOL_PUSHER_RETRACT 			= 4;



const UINT32 ANALOG_DRIVE_GYRO 				= 1;
//const UINT32 ANALOG_DECK_GYRO 			= 2;

const UINT32 RELAY_COMPRESSOR 				= 1;
const UINT32 RELAY_BLING					= 2;
const UINT32 RELAY_CAMERA_LED				= 3;



/*
 * Put some constants here for easy access
 */

//	todo: Set this speed to something tolerable
#define MOTOR_SPEED_MAX		1000.0f

//	Shooter speed in our output units.  THIS NEEDS TO BE DETERMINED
//	BY OBSERVATION.  I'm guessing we'll use RPS as our output units.
#define SHOOTER_FRONT_ENC_CPR 32.0f
//	
#define SHOOTER_SPEED_FRONT   (SHOOTER_SPEED_MAX * 0.85)
//	Speed step down from Front to middle, and again from middle to back
#define SHOOTER_SPEED_FACTOR 0.99
//	Maximum observed shooter speed
#define SHOOTER_SPEED_MAX	115
//	Time that the disc pusher should remain forward after pushing
#define SHOOTER_PUSHER_WAIT_TIME 0.3f //was 0.9f
//	Time that we should wait for the motors to spin up, if we can't use the encoder
#define SHOOTER_SPINUP_WAIT_TIME 1.5f
//	Speed at or over which OkayToShoot() should return TRUE
#define SHOOTER_OKAY_TO_SHOOT 90
//	If the PID loop isn't working, use this power setting to spin the wheels
#define SHOOTER_RAW_SPEED  .95f
//  Slow speed for pyramid shot without PID
#define SHOOTER_SLOW_SPEED 0.8f
//	When allowing a speed stepping, incr by this.  Don't think is used.
#define SHOOTER_SPEED_INCREMENT 0.10f
//	Notes:
//	RPM of motor ~5000, 1.45 gearing ratio, 32 encoder clicks per revolution

//	todo: Set the lift speed to a reasonable amount
const float  SECONDARY_LIFT_SPEED = 0.5;

const float DECK_ANGLE_TOLERANCE = 1.2f;
#define DECK_ANGLE_BOTTOM 0
#define DECK_ANGLE_TOP 46
#define DECK_ANGLE_FLOORLOAD  10
//	Angle at which we shoot unless adjusted
#define DECK_ANGLE_SHOOTING  45
//	Increment by which the shooting angle can be adjusted
#define DECK_ANGLE_INCREMENT 2.0
//	Angle to raise deck to so the prop will drop out.  Note that this is actually
//	the angle above where the deck starts propped up at, because when we power up
//	the encoder thinks it's at 0.  We could override this behavior, by creating
//	a decendant class of the Encoder, or otherwise added the propped angle to 
//	our calculations if we start up with the deck swich registering false, until
//	the deck switch registers true.  I might talk myself into this.
#define DECK_ANGLE_DROP_PROP  70
#define PROPPED_DECK_ANGLE 49

const float DECK_STALL_SPEED = 0.225;	// SILVER: 0.20;
const float DECK_MOTOR_ASCENT_SPEED = 0.7;
const float DECK_MOTOR_DESCENT_SPEED = 0.07;

const float DRV_DIST_PER_PULSE = 8.0 * 3.1415926358979323846264338 / 360;
//	circ = D * PI, 4 Inch dia

const float DRIVE_NUDGE_TIME = 0.2f;

//	Setting this to true disables all the SmartDashboard calls to send data
//	to the smart dashboard.
#define SDMD true

//	Turn on PID in Shooter
#define PID  false

//	Enable the watchdog timer on all motors?
#define SAFETY_ENABLED false

#endif
