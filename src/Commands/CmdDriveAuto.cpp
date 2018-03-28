#include "CmdDriveAuto.h"
#include "../Utilities.h"

CmdDriveAuto::CmdDriveAuto(float speed, float distance ) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(drive);
	
	m_speedLeft = speed;
	m_speedRight = speed;
	m_distance = distance;
}

CmdDriveAuto::CmdDriveAuto(float leftSpeed, float rightSpeed, float distance ) {
	Requires(drive);
	
	m_speedLeft = leftSpeed;
	m_speedRight = rightSpeed;
	m_distance = distance;
}

// Called just before this Command runs the first time
void CmdDriveAuto::Initialize() {
	m_finalLeftDist = drive->DistLeft() + (m_distance * sign( m_speedLeft ) );
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveAuto::Execute() {
	drive->ProgrammedDrive( m_speedLeft, m_speedRight);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveAuto::IsFinished() {
	if (m_speedLeft > 0)
	{
		//	Not using the Utility function InTolerance() because we want to catch
		//	overshoot.
		return (drive->DistLeft() >= m_finalLeftDist);
	}
	else
	{
		return (drive->DistLeft() <= m_finalLeftDist);
	}
}

// Called once after isFinished returns true
void CmdDriveAuto::End() {
	drive->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveAuto::Interrupted() {
	drive->Stop();
}
