#ifndef CMDDRIVENUDGE_H
#define CMDDRIVENUDGE_H

#include "../CommandBase.h"
#include "../utilities.h"

/**
 *
 *
 * @author WindRiver
 */
class CmdDriveNudge: public CommandBase {
private:
	 bool m_forward;
	 unsigned long m_endPacketNumber;
public:
	CmdDriveNudge( bool forward );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void RecordInitialize();
	virtual void LoadInitData( tinyxml2::XMLElement *data );
};

#endif
