#include "CmdReplayProgram.h"


//#include "CmdDeckPositionToFloorLoad.h"

#include "CmdDriveChangeMode.h"
#include "CmdDriveWithJoystickArcade.h"
#include "CmdDriveWithJoystickTank.h"
#include "CmdGearShiftHigh.h"
#include "CmdGearShiftLow.h"
#include "CmdGearShiftToggle.h"
//#include "CmdLiftShiftOff.h"
//#include "CmdLiftShiftOn.h"
//#include "CmdLiftShiftToggle.h"

#include "CmdRecordProgram.h"
#include "CmdReplayProgram.h"
//#include "CmdSecondaryLiftClimb.h"
//#include "CmdSecondaryLiftReverse.h"
#include "CmdShooterMotorStart.h"
#include "CmdShooterMotorStop.h"
#include "CmdShooterMotorToggle.h"
#include "CmdShooterPusherRetract.h"
#include "CmdShooterShoot.h"
#include "CmdStopRecording.h"


//#include "CmdLiftSecondaryCylindersTopToggle.h"
//#include "CmdLiftSecondaryCylindersTopEngage.h"
//#include "CmdLiftSecondaryCylindersTopDisengage.h"
//#include "CmdLiftSecondaryCylindersBottomToggle.h"
//#include "CmdLiftSecondaryCylindersBottomEngage.h"
//#include "CmdLiftSecondaryCylindersBottomDisengage.h"

#include "CmdShooterWaitForSpeed.h"
#include "CmdShooterSpeedToggle.h"


CmdReplayProgram::CmdReplayProgram()
	: CommandBase( "CmdReplayProgram" )
{
	//	Null out the member pointers
	m_xml = NULL;
	m_current = NULL;
	m_programFileName = NULL;

	//	Set up our table of command object pointers and names
	if (cmdMap.size() == 0)
		LoadMap();
}

CmdReplayProgram::CmdReplayProgram( const char * filename )
{
	m_xml = NULL;
	m_current = NULL;
	m_programFileName = new std::string( filename );
	
	//	Set up our table of command object pointers and names
	if (cmdMap.size() == 0)
		LoadMap();
}
// Called just before this Command runs the first time
void CmdReplayProgram::Initialize() 
{
	char fileBuff[255];
	
	//	The file will be in the programs folder.
	strcpy( fileBuff, "programs/");
	
	//	If we were not constructed with a file name, use the default one
	//	Otherwise, open the one we were constructed with
	if (m_programFileName == NULL)
		strcat( fileBuff, "default.xml");
	else
	{
		strcat( fileBuff, m_programFileName->c_str());
	}
	
	//	Construct an XML document and save the pointer in the member, and load our
	//	file in it.
	m_xml = new tinyxml2::XMLDocument( true, tinyxml2::COLLAPSE_WHITESPACE );

	tinyxml2::XMLError sts = m_xml->LoadFile( fileBuff );
	if (sts != tinyxml2::XML_SUCCESS)
	{
#if !SDMD
		//SmartDashboard::PutNumber( "tiny2xml2::XMLDocument->LoadFile sts", sts );
#endif
		cout << "Loadfile Status " << sts << std::endl;
		delete m_xml;	// Don't need this anymore if we couldn't load the file
		m_xml = NULL;
	}
	else
	{
#if !SDMD
		SmartDashboard::PutString( "CmdReplayProgram", "File open");
#endif
		//	Walk to the Top level (record) node
		m_current = m_xml->LastChild();

		if (strcmp(m_current->Value(), "record" ) != 0)
		{
#if !SDMD
			SmartDashboard::PutString( "CmdReplayProgram", "?Top element is not 'record'");
#endif
			cout << "CmdReplayProgram, Top Element of program file is not 'record'" << std::endl;
			delete m_xml;		// Can't use this file.  Drop the object on the floor
			m_current = NULL;	// Null this out, so we know we're not doing anything with the file.
		}
		else
		{
			//	Now, grab the first child of the parent, our first recorded happening
			m_current = m_current->FirstChild();
		}
	}
	
	replaying( true );
	
	//	Save the current packet number; we'll subtract this from all future packet numbers to keep the
	//	XML file's packet numbers in step with ours.
	basePacketNumber = DriverStation::GetInstance()->GetPacketNumber();
}

// Called repeatedly when this Command is scheduled to run
void CmdReplayProgram::Execute() {
	if (m_current != NULL)
	{
		//	Get the biased current packet number
		UINT32 currentPacketNumber = (DriverStation::GetInstance()->GetPacketNumber() - basePacketNumber);
		
		//	And display it for prosterity
		char buff[22];	// what's below, plus the null, plus 4 digits, just in case
		
		sprintf( buff, "Executing %6d", currentPacketNumber );
#if !SDMD
		SmartDashboard::PutString( "CmdReplayProgram", buff);
#endif
		
		//	Execute any unexpired long-term elements, and remove the expired ones
		for ( std::list<tinyxml2::XMLElement *>::iterator
				it = elementList.begin();
				it != elementList.end();
				/* Incrementing in loop to handle Halloween problems */ )
		{
			if ( (*it)->UnsignedAttribute("endClock") <	currentPacketNumber )
				ProcessStep( *it++ );			//	Deal with this element, and advance the iterator
			else
				it = elementList.erase( it );	//	Removing an entry effectively advances the iterator to the next entry
		}
		
		//	Convert the current node into an element for us to process
		tinyxml2::XMLElement *element = m_current->ToElement();
		
		//	While the clock value of the node is less than our offset packet number
		//	we will process this node
		while ( element->UnsignedAttribute( "clock" ) < currentPacketNumber )
		{
			ProcessStep( element );
			
			//	If this is a long term element, add it to the long-term element queue
			//	Be warned that we're shutting down when the last element is read out of the
			//	XML file.  If you have an endClock on an element that lives past that
			//	timestamp, well that's just too dang bad.
			if (element->Attribute("endClock") != NULL)
			{
				elementList.push_back( element ); //insert( elementList.end(), element );
			}
			
			//	And move on to the next node
			m_current = m_current->NextSibling();
			
			//	We've hit the end of the list; time to boogie--before we try to cast this null
			//	pointer into an element.
			if (m_current==NULL)
				break;
			
			//	And get an element pointer so we can treat it as one
			element = m_current->ToElement();
		}
	}
}


// Make this return true when this Command no longer needs to run execute()
bool CmdReplayProgram::IsFinished() {
	//	When there are no more entries, we're done running the program file.
	return (m_current==NULL);
}

// Called once after isFinished returns true
void CmdReplayProgram::End() {
	if (m_xml != NULL)
	{
		delete m_xml;
		m_xml = NULL;
	}
	
	//	Depending on our queue going out of scope to free all its memory
	
	//	Remove this flag to revert behaviors to the live ones
	replaying(false);

	//	Tell the world about me...
#if !SDMD
	SmartDashboard::PutString( "CmdReplayProgram", "Ended");
#endif
	cout << "CmdReplayProgram, Ended" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdReplayProgram::Interrupted() {
	replaying(false);
#if !SDMD
	SmartDashboard::PutString( "CmdReplayProgram", "Interrupted");
#endif
	cout << "CmdReplayProgram, Interrupted" << std::endl;
}

//	Process an XML element that contains a single step in the "program".
void CmdReplayProgram::ProcessStep( tinyxml2::XMLElement * element )
{
	//	Get a pointer to a command for the object name given in the object attribute of the element
	CommandBase *cmd = CommandFromName( element->Attribute("object") );
	
	if (cmd != NULL)
	{
		string elementType = element->Name();
		
		cout << "Processing a " << elementType << " from " << element->Attribute("object") << std::endl;
		
		if (elementType == "execute")
		{
			if (!element->NoChildren())
			{
				cmd->LoadData( element );
			}
			
			//	Then add command to the scheduler's queue.  If this is a one shot command, this is necessary.
			//	If this a command (like CmdJoystickDrive) that gets run pretty much continously, then this is
			//	redundant and a waste, but I hope not an issue.  We can't really tell what the scheduler has
			//	in the queue, so.
			Scheduler::GetInstance()->AddCommand(cmd);
		}
		else if (elementType == "initialize")
		{
			if (!element->NoChildren())
			{
				cmd->LoadInitData( element );
			}
		}
		else
		{
			cout << "Unknown record file element read (" << elementType << ").  Dropping." << std::endl;
		}

		
		//	If the element has children, then pass the element to the command to load the data

	}
	
}

//	Lookup the CommandBase object pointer for the name from the XML.  Given that "all it takes" is a STL map
//	lookup, I'm not sure why this is a method all to itself.  I thought it would be more complicated.
CommandBase * CmdReplayProgram::CommandFromName( const char * name )
{
	return cmdMap[ name ];
}
//
//	Like OI and the new commands created for the button events, create pointers to the commands that we
//	care about and associate them with the their names.  This lets us grab one on the fly when we see
//	its name in the XML file.  In C# we might do Reflection on the namespace to turn the text version of
//	the class name into a pointer to an object of that type, but we're not in Microsoft's CLR here.
//
//	If we were to get really paranoid about the multiple objects, we could move this map to somewhere we
//	could share it with the OI button event definitions.  Note that if multiple buttons call one command
//	we already have duplication.
//
//	Toggles, cycles and program operations don't belong here, and have been commented out.
//
void CmdReplayProgram::LoadMap()
{

	//cmdMap[ "CmdDeckPositionCycle" ] = new CmdDeckPositionCycle();

//	cmdMap[ "CmdDeckPositionToFloorLoad" ] = new CmdDeckPositionToFloorLoad();

	cmdMap[ "CmdDriveChangeMode" ] = new CmdDriveChangeMode();
	cmdMap[ "CmdDriveWithJoystickArcade" ] = new CmdDriveWithJoystickArcade();
	cmdMap[ "CmdDriveWithJoystickTank" ] = new CmdDriveWithJoystickTank();
	cmdMap[ "CmdGearShiftHigh" ] = new CmdGearShiftHigh();
	cmdMap[ "CmdGearShiftLow" ] = new CmdGearShiftLow();
	//cmdMap[ "CmdGearShiftToggle" ] = new CmdGearShiftToggle();
//	cmdMap[ "CmdLiftShiftOff" ] = new CmdLiftShiftOff();
//	cmdMap[ "CmdLiftShiftOn" ] = new CmdLiftShiftOn();
	//cmdMap[ "CmdLiftShiftToggle" ] = new CmdLiftShiftToggle();

	//cmdMap[ "CmdPrimaryLiftToggle" ] = new CmdPrimaryLiftToggle();
	//cmdMap[ "CmdRecordProgram" ] = new CmdRecordProgram();
	//cmdMap[ "CmdReplayProgram" ] = new CmdReplayProgram();
//	cmdMap[ "CmdSecondaryLiftClimb" ] = new CmdSecondaryLiftClimb();
//	cmdMap[ "CmdSecondaryLiftReverse" ] = new CmdSecondaryLiftReverse();
	cmdMap[ "CmdShooterMotorStart" ] = new CmdShooterMotorStart();
	cmdMap[ "CmdShooterMotorStop" ] = new CmdShooterMotorStop();
	//cmdMap[ "CmdShooterMotorToggle" ] = new CmdShooterMotorToggle();
	//cmdMap[ "CmdShooterPusherRetract" ] = new CmdShooterPusherRetract();
	cmdMap[ "CmdShooterShoot" ] = new CmdShooterShoot();
	//cmdMap[ "CmdStopRecording" ] = new CmdStopRecording();

	//cmdMap[ "CmdDeckToggleStall" ] = new CmdDeckToggleStall();
	//cmdMap[ "CmdLiftSecondaryCylindersTopToggle" ] = new CmdLiftSecondaryCylindersTopToggle();
//	cmdMap[ "CmdLiftSecondaryCylindersTopEngage" ] = new CmdLiftSecondaryCylindersTopEngage();
//	cmdMap[ "CmdLiftSecondaryCylindersTopDisengage" ] = new CmdLiftSecondaryCylindersTopDisengage();
	//cmdMap[ "CmdLiftSecondaryCylindersBottomToggle" ] = new CmdLiftSecondaryCylindersBottomToggle();
//	cmdMap[ "CmdLiftSecondaryCylindersBottomEngage" ] = new CmdLiftSecondaryCylindersBottomEngage();
//	cmdMap[ "CmdLiftSecondaryCylindersBottomDisengage" ] = new CmdLiftSecondaryCylindersBottomDisengage();

	cmdMap[ "CmdShooterWaitForSpeed" ] = new CmdShooterWaitForSpeed();
	cmdMap[ "CmdShooterSpeedToggle" ] = new CmdShooterSpeedToggle();

//	cmdMap[ "CmdShooterBarsToggle" ] = new CmdShooterBarsToggle();
	return;
}
