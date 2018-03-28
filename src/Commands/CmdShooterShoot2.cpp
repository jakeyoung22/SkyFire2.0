#include "CmdShooterShoot2.h"

#include "../utilities.h"

CmdShooterShoot2::CmdShooterShoot2( ) : CommandBase("CmdShooterShoot2")
{
	// Use requires() here to declare subsystem dependencies
	Requires(shooter);
}

// Called just before this Command runs the first time
void CmdShooterShoot2::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CmdShooterShoot2::Execute()
{
	//fixme: this uses the raw speed get rather than the encoder setting. It may need to be changed if we get that working

	shooter->Pusher(Shooter::shoot);



}

// Make this return true when this Command no longer needs to run execute()
bool CmdShooterShoot2::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CmdShooterShoot2::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdShooterShoot2::Interrupted()
{

}


