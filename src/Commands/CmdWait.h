#ifndef CmdWait_H
#define CmdWait_H

#include "../CommandBase.h"

/**
 *
 *
 * @author WindRiver
 */
class CmdWait: public CommandBase {
private:
	UINT32 endPacketNumber;
	float  m_waitTime;
	//UINT32 basePacketNumber;
public:
	CmdWait( float waitTime = SHOOTER_SPINUP_WAIT_TIME);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
