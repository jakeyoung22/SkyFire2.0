#ifndef CMDSHOOTERBLINGON_H
#define CMDSHOOTERBLINGON_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingOn: public CommandBase {
public:
	CmdShooterBlingOn();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
