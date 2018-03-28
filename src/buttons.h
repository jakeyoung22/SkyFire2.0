//	This file contains a macro call for each button
//  The form of each macro call is:
//	BUTTON_SETUP( btn_name, pad, btn_code, action, cmd, arg  )
//
//		btn_name is the variable name for the button
//		pad is the variable for the game pad the button is on
//		btn_code is the constant from UIMAP.H for the button
//		cmd is the name of the command to create an instance of
//		arg is the optional argument for the command constructor
//
//	e.g.:
//		BUTTON_SETUP( m_shooterPickupToggleButton, m_operatorPad, OPR_BTN_SHOOTER_SHOOT, WhenPressed, CmdToggleConveyer, )
//
//	This header will get included in two different files.  Note the lack of a guard constant on
//	this one. :)
//
//	In OI.H, it will get called with one macro expansion definition for BUTTON_SETUP
//	in OI.CPP, it will get included with a different macro expansion definition for BUTTON_SETUP.
//
//	Using the two different expansions, different macro arguments will get assembled to write
//	different code.
//	in the OI.H it will define a button pointer data member
//	In the OI.CPP it will create the instance and assign it to the data member pointer
//		then it will associate the button event with the newly created command
//
//	The idea is to simplify a button definition down to one line of code here instead of
//	3 split over two files.
//
//	Unfortunately, it's not quite this easy.  I also need the definition of the command classes
//	in the OI.CPP expansion, which means the command's header also needs to be included.  Rats.
//	So... to try to keep things simple, I'm going to put the includes here, too.
//	These includes will be invoked whenever BUTTON_HEADERS is defined.  Otherwise, not.  This
//	macro define/include combination will occur early in OI.CPP.
//
#ifdef BUTTON_HEADERS
//	Include each command header here
//#include "Commands/CmdDeckPositionCycle.h"
#include "Commands/CmdGearShiftToggle.h"
//#include "Commands/CmdLiftShiftToggle.h"
//#include "Commands/CmdPrimaryLiftToggle.h"
//#include "Commands/CmdSecondaryLiftClimb.h"
//#include "Commands/CmdSecondaryLiftReverse.h"
#include "Commands/CmdShooterShoot.h"
//#include "Commands/CmdShooterShoot2.h"

//#include "Commands/CmdShooterPusherRetract.h"
#include "Commands/CmdShooterMotorToggle.h"
#include "Commands/CmdTestShooterMotors.h"
//#include "Commands/CmdLiftSecondaryCylindersTopEngage.h"
//#include "Commands/CmdLiftSecondaryCylindersTopDisengage.h"
//#include "Commands/CmdLiftSecondaryCylindersBottomEngage.h"
//#include "Commands/CmdLiftSecondaryCylindersBottomDisengage.h"
#include "Commands/CmdDriveChangeMode.h"

#include "Commands/CmdShooterSpeedIncrease.h"
#include "Commands/CmdShooterSpeedDecrease.h"
#include "Commands/CmdShooterSpeedToggle.h"
#include "Commands/CmdShooterClearJam.h"

#include "Commands/CmdDriveNudge.h"

#include "Commands/CmdShooterLoaderToggle.h"

#include "Commands/CmdShooterBlingToggle.h"
#include "Commands/CmdShooterBlingOnToggle.h"

#else
//	Declare each button here:
//				button name                     pad              button code                     btn event    Command              Argument

//BUTTON_MORE(m_shooterShootButton,                                                              WhenReleased,CmdShooterPusherRetract,                   )
	//Taken out to add a wait to delay the retraction.
	//The wait could be changed to a CommandGroup later.
//BUTTON_SETUP( m_shooterMotorToggleButton,       m_driverPad, 	 DRV_BTN_SHOOTER_ON,             WhenPressed, CmdShooterMotorToggle,                   )
//BUTTON_SETUP( m_deckCycleButton,                m_operatorPad, 	 OPR_BTN_DECK_CYCLE,             WhenPressed, CmdDeckPositionCycle,                    )
//BUTTON_SETUP( m_deckStallButton,		          m_operatorPad,   OPR_BTN_DECK_STALL,	           WhenPressed, CmdDeckToggleStall,                      )
//BUTTON_SETUP( m_primaryLiftToggle,              m_operatorPad,   OPR_BTN_PRIMARY_LIFT,           WhenPressed, CmdPrimaryLiftToggle,                    )
//BUTTON_SETUP( m_deckAngleUp,                    m_operatorPad,   OPR_BTN_ANGLE_UP,               WhenPressed, CmdIncreaseShootingAngle,                )
//BUTTON_SETUP( m_deckAngleDown,                  m_operatorPad,   OPR_BTN_ANGLE_DOWN,             WhenPressed, CmdDecreaseShootingAngle,                )
//BUTTON_SETUP( m_shooterSpeedToggle,             m_operatorPad,   OPR_BTN_SHOOTER_SPEED_TOGGLE,   WhenPressed, CmdShooterSpeedToggle,                   )
//BUTTON_SETUP( m_deckJogUp,                		m_operatorPad,   OPR_BTN_JOG_DECK,               WhenPressed, CmdDeckJogUp,                		 0.5f  )
//BUTTON_SETUP( m_shooterpusherretract,             m_driverPad,   DRV_BTN_PUSHER_RETRACT,          WhenPressed, CmdShooterPusherRetract,                         )


BUTTON_SETUP( m_shooterSpeedToggle,             m_driverPad,   DRV_BTN_SHOOTER_SPEED_TOGGLE,   WhenPressed, CmdShooterSpeedToggle,                   )
BUTTON_SETUP( m_shooterMotorToggleButton,       m_driverPad, 	 DRV_BTN_SHOOTER_ON,             WhenPressed, CmdShooterMotorToggle,                   )
BUTTON_SETUP( m_shooterClearJam,                m_driverPad,   DRV_BTN_CLEAR_JAM,              WhenPressed, CmdShooterClearJam,                0.25f )
BUTTON_SETUP( m_shooterShootButton,             m_driverPad,   DRV_BTN_SHOOTER_SHOOT,          WhenPressed, CmdShooterShoot,                         )

//BUTTON_SETUP( m_driveLiftShiftButton,           m_driverPad, 	   DRV_BTN_LIFT_SHIFT,             WhenPressed, CmdLiftShiftToggle,                      )
BUTTON_SETUP( m_driveGearShiftButton,           m_driverPad,   	 DRV_BTN_GEAR_SHIFT,             WhenPressed, CmdGearShiftToggle,                      )
BUTTON_SETUP( m_driveChangeMode,           m_driverPad,   	 DRV_BTN_CHANGE_MODE,             WhenPressed, CmdDriveChangeMode,                      )
//BUTTON_SETUP(m_driveBlingToggleButton, m_driverPad, DRV_BLING_TOGGLE, WhenPressed, CmdShooterBlingToggle, )
BUTTON_SETUP(m_driveBlingOnToggleButton, m_driverPad, DRV_BLING_ON_TOGGLE, WhenPressed, CmdShooterBlingOnToggle, )
//BUTTON_SETUP( m_secondaryLiftClimb,             m_driverPad,     DRV_BTN_SECONDARY_CLIMB,        WhenPressed, CmdSecondaryLiftClimb,                   )
//BUTTON_SETUP( m_secondaryLiftReverse,           m_driverPad,     DRV_BTN_SECONDARY_OUT,          WhenPressed, CmdSecondaryLiftReverse,                 )
//BUTTON_SETUP( m_secondaryCylindersTopButton, 	  m_driverPad,     DRV_BTN_SECONDARY_TOP_ARMS,     WhenPressed, CmdLiftSecondaryCylindersTopEngage,      )
//BUTTON_MORE(  m_secondaryCylindersTopButton, 	                                                   WhenReleased,CmdLiftSecondaryCylindersTopDisengage,   )
//BUTTON_SETUP( m_secondaryCylindersBottomButton, m_driverPad,     DRV_BTN_SECONDARY_BOTTOM_ARMS,  WhenPressed, CmdLiftSecondaryCylindersBottomEngage,   )
//BUTTON_MORE(  m_secondaryCylindersBottomButton,                                              	   WhenReleased,CmdLiftSecondaryCylindersBottomDisengage,)
//BUTTON_SETUP( m_driveScootFwd,                  m_driverPad,     DRV_BTN_SCOOT_FWD,              WhenPressed, CmdDriveNudge,                     true  )
//BUTTON_SETUP( m_driveScootBck,                  m_driverPad,     DRV_BTN_SCOOT_BCK,              WhenPressed, CmdDriveNudge,                     false )
//BUTTON_SETUP( m_toggleShooterAlignment,         m_driverPad,     DRV_BTN_SHOOTER_BARS_TOGGLE,    WhenPressed, CmdShooterBarsToggle,                    )
#endif
