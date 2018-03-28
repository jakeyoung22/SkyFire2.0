#ifndef CMDDRIVEWITHJOYSTICKARCADE_H
#define CMDDRIVEWITHJOYSTICKARCADE_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdDriveWithJoystickArcade: public CommandBase {
public:
	CmdDriveWithJoystickArcade();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
	virtual void RecordExecute( );
	
	virtual void LoadData(tinyxml2::XMLElement *data);	//Used by CmdReplayProgram
	
private:
	void ReadJoystick();
	
	float m_speed, 	m_rotate;
};

#endif
