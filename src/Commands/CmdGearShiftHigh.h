#ifndef CMDGEARSHIFTHIGH_H
#define CMDGEARSHIFTHIGH_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdGearShiftHigh: public CommandBase {
public:
	CmdGearShiftHigh();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
