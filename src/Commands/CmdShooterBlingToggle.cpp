#include "CmdShooterBlingToggle.h"
#include "CmdShooterBlingSolid.h"
#include "CmdShooterBlingFlash.h"

CmdShooterBlingToggle::CmdShooterBlingToggle() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdShooterBlingToggle::Initialize() {
	c = NULL;
}

// Called repeatedly when this Command is scheduled to run
void CmdShooterBlingToggle::Execute() {
	if(shooter->GetBlingFlashing())
	{
		c = new CmdShooterBlingSolid();
	}
	else
	{
		c = new CmdShooterBlingFlash();
	}
	c->Start();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterBlingToggle::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdShooterBlingToggle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterBlingToggle::Interrupted() {
	
}
