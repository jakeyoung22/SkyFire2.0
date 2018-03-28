#include "CmdShooterBlingOff.h"

CmdShooterBlingOff::CmdShooterBlingOff() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingOff::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingOff::Execute() {
	shooter->SetBlingOn(false);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingOff::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingOff::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingOff::Interrupted() {
	
}
