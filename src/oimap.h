#ifndef OIMAP_H
#define OIMAP_H
/*+
 * OI MAP - contains the constants to tell us where the OI devices are
 * (similar to RobotMap's defining of the on-robot elements)
 * 
 * "static" because I've elected to include these in the OI class so they can't leak out
 * 
 * If they have to leak out, we'll keep them in class, but make them public instead of private.
 * Why am I not doing this with the Robotmap consts?  I might yet.
 */

#include "xb360map.h"

const static UINT32 PAD_DRIVER   = 1;
const static UINT32 PAD_OPERATOR = 2;

//	All scaled axes use this filter value.  If the absolute value of the axis value
//	is less than this number, then it is set to zero.  This is a noise filter because
//	the joysticks don't return to zero real well.
const static float  AXIS_FILTER = 0.04;

const static UINT32 DRV_AXIS_X = XB360_AXIS_LEFT_X;
const static UINT32 DRV_AXIS_Y = XB360_AXIS_LEFT_Y;
const static bool   DRV_AXIS_Y_INVERT = true;	// Reverses the sign of the vertical axis

const static UINT32 DRV_AXIS_X2 = XB360_AXIS_RIGHT_X;
const static UINT32 DRV_AXIS_Y2 = XB360_AXIS_RIGHT_Y;
const static bool   DRV_AXIS_Y2_INVERT = true;	// Reverses the sign of the vertical axis

const static UINT32 DRV_AXIS_Z  = XB360_AXIS_TRIGGER;

const static UINT32 OPR_AXIS_Y = XB360_AXIS_LEFT_Y;
const static bool   OPR_AXIS_Y_INVERT = true;	// Reverses the sign of the vertical axis

const static UINT32 OPR_AXIS_Y2 = XB360_AXIS_RIGHT_Y;
const static bool   OPR_AXIS_Y2_INVERT = true;	// Reverses the sign of the vertical axis

const static UINT32 OPR_AXIS_Z  = XB360_AXIS_TRIGGER;

//const static UINT32 OPR_AXIS_X3 = XB360_AXIS_DPAD_X;	// Not currently used


//const static UINT32 OPR_BTN_SHOOTER_SHOOT = XB360_BUMPER_LEFT;
//const static UINT32 OPR_BTN_DECK_CYCLE = XB360_BUMPER_RIGHT;
//const static UINT32 OPR_BTN_PRIMARY_LIFT = XB360_Y;
//const static UINT32 OPR_BTN_DECK_STALL = XB360_LEFT_STICK;
//const static UINT32 OPR_BTN_ANGLE_UP	 =	XB360_START;
//const static UINT32 OPR_BTN_ANGLE_DOWN   =	XB360_BACK;
//const static UINT32 OPR_BTN_PUSHER_RETRACT = XB360_A;
//const static UINT32 OPR_BTN_JOG_DECK = XB360_X;

//const static UINT32 DRV_BTN_SCOOT_BCK = XB360_A;
//const static UINT32 DRV_BTN_SCOOT_FWD = XB360_Y;
const static UINT32 DRV_BTN_GEAR_SHIFT = XB360_BUMPER_RIGHT;
const static UINT32 DRV_BTN_SHOOTER_ON = XB360_BACK;
const static UINT32 DRV_BTN_CLEAR_JAM = XB360_X;
//const static UINT32 DRV_BTN_SHOOTER_SPEED_TOGGLE = XB360_START;
const static UINT32 DRV_BTN_AIMBOT = XB360_START;
//const static UINT32 DRV_BTN_SECONDARY_CLIMB = XB360_A;
//const static UINT32 DRV_BTN_SECONDARY_OUT = XB360_X;
//const static UINT32 DRV_BTN_SECONDARY_TOP_ARMS = XB360_BACK;
const static UINT32 DRV_BTN_SHOOTER_SHOOT = XB360_BUMPER_LEFT;
const static UINT32 DRV_BTN_CHANGE_MODE	  = XB360_Y;
//const static UINT32 DRV_BTN_PUSHER_RETRACT = XB360_B;
const static UINT32 DRV_BLING_TOGGLE			= XB360_A;
const static UINT32 DRV_BLING_ON_TOGGLE			= XB360_B;

//const static UINT32 DRV_BTN_SHOOTER_BARS_TOGGLE = XB360_BUMPER_LEFT;

#endif
