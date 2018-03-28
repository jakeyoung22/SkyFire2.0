#ifndef CMDREPLAYPROGRAM_H
#define CMDREPLAYPROGRAM_H

#include "../CommandBase.h"
#include "../tools/tinyxml2.h"
#include <map>
#include <list>

/**
 *
 *
 * @author WindRiver
 */
class CmdReplayProgram: public CommandBase {
public:
	CmdReplayProgram();
	CmdReplayProgram( const char * filename );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	typedef struct cmdItem {
		char * name;
		CommandBase * cmd;
		cmdItem( char * _name, CommandBase * _cmd ) {name =_name; cmd = _cmd; };
	} t_cmdItem;
	
	struct name_compare {
		bool operator()(const t_cmdItem& x, const t_cmdItem& y) const
		{
			return (strcmp( x.name, y.name ) < 0);
		}
	};

	tinyxml2::XMLDocument * m_xml;
	tinyxml2::XMLNode     * m_current;
	UINT32 basePacketNumber;
	
	//std::map<>
	//std::map<t_cmdItem, name_compare> *cmdMap;
	std::map< std::string, CommandBase *> cmdMap;
	std::list< tinyxml2::XMLElement* > elementList;
protected:
	void ProcessStep( tinyxml2::XMLElement * element );
	CommandBase * CommandFromName( const char * name );
	void LoadMap();
	std::string * m_programFileName;
};

#endif
