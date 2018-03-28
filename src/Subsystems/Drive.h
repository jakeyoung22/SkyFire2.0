#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @author 1319
 */
class Drive: public Subsystem {
public:
	enum e_gear { unknown=0, low=1, high=2};
	enum e_mode { arcade=0, tank=1, climb=2 };
	
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	e_gear m_gear;
	e_mode m_mode;
	
	DoubleSolenoid *m_solGear;
	
	Victor *m_left, *m_right;
	RobotDrive *m_drive;
	
	Encoder *m_leftEncoder, *m_rightEncoder;
	Gyro *m_driveGyro;
	
	Command *m_CmdArcade, *m_CmdTank, *m_CmdClimb;
	
public:
	Drive();
	void InitDefaultCommand();
	
	//	Properties
	
	float Heading();		// Returns the Gyro heading
	float SpeedLeft();		// Returns the speed of left wheels in IPS
	float SpeedRight();		// Returns the speed of the right wheels in IPS
	float DistLeft();
	float DistRight();
	
	Drive::e_gear Gear();	// Returns the Gear setting
	Drive::e_mode Mode();	// Returns the current driving mode
	
	//	Methods
	
	void Gear( Drive::e_gear value );	// Sets the Gear to new value
	void Mode( Drive::e_mode value );	// Sets the mode to new value
	void JoystickArcadeDrive( float speed, float rotate);	// Drive Robot
	void JoystickTankDrive( float leftSpeed, float rightSpeed);
	void ProgrammedDrive( float leftSpeed, float rightSpeed);
	void Stop();
	void ResetHeading( );
	
	void PlaceSensorsOnLiveWindow( LiveWindow *lw );
};

#endif
