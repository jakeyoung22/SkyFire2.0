#ifndef CMDGEARSHIFTLOW_H
#define CMDGEARSHIFTLOW_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdGearShiftLow: public CommandBase {
public:
	CmdGearShiftLow();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
