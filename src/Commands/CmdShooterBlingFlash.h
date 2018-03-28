#ifndef CMDSHOOTERBLINGFLASH_H
#define CMDSHOOTERBLINGFLASH_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingFlash: public CommandBase {
public:
	CmdShooterBlingFlash();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
