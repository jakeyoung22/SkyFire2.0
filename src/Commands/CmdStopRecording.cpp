#include "CmdStopRecording.h"

CmdStopRecording::CmdStopRecording() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdStopRecording::Initialize() {
	if (recording() )
		stopRecording();
}

// Called repeatedly when this Command is scheduled to run
void CmdStopRecording::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool CmdStopRecording::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdStopRecording::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdStopRecording::Interrupted() {
}
