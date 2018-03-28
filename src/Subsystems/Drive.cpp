#include "Drive.h"
#include "../Robotmap.h"
#include "../Commands/CmdDriveWithJoystickArcade.h"
#include "../Commands/CmdDriveWithJoystickTank.h"
//#include "../Commands/CmdTestSecondaryClimber.h"

Drive::Drive() : Subsystem("Drive")
{
	m_left = new Victor(PWM_LEFT_PORT);
	m_right = new Victor(PWM_RIGHT_PORT);
	
	m_drive = new RobotDrive(m_left, m_right);
	m_drive->SetInvertedMotor( RobotDrive::kFrontRightMotor, true);
	m_drive->SetInvertedMotor( RobotDrive::kRearRightMotor, true);

	
	m_solGear = new DoubleSolenoid(SOL_GEAR_SHIFT_LOW, SOL_GEAR_SHIFT_HIGH);
	
	m_leftEncoder = new Encoder(GPIO_LEFT_ENCODER_A, GPIO_LEFT_ENCODER_B, true, Encoder::k1X);
	m_rightEncoder = new Encoder(GPIO_RIGHT_ENCODER_A, GPIO_RIGHT_ENCODER_B, false, Encoder::k1X);

	
	m_leftEncoder->SetDistancePerPulse( DRV_DIST_PER_PULSE );
	m_rightEncoder->SetDistancePerPulse( DRV_DIST_PER_PULSE );
	
	m_leftEncoder->Start();
	m_rightEncoder->Start();
	
	m_driveGyro = NULL;
	//m_driveGyro = new Gyro(ANALOG_DRIVE_GYRO);
	//m_driveGyro->Reset();
	
	//	Start us off in high gear
	Gear( high );
	
	//	Default to Arcade Drive
	m_mode = tank;
	
	m_CmdArcade = NULL;
	m_CmdTank = NULL;
	m_CmdClimb = NULL;
	
	//m_drive->SetExpiration( 2.0f );
	m_drive->SetSafetyEnabled( SAFETY_ENABLED );
}
    
void Drive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	m_CmdArcade = new CmdDriveWithJoystickArcade();
	m_CmdTank = new CmdDriveWithJoystickTank();
	m_CmdClimb = NULL; //new CmdTestSecondaryClimber();
	SetDefaultCommand( m_CmdTank );
}

float Drive::Heading()
{
	if (m_driveGyro != NULL)
		return m_driveGyro->GetAngle();
	else
		return 0;
}

Drive::e_gear Drive::Gear()
{
	return m_gear;
}

Drive::e_mode Drive::Mode()
{
	return m_mode;
}

void Drive::ProgrammedDrive(float leftSpeed, float rightSpeed)
{
	m_drive->TankDrive(0-leftSpeed, rightSpeed, false);
}

float Drive::SpeedLeft()
{
	return (float)(m_leftEncoder->GetRate());
}

float Drive::SpeedRight()
{
	return (float)(m_rightEncoder->GetRate());
}

void Drive::JoystickTankDrive(float leftSpeed, float rightSpeed)
{
	m_drive->TankDrive(0-leftSpeed, rightSpeed, false );
//	static long loop=0;
//	if (loop++ % 10 == 0)
//	cout << "TankDrive L: " << leftSpeed << ", R: " << rightSpeed << std::endl;
}

void Drive::Stop()
{
	m_drive->StopMotor();
}

void Drive::Gear(Drive::e_gear value)
{
	switch(value)
	{
		case low:
			m_solGear->Set(DoubleSolenoid::kForward);
			break;
		case high:
			m_solGear->Set(DoubleSolenoid::kReverse);
			break;
		default:
			m_solGear->Set(DoubleSolenoid::kOff);
			break;
	}
	
	m_gear = value;
}

void Drive::Mode( Drive::e_mode value )
{
	if (m_mode != value)
	{
		m_mode = value;
		switch (m_mode)
		{
		case arcade:
			SetDefaultCommand( m_CmdArcade );
			break;
		case tank:
			cout << "Setting default command to tank" << std::endl;
			SetDefaultCommand( m_CmdTank );
			break;
		case climb:
			//SetDefaultCommand( m_CmdClimb );
			//break;
		default:
			SetDefaultCommand( NULL );
			cout << "Hm... no default drive command.  What happened?" << std::endl;
			break;
		}
	}
	
}

void Drive::JoystickArcadeDrive(float speed, float rotate)
{
	//	It appears that we need to pass the X axis (rotate) in the "speed"
	//	parameter and the Y axis (speed) in the "rotate" parameter.  We've
	//	decided to use the correct names here and let WPIlib just be crazy.
	m_drive->ArcadeDrive( 0-rotate, speed, false);
}

void Drive::ResetHeading()
{
	if (m_driveGyro != NULL)
		m_driveGyro->Reset();
}

void Drive::PlaceSensorsOnLiveWindow( LiveWindow *lw )
{
	
	if (m_driveGyro != NULL) lw->AddSensor( "Drive", "Gyro", m_driveGyro );
	lw->AddActuator( "Drive", "Left Drive Motor", m_left);
	lw->AddActuator( "Drive", "Right Drive Motor", m_right );
	lw->AddActuator( "Drive", "Gear Solenoid", m_solGear);
	lw->AddSensor( "Drive", "Left Encoder", m_leftEncoder);
	lw->AddSensor( "Drive", "Right Encoder", m_rightEncoder);
}

float Drive::DistLeft()
{
	return m_leftEncoder->Get();
}
float Drive::DistRight()
{
	return m_rightEncoder->Get();
}
