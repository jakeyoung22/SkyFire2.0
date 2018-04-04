#include "cmdBaseAimByCamera.h"

#include "../vision/BackboardFinder.h"

#include "iostream"


cmdBaseAimByCamera::cmdBaseAimByCamera()
	: CommandBase("cmdBaseAimByCamera")
{
	Requires(drive);

	camera = new BackboardFinder;




}

// Called just before this Command runs the first time
void cmdBaseAimByCamera::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void cmdBaseAimByCamera::Execute()
{



	//if (camera->SeesTarget() == true)
	//{
		std::cout << "Correction Factor" << 0-camera->DoVision() << "\n" ;
			drive->JoystickArcadeDrive(0.0f, OI::Filter(0-camera->DoVision())  );
	//}


}

// Make this return true when this Command no longer needs to run execute()
bool cmdBaseAimByCamera::IsFinished()
{
	//	If no target lock, exit
	if (camera->HasLock()== true)
	{
		return true;
	}
	else
		return false;



}

// Called once after isFinished returns true
void cmdBaseAimByCamera::End()
{
	drive->JoystickArcadeDrive( 0.0f, 0.0f );


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cmdBaseAimByCamera::Interrupted()
{
	End();
}

void cmdBaseAimByCamera::SetOffsetAngle(double angle) {
  offsetAngle_ = angle;
}
