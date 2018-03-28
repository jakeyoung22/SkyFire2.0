#include "CmdGearShiftLow.h"

CmdGearShiftLow::CmdGearShiftLow() : CommandBase("CmdGearShiftLow")
{
	Requires(drive);
}

// Called just before this Command runs the first time
void CmdGearShiftLow::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void CmdGearShiftLow::Execute()
{
	drive->Gear(Drive::low);	
	RecordExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool CmdGearShiftLow::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CmdGearShiftLow::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdGearShiftLow::Interrupted()
{
	
}
