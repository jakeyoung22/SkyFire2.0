#ifndef CMDDRIVEAUTO_H
#define CMDDRIVEAUTO_H

#include "../CommandBase.h"

/**
 *
 *
 * @author WindRiver
 */
class CmdDriveAuto: public CommandBase {
private:
	float m_speedLeft;
	float m_speedRight;
	float m_distance;
	
	float m_finalLeftDist;
public:
	CmdDriveAuto( float speed, float distance );
	CmdDriveAuto( float speedLeft, float speedRight, float distance );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
