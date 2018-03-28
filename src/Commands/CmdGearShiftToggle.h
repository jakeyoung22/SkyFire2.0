#ifndef CMDGEARSHIFTTOGGLE_H
#define CMDGEARSHIFTTOGGLE_H

#include "../CommandBase.h"
#include "CmdGearShiftHigh.h"
#include "CmdGearShiftLow.h"

/**
 * @author 1319
 */
class CmdGearShiftToggle: public CommandBase {
public:
	CmdGearShiftToggle();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
