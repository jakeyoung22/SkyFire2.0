#ifndef CMDSHOOTERLOADERTOGGLE_H
#define CMDSHOOTERLOADERTOGGLE_H

#include "../CommandBase.h"
#include "CmdShooterShoot2.h"
#include "CmdShooterPusherRetract.h"

/**
 * @author 1319
 */
class CmdShooterLoaderToggle: public CommandBase {
private:

public:
	CmdShooterLoaderToggle( );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	

};

#endif
