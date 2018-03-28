#ifndef CMDSHOOTERMOTORSTOP_H
#define CMDSHOOTERMOTORSTOP_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdShooterMotorStop: public CommandBase {
public:
	CmdShooterMotorStop();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
