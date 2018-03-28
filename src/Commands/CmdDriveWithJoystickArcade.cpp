#include "CmdDriveWithJoystickArcade.h"

CmdDriveWithJoystickArcade::CmdDriveWithJoystickArcade() : CommandBase("CmdDriveWithJoystickArcade")
{
	// Use requires() here to declare subsystem dependencies
	Requires( drive );
}

// Called just before this Command runs the first time
void CmdDriveWithJoystickArcade::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveWithJoystickArcade::Execute()
{
	if (!replaying())
		ReadJoystick();	
	
	drive->JoystickArcadeDrive( m_speed, m_rotate /*, m_spin */);
	// We'll be recording stuff and everything.
	RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveWithJoystickArcade::IsFinished()
{
	return (drive->Mode() != Drive::arcade );
}

// Called once after isFinished returns true
void CmdDriveWithJoystickArcade::End()
{
	drive->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveWithJoystickArcade::Interrupted()
{
	drive->Stop();	// For now, some commands this may screw up.
}

void CmdDriveWithJoystickArcade::ReadJoystick()
{
	m_speed = oi->driveY();			// This has been found to be correct
	m_rotate = oi->driveX();		// Don't mess with it.  :)
}

void CmdDriveWithJoystickArcade::RecordExecute()
{
	//	buffer to hold the string we're building.
	char buff[100];
	
	sprintf( buff, "<drive speed='%5.3f' rotate='%5.3f'/>", m_speed, m_rotate);
	
	CommandBase::CommonRecord( "execute", buff );
}
void CmdDriveWithJoystickArcade::LoadData(tinyxml2::XMLElement *data)
{
	//	The execute element passed to us includes the drive element (as written in
	//	the RecordExecute() method just above us.  Look up there to see what it looks
	//	like.
	tinyxml2::XMLElement *e = data->FirstChildElement();
	
	m_speed  = e->FloatAttribute( "speed" );
	m_rotate = e->FloatAttribute( "rotate" );
}


