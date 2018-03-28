#include "CmdShooterLoaderToggle.h"

#include "../utilities.h"

CmdShooterLoaderToggle::CmdShooterLoaderToggle( ) : CommandBase("CmdShooterLoaderToggle")
{
	// Use requires() here to declare subsystem dependencies
	Requires(shooter);
}

// Called just before this Command runs the first time
void CmdShooterLoaderToggle::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CmdShooterLoaderToggle::Execute()
{
	//fixme: this uses the raw speed get rather than the encoder setting. It may need to be changed if we get that working

	Command *c;
		if(shooter->Pusher() == Shooter::retract)
		{
			c = new CmdShooterShoot2();
		}
		else
		{
			c = new CmdShooterPusherRetract();
		}

		c->Start();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterLoaderToggle::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CmdShooterLoaderToggle::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterLoaderToggle::Interrupted()
{

}


