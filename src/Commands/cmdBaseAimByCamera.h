#ifndef cmdBaseAimByCamera_H
#define cmdBaseAimByCamera_H

#include "../CommandBase.h"
#include "../vision/BackboardFinder.h"

#include "WPILib.h"

class cmdBaseAimByCamera: public CommandBase
{
public:
	cmdBaseAimByCamera(  );
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	BackboardFinder* camera;
	BackboardFinder* target_;

	  bool foundTarget_;
	  double offsetAngle_;
};

#endif
