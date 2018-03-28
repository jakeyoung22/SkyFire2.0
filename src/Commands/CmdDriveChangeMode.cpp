#include "CmdDriveChangeMode.h"

CmdDriveChangeMode::CmdDriveChangeMode() : CommandBase("CmdDriveChangeMode") {
	Requires(drive);
	// We don't really need the drive just to change the drive mode
}

// Called just before this Command runs the first time
void CmdDriveChangeMode::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void CmdDriveChangeMode::Execute() {
	switch (drive->Mode())
	{
		case Drive::arcade:
			cout << "Changing drive mode to tank" << std::endl;
			drive->Mode( Drive::tank );
			break;
		case Drive::tank:
			cout << "Changing drive mode to Arcade" << std::endl;
			drive->Mode( Drive::arcade );
			break;
		default:
			// We might splash something on the SmartDashboard that trying to change
			// modes while climbing isn't very bright.  Up is the only direction.
			break;
	}
	// Doesn't need to be recorded as this command simply changes joystick drive
	// commands from one type to the other, and they're being recorded.
}

// Make this return true when this Command no longer needs to run execute()
bool CmdDriveChangeMode::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdDriveChangeMode::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdDriveChangeMode::Interrupted() {
}
