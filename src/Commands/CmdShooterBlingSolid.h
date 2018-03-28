#ifndef CMDSHOOTERBLINGSOLID_H
#define CMDSHOOTERBLINGSOLID_H

#include "../CommandBase.h"

/**
 * @author Flash 1319
 */
class CmdShooterBlingSolid: public CommandBase {
public:
	CmdShooterBlingSolid();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
