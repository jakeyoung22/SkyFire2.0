#ifndef CMDSHOOTERBLINGONTOGGLE_H
#define CMDSHOOTERBLINGONTOGGLE_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingOnToggle: public CommandBase {
private:
	Command *c;
public:
	CmdShooterBlingOnToggle();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
