#include "CmdDriveWithJoystickTank.h"

CmdDriveWithJoystickTank::CmdDriveWithJoystickTank() : CommandBase("CmdDriveWithJoystickTank")
{
	// Use requires() here to declare subsystem dependencies
	Requires(drive);
}

// Called just before this Command runs the first time
void CmdDriveWithJoystickTank::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveWithJoystickTank::Execute()
{
	if (!replaying())
		ReadJoysticks();	
	
	drive->JoystickTankDrive( m_right, m_left );
	
	RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveWithJoystickTank::IsFinished()
{
	return (drive->Mode() != Drive::tank );
}

// Called once after isFinished returns true
void CmdDriveWithJoystickTank::End()
{
	drive->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveWithJoystickTank::Interrupted()
{
	drive->Stop();	// For now, some commands this may screw up.
}

void CmdDriveWithJoystickTank::ReadJoysticks()
{
	m_left  = oi->driveY();
	m_right = oi->driveY2();
}
void CmdDriveWithJoystickTank::RecordExecute()
{
	//	buffer to hold the string we're building.
	char buff[100];
	
	sprintf( buff, "<drive left='%5.3f' right='%5.3f'/>", m_left, m_right );

	CommandBase::CommonRecord( "execute", buff );
}
void CmdDriveWithJoystickTank::LoadData(tinyxml2::XMLElement *data)
{
	//	The execute element passed to us includes the drive element (as written in
	//	the RecordExecute() method just above us.  Look up there to see what it looks
	//	like.
	tinyxml2::XMLElement *e = data->FirstChildElement();
	
	m_left  = e->FloatAttribute( "left" );
	m_right = e->FloatAttribute( "right" );
}
