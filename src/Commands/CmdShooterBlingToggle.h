#ifndef CMDSHOOTERBLINGTOGGLE_H
#define CMDSHOOTERBLINGTOGGLE_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingToggle: public CommandBase {
private:
	Command *c;
public:
	CmdShooterBlingToggle();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
