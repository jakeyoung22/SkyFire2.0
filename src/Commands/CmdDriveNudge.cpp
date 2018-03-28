#include "CmdDriveNudge.h"

CmdDriveNudge::CmdDriveNudge( bool forward ) : CommandBase("CmdDriveNudge") {
	// Use requires() here to declare subsystem dependencies
	Requires(drive);
	m_forward = forward;
}

// Called just before this Command runs the first time
void CmdDriveNudge::Initialize()
{
	m_endPacketNumber = EndPacketNumber( DRIVE_NUDGE_TIME );
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveNudge::Execute() {
	if (m_forward)
		drive->ProgrammedDrive( 0.40f, 0.42f);
	else
		drive->ProgrammedDrive(-0.45f, -0.40f);
	
	RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveNudge::IsFinished() {
	return (DriverStation::GetInstance()->GetPacketNumber()) >= m_endPacketNumber;
}

// Called once after isFinished returns true
void CmdDriveNudge::End() {
	drive->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveNudge::Interrupted() {
	drive->Stop();
}

void CmdDriveNudge::RecordInitialize()
{
	char buff[80];
	sprintf(buff, "<nudge forward='%s' />", m_forward ? "true" : "false");
	CommonRecord("initialize", buff );
}

void CmdDriveNudge::LoadInitData( tinyxml2::XMLElement *data )
{
	tinyxml2::XMLElement *e = data->FirstChildElement();
	
	m_forward = e->BoolAttribute( "forward" );
}
