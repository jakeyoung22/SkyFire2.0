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
	float m_correction = camera->GetX();
	float m_targetLock	= camera->HasLock();
/*
	if (camera->HasFreshTarget(true)
	{
		drive->JoystickTankDrive( OI::Filter(0-camera->getSteer()*0.86), OI::Filter(camera->getSteer()*0.86), false);
	}
	else
	{
		drive->JoystickTankDrive( 0.0f, 0.0f, false );
		//angulator->SetAngle(m_angAngle);
	}
	*/


	if (m_targetLock == true)
	{
		std::cout << "Correction Factor" << 0-camera->DoVision() << "\n" ;
			drive->JoystickArcadeDrive(0.0f, OI::Filter(0-camera->DoVision())  );
	}

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
