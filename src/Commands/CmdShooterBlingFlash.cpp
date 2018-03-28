#include "CmdShooterBlingFlash.h"

CmdShooterBlingFlash::CmdShooterBlingFlash() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingFlash::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingFlash::Execute() {
	shooter->SetFlashBling(true);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingFlash::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingFlash::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingFlash::Interrupted() {
	
}
