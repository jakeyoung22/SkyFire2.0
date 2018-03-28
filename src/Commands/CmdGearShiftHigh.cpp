#include "CmdGearShiftHigh.h"

CmdGearShiftHigh::CmdGearShiftHigh() : CommandBase("CmdGearShiftHigh")
{
	// How much movement can the gear box tolerate while we're shifting?
	// Can we shift under full load?
	//	Erich says "Yes, we can."
	Requires(drive);
}

// Called just before this Command runs the first time
void CmdGearShiftHigh::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void CmdGearShiftHigh::Execute()
{
	drive->Gear(Drive::high);	
	RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearShiftHigh::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CmdGearShiftHigh::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearShiftHigh::Interrupted()
{
	
}
