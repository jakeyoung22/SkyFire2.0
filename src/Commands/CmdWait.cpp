#include "CmdWait.h"

CmdWait::CmdWait( float waitTime ) : CommandBase("CmdWait")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	m_waitTime = waitTime;
}

// Called just before this Command runs the first time
void CmdWait::Initialize()
{
	endPacketNumber = DriverStation::GetInstance()->GetPacketNumber() + (int)(m_waitTime * 50.0);
}

// Called repeatedly when this Command is scheduled to run
void CmdWait::Execute()
{
	
}

// Make this return true when this Command no longer needs to run execute()
bool CmdWait::IsFinished()
{
	//return (shooter->OkayToShoot() );
	return (DriverStation::GetInstance()->GetPacketNumber()) >= endPacketNumber ;

}

// Called once after isFinished returns true
void CmdWait::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdWait::Interrupted()
{
	
}
