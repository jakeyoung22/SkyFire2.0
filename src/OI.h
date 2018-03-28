#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	
#include "oimap.h"

	Joystick *m_driverPad, *m_operatorPad;
	
#define BUTTON_SETUP( btn_name, pad, btn_code, action, cmd, arg ) \
	JoystickButton *btn_name;

#define BUTTON_MORE(a, b, c, d) ;
	
#include "buttons.h"
	
#undef BUTTON_SETUP
#undef BUTTON_MORE

public:
	OI();
	
	float driveX();	// X axis value
	float driveY();	// Y axis value
	float driveX2();	// X axis value on second X/Y stick
	float driveY2();	// Y axis value on second X/Y stick
	float driveZ();		// Z axis value

	float operatorY();	// Y axis value
	float operatorY2();	// Y axis value on second X/Y stick
	float operatorZ();	// Z axis value

	

	
	static float scaleAxis( float inp );
};

#endif
