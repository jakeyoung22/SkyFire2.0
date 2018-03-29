#include "WPILib.h"

#include "CommandBase.h"
#include "Commands/Command.h"
#include "Commands/CmdRecordProgram.h"
#include "Commands/CmdReplayProgram.h"
#include "Commands/CmdStopRecording.h"
#include "Commands/CmdDriveChangeMode.h"
#include "vision/BackboardFinder.h"

class BackboardFinder;
#include "Subsystems/Pneumatics.h"

#include "Utilities.h"

#include <dirent.h>

//extern int sysClkRateGet();

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	//LiveWindow *lw;
	Pneumatics *pneumatics;
	
	SendableChooser *sc;
	

	  // Vision
	  BackboardFinder* target_;

public:
	CommandBasedRobot()
	{
		cout << "CommandBasedRobot Constructor..." << std::endl;
		autonomousCommand = NULL;

		//lw = NULL;
		pneumatics = NULL;
		sc = NULL;
	}
private:
	
	virtual void RobotInit()
	{
		CommandBase::init();
		//lw = LiveWindow::GetInstance();
	
		pneumatics = new Pneumatics( );
		pneumatics->Start();
		WaitCommand(5);
		//vision
		target_ = new BackboardFinder();
		//target_->Start();

//cout << "clock rate "<<sysClkRateGet() << std::endl;
#if !SDMD
		SmartDashboard::PutData("Toggle Drive Mode", new CmdDriveChangeMode( ));
		
		//	Expose the stuff on the Live Window
		//CommandBase::drive->PlaceSensorsOnLiveWindow( lw );
		//CommandBase::shooter->PlaceSensorsOnLiveWindow( lw );
		
		//	Deal with the recording stuff.  Put up a text field for saving the file,
		SmartDashboard::PutString("RecordFile", "record.xml");
		SmartDashboard::PutData("Record Program", new CmdRecordProgram() );
		SmartDashboard::PutData("Stop Recording", new CmdStopRecording() );
		
		//	Do a chooser for picking the files already there for autonomous. 
		sc = new SendableChooser();
		OfferProgramFiles();
		SmartDashboard::PutData("Autonomous Programs", sc );
		

		
		//SmartDashboard::PutNumber( "Shooting Angle", CommandBase::deck->ShooterAngle() );
#endif	
		PrintDriverStationSelection();
		
		//	All done with init
		cout << "CommandBasedRobot::RobotInit complete. Rock and Roll" << std::endl;
	}
	
	//	Autonomous
	
	virtual void AutonomousInit() {
		//	Get a program file choice from the SendableChooser
		//std::string *afile = (std::string *)sc->GetSelected();
		
		//	Load that command and start it
		//PrintDriverStationSelection();
		
		CommandBase::shooter->UpdateBling();
		
//		switch(DriverStationSelection())
//		{
//			case 1:
//				autonomousCommand = new CgAutonomousOne();
//				break;
//			case 2:
//				autonomousCommand = new CgAutonomousTwo();
//				break;
//			case 4:
//				autonomousCommand = (Command *)new CmdReplayProgram( afile->c_str() );
//				break;
//			default:
				autonomousCommand = NULL;
//				break;
//		}
				autonomousCommand->Cancel();
		
		cout << "Autonomous Init complete." << std::endl;
	}
	
	virtual void AutonomousPeriodic()
	{
		//SmartDashboard::PutData( CommandBase::shooter );
		CommandBase::shooter->ShowMotorSpeed();
#if !SDMD
		SmartDashboard::PutString( "Playback", CommandBase::replaying()?"Yes":"No");
		SmartDashboard::PutNumber( "Left Speed:", CommandBase::drive->SpeedLeft() );
		SmartDashboard::PutNumber( "Right Speed:", CommandBase::drive->SpeedRight() );
		SmartDashboard::PutNumber( "Left Clicks:", CommandBase::drive->DistLeft() );

#endif
		Scheduler::GetInstance()->Run();
	}
	
	//	Teleop
	
	virtual void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this code or comment it out.
		if (autonomousCommand != NULL)
		{
			autonomousCommand->Cancel();
			//delete autonomousCommand;
			//autonomousCommand = NULL;
		}
		cout << "Teleop Init complete. Try not to hit anyone" << std::endl;
		CommandBase::shooter->SetFlashBling(false);


	}
	
	virtual void TeleopPeriodic()
	{
		
		Scheduler::GetInstance()->Run();
		cout << "Battery Voltage " << DriverStation::GetInstance()->GetBatteryVoltage() << std::endl;
		

		CommandBase::shooter->PeriodicCheck();
		CommandBase::shooter->UpdateBling();

		  // Vision


		
#if !SDMD
		static int loop = 0;
		if (loop++ % 5 == 0)
		{
			CommandBase::shooter->ShowMotorSpeed();
			//CommandBase::shooter->ShowDiscLoaded();
			SmartDashboard::PutString( "Mode", CommandBase::drive->Mode()==Drive::arcade ? "Arcade" : 
											   "Tank" );
			SmartDashboard::PutString( "Gear", CommandBase::drive->Gear()==Drive::low ? "low" : "high");
			SmartDashboard::PutNumber( "Left Speed:", CommandBase::drive->SpeedLeft() );
			SmartDashboard::PutNumber( "Left Clicks:", CommandBase::drive->DistLeft() );
	
			//SmartDashboard::PutNumber( "Right Speed:", CommandBase::drive->SpeedRight() );
			//SmartDashboard::PutNumber( "Left Clicks:", CommandBase::drive->DistRight() );
			//cout << "Speed, Left " << CommandBase::drive->SpeedLeft() << 
			//			 "  Right " << CommandBase::drive->SpeedRight() << std::endl;
			
			SmartDashboard::PutString( "Recording", CommandBase::recording() ? "Yes" : "No");
	
			//	Debugging info.
			//SmartDashboard::PutNumber( "DRV X", CommandBase::oi->driveX());
			//SmartDashboard::PutNumber( "DRV Y", CommandBase::oi->driveY());
			//SmartDashboard::PutNumber( "OPR Z", CommandBase::oi->operatorZ());

			SmartDashboard::PutNumber( "Shooter Target Speed", CommandBase::shooter->FrontMotorTargetSpeed() );
			CommandBase::shooter->ShowMotorSpeed();
			
			//	Put all the subsystems on the dashboard for the time being.  Let's us look around

			//SmartDashboard::PutData( CommandBase::climber );
			//SmartDashboard::PutData( CommandBase::loader );
			//SmartDashboard::PutData( CommandBase::shooter );
			

			SmartDashboard::PutBoolean( "Air Pressure Full", pneumatics->TankFull() );
			SmartDashboard::PutNumber("Battery Voltage", DriverStation::GetInstance()->GetBatteryVoltage());

			

		}
#endif		
	}

	//	Test
	//
	
	virtual void TestInit()
	{
		//	Note that enabling LiveWindow shuts down the command scheduler

		cout << "**********************" << std::endl << "Entering Test Init" << std::endl;
		//lw->SetEnabled( true );
	}
	
	virtual void TestPeriodic()
	{
		//lw->Run();
	}
	
	//	Disabled
	
	virtual void DisabledInit()
	{
		//lw->SetEnabled( false );
		cout << "**********************" << std::endl << "Enter Disabled Init" << std::endl;
	}
	
	virtual void DisabledPeriodic()
	{
#if !SDMD
		static int loop=0;
		if (loop++ % 2 == 0)
		{
			SmartDashboard::PutBoolean( "Air Pressure Full", pneumatics->TankFull() );
			//SmartDashboard::PutString( "Mode", CommandBase::drive->Mode()==Drive::arcade ? "Arcade" : "Tank" );
			SmartDashboard::PutNumber("Battery Voltage", DriverStation::GetInstance()->GetBatteryVoltage());
			SmartDashboard::PutString("Mode", CommandBase::drive->Mode() == Drive::arcade ? "Arcade" : "Tank");
			SmartDashboard::PutString("Gear", CommandBase::drive->Gear() == Drive::high ? "High" : "Low");

		}
#endif
		return;
	}
	
	void OfferProgramFiles( )
	{
		//	Open the programs folder in the root.  This is where we will put our XML programs.
		DIR *pDir = opendir( "programs" );
		
		if (pDir == NULL)
		{
			// Error
			//SmartDashboard::PutNumber("Error loading program file list",(int)errno );
			cout << "Error loading program file list " << errno << std::endl;
		}
		else
		{
			cout << "Program files found: " << std::endl;
			//	Read through the directory file, getting each entry one at a time, assuming each
			//	such entry is a program file.  Sending a command should create a button for that command.
			while ( dirent * p = readdir( pDir )  )
			{
// This will create a sendable chooser with a list of strings
				std::string *s = new std::string( p->d_name );
				if (*s == "Default.xml")
					sc->AddDefault(p->d_name, (void *)s );
				else
					sc->AddObject( p->d_name, (void *)s );

//				This creates command objects on the dash.  I'd prefer to just create one command
//				and let it grab the sendable chooser.
//				SmartDashboard::PutData( p->d_name, new CmdReplayProgram( p->d_name ));
//				Stuff( p->d_name );
				
				//	This dumps the name to the console
				cout << "\t" << p->d_name << std::endl;
			}
			
			closedir( pDir );
		}
		
		pDir = NULL;
	}
	
	//Prints to the console which Autonomous mode the currently selected
	//button configuration on the dashboard would activate
	void PrintDriverStationSelection()
	{
		switch(DriverStationSelection())
		{
			case 1:
				cout << "CgAutonomousOne : Stationary Autonomous Mode Selected" << std::endl;
				break;
			case 2:
				cout << "CgAutonomousTwo : Turning Autonomous Mode Selected" << std::endl;
				break;
			case 4:
				cout << "Recorded Autonomous Mode Selected - Select on the SmartDashboard" << std::endl;
				break;
			default:
				cout << "Recorded Autonomous Mode Selected - Select on the SmartDashboard" << std::endl;
				break;
		}
	}



};

START_ROBOT_CLASS(CommandBasedRobot);

