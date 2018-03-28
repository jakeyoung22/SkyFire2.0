#ifndef CMDDRIVEWITHJOYSTICKTANK_H
#define CMDDRIVEWITHJOYSTICKTANK_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdDriveWithJoystickTank: public CommandBase {
public:
	CmdDriveWithJoystickTank();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
	virtual void RecordExecute( );
	
	virtual void LoadData(tinyxml2::XMLElement *data);	//Used by CmdReplayProgram
private:
	void ReadJoysticks();
	
	float m_left, m_right;
};

#endif
