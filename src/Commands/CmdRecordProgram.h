#ifndef CMDRECORDPROGRAM_H
#define CMDRECORDPROGRAM_H

#include "../CommandBase.h"

/**
 *
 *
 * @author WindRiver
 */
class CmdRecordProgram: public CommandBase {
public:
	CmdRecordProgram();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
protected:
	const char * MakeFilename();
};

#endif
