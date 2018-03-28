#include "OI.h"

#include <math.h>
#include "utilities.h"

//	This includes all the Command Headers needed for buttons
#define BUTTON_HEADERS
#include "buttons.h"
#undef BUTTON_HEADERS



OI::OI() {
	
	// Create the devices for the GamePads
	m_driverPad   = new Joystick( PAD_DRIVER   );
	m_operatorPad = new Joystick( PAD_OPERATOR );
	
	// Create the buttons and associate commands with them

#define BUTTON_SETUP( btn_name, pad, btn_code, action, cmd, arg  ) \
	btn_name = new JoystickButton( pad, btn_code ); \
	btn_name->action( new cmd( arg ) );
	
#define BUTTON_MORE( btn_name, action, cmd, arg  ) \
	btn_name->action( new cmd( arg ) );

#include "buttons.h"
	
#undef BUTTON_SETUP
	
#undef BUTTON_MORE

}

//	Returns the scaled value of the primary X axis
float OI::driveX()
{
	return scaleAxis(m_driverPad->GetRawAxis( DRV_AXIS_X )); // X axis value
}

//	Returns the scaled, inverted (if necessary) value of the primary Y axis
float OI::driveY()
{
	float ret;
	
	ret = m_driverPad->GetRawAxis( DRV_AXIS_Y ); // Y axis value
	//	The Game pad Y axes go postive DOWN and negative UP... this is backwards
	//	if DRV_AXIS_Yx_INVERT is true, then flip it
	if (DRV_AXIS_Y_INVERT)
		ret = 0 - ret;
	
	return scaleAxis(ret);
}

//	Returns the scaled value of the secondary X axis
float OI::driveX2()
{
	return scaleAxis(m_driverPad->GetRawAxis( DRV_AXIS_X2 )); // X2 axis value
}

//	Returns the scaled, inverted (if necessary) value of the second Y axis
float OI::driveY2()
{
	float ret;
		
	ret = m_driverPad->GetRawAxis( DRV_AXIS_Y2 ); // Y2 axis value
	
	//	The Game pad Y axes go postive DOWN and negative UP... this is backwards
	//	if DRV_AXIS_Yx_INVERT is true, then flip it
	if (DRV_AXIS_Y2_INVERT)
		ret = 0 - ret;
	
	return scaleAxis(ret);
}

// New - Z axis for the Driver (triggers)
float OI::driveZ()
{
	float ret;

	ret = m_driverPad->GetRawAxis( DRV_AXIS_Z ); // RT axis value

	return scaleAxis(ret);
}


// Operators

//	Returns the scaled, inverted (if necessary) value of the primary Y axis
float OI::operatorY()
{
	float ret;
	
	ret = m_operatorPad->GetRawAxis( OPR_AXIS_Y ); // Y axis value
	//	The Game pad Y axes go postive DOWN and negative UP... this is backwards
	//	if DRV_AXIS_Yx_INVERT is true, then flip it
	if (OPR_AXIS_Y_INVERT)
		ret = 0 - ret;
	
	return scaleAxis(ret);
}

//	Returns the scaled, inverted (if necessary) value of the second Y axis
float OI::operatorY2()
{
	float ret;
		
	ret = m_operatorPad->GetRawAxis( OPR_AXIS_Y2 ); // Y2 axis value
	
	//	The Game pad Y axes go postive DOWN and negative UP... this is backwards
	//	if DRV_AXIS_Yx_INVERT is true, then flip it
	if (OPR_AXIS_Y2_INVERT)
		ret = 0 - ret;
	
	return scaleAxis(ret);
}

float OI::operatorZ()
{
	float ret;
	
	ret = m_operatorPad->GetRawAxis( OPR_AXIS_Z ); // Z axis value
	
	return scaleAxis(ret);
}




float OI::scaleAxis( float inp )
{
	const float k = 21;
	const float y = 22;
		
	float filteredInput = fabs(inp);
	
	if (filteredInput < AXIS_FILTER )
		filteredInput = 0.0;

	return (pow( y, filteredInput ) - 1) / k * sign(inp); 
}
