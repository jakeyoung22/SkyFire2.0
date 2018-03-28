#include "CmdRecordProgram.h"
#include <time.h>
#include <stdio.h>

CmdRecordProgram::CmdRecordProgram() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CmdRecordProgram::Initialize() {
	if (!recording())
		startRecording(MakeFilename() /* "tmp/record.xml" */);
}

// Called repeatedly when this Command is scheduled to run
void CmdRecordProgram::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool CmdRecordProgram::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CmdRecordProgram::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdRecordProgram::Interrupted() {
}

const char * CmdRecordProgram::MakeFilename()
{
#if true
	static std::string prog = "tmp/";
	prog.append( SmartDashboard::GetString( "RecordFile" ) );
	return prog.c_str();
#else
	time_t timer;			//	Seconds since origin time
	struct tm c;			//	A structure that holds the times in components.
	static char buff[80];	// Static so will be around after we return
	
	//	Get the clock in local time, and convert it into the broken down structure
	timer = time( NULL );
	localtime_r( &timer, &c );
	
	//	Use the date/time info to make a filename with the date in yyyymmdd-hhmmss format
	//	in the tmp folder.
	sprintf( buff,
			"tmp/rec%04d%02d%02d-%02d%02d%02d.xml",
			c.tm_year+1900, c.tm_mon, c.tm_mday, c.tm_hour, c.tm_min, c.tm_sec );
	
	//	return a pointer to this buffer

	return buff;
#endif
}

