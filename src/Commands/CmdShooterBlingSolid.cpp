#include "CmdShooterBlingSolid.h"

CmdShooterBlingSolid::CmdShooterBlingSolid() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingSolid::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingSolid::Execute() {
	shooter->SetFlashBling(false);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingSolid::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingSolid::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingSolid::Interrupted() {
	
}
