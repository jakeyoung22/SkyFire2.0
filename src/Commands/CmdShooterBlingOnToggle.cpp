#include "CmdShooterBlingOnToggle.h"
#include "CmdShooterBlingOn.h"
#include "CmdShooterBlingOff.h"

CmdShooterBlingOnToggle::CmdShooterBlingOnToggle() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingOnToggle::Initialize() {
	c = NULL;
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingOnToggle::Execute() {
	if(shooter->GetBlingOn()) {
		c = new CmdShooterBlingOff();
	}
	else {
		c = new CmdShooterBlingOn();
	}
	c->Start();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingOnToggle::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingOnToggle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingOnToggle::Interrupted() {
	
}
