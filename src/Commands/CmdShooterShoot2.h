#ifndef CMDSHOOTERSHOOT2_H
#define CMDSHOOTERSHOOT2_H

#include "../CommandBase.h"

/**
 * @author 1319
 */
class CmdShooterShoot2: public CommandBase {
private:

public:
	CmdShooterShoot2( );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	

};

#endif
