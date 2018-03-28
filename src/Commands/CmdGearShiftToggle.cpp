#include "CmdGearShiftToggle.h"

CmdGearShiftToggle::CmdGearShiftToggle() : CommandBase("CmdGearShiftToggle")
{
	
}

// Called just before this Command runs the first time
void CmdGearShiftToggle::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void CmdGearShiftToggle::Execute()
{
	Command *c;
	if(drive->Gear() == Drive::low)
	{
		c = new CmdGearShiftHigh();
	}
	else
	{
		c = new CmdGearShiftLow();
	}
	
	c->Start();
	
	// Don't record, so that playback doesn't have to know not to replay it back
	// Why not replay it?  Because that would duplicate the command we're about to
	// spawn (well, it may duplicate or do the wrong one, or... )
	//RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearShiftToggle::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CmdGearShiftToggle::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearShiftToggle::Interrupted()
{
	
}
