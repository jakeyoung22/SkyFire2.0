#ifndef CMDSHOOTERBLINGOFF_H
#define CMDSHOOTERBLINGOFF_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingOff: public CommandBase {
public:
	CmdShooterBlingOff();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
