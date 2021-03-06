#ifndef cmdBaseAimByCamera_H
#define cmdBaseAimByCamera_H

#include "../CommandBase.h"
#include "../vision/BackboardFinder.h"
//#include "../vision/AimBot.h"
#include "../Subsystems/Drive.h"

#include "WPILib.h"

class cmdBaseAimByCamera: public CommandBase
{
public:
	cmdBaseAimByCamera( );
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetOffsetAngle(double angle);
private:
	BackboardFinder* camera;
	BackboardFinder* target_;
	Drive 	* drive;

	float m_correction;
	  bool foundTarget_;
	  double offsetAngle_;
};

#endif
