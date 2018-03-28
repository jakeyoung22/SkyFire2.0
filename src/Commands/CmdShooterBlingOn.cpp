#include "CmdShooterBlingOn.h"

CmdShooterBlingOn::CmdShooterBlingOn() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingOn::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingOn::Execute() {
	shooter->SetBlingOn(true);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingOn::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingOn::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingOn::Interrupted() {
	
}
