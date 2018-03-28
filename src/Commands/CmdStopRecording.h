#ifndef CMDSTOPRECORDING_H
#define CMDSTOPRECORDING_H

#include "../CommandBase.h"

/**
 *
 *
 * @author WindRiver
 */
class CmdStopRecording: public CommandBase {
public:
	CmdStopRecording();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
