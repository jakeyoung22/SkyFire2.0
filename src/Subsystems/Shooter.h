#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include "../robotmap.h"


/*
 * Front Wheel is Green
 * Second Wheel is Orange
 * Back Wheel is Blue
 */

/**
 * Shooter, based on PIDSubsystem to drive the primary shooting motor 
 * at a known speed based on an encoder instead of % motor output
 *
 * @author 1319
 */
class Shooter: public PIDSubsystem {
public:
	enum e_pusher { unknown=0, shoot=1, retract=2};
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	e_pusher m_pusher;
	// set the P, I, and D constants here
	static const double Kp = 0.3;	//todo: These are WRONG... get better numbers
	static const double Ki = 0.005;
	static const double Kd = 0.002;
	static const double Kf = 0.8;
	
	Victor	*m_frontMotor, *m_middleMotor, *m_backMotor;
	Encoder *m_frontEncoder; //, *m_backEncoder;
	
	//DoubleSolenoid *m_solPusher;
	DoubleSolenoid *m_solPusher;
	
	Relay *m_bling, *m_cameraLED;

	float m_targetSpeedFront;

	float m_shooterRawSpeed;
	
	bool m_running;
	bool m_flashBling, m_blingOn;
public:
	Shooter();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	
	//	Properties
	float FrontMotorSpeed();	// in RPM?  %of max RPM or encoder rate?
	bool  OkayToShoot();
	
	float FrontMotorRawSpeed(); //returns the raw speed the front motor is set at
	
	float FrontMotorTargetSpeed();
	
	//	Methods
	void RunMotors( float frontSpeed=SHOOTER_SPEED_FRONT );
	void SetRawMotorSpeed( float frontSpeed );	// This is for internal use, and testing only
	void StopMotors();
	//void PushDisc( bool );	// Pushes bottom disc into rear motor, aka SHOOT!
	
	void ShowMotorSpeed();
	//void ShowDiscLoaded();
	
	void PlaceSensorsOnLiveWindow( LiveWindow *lw );
	
	void IncreaseShooterSpeed();
	void DecreaseShooterSpeed();
	
	void SetBackMotorOnly( float speed );
	
	void MotorSpeedToggle();
	
	void PeriodicCheck();

	void ShooterOnBling();

	Shooter::e_pusher Pusher();	// Returns the Pusher setting


	void Pusher( Shooter::e_pusher value );	// Sets the Pusher to new value

	bool GetBlingOn();				//Returns true if the bling is on, else false
	bool GetBlingFlashing();		//Returns true if the bling is flashing, else false
	bool CameraLit();				//Returns true if the Camera LED Ring is on, else false

	void SetCameraLED(bool lit);	//Turns on the LED ring around the camera if lit is true, else turns it off
	void UpdateBling();				//Updates the bling
	void SetBlingOn(bool blingOn);	//Sets the bling to be on if passed true, else sets it to be off
	void SetFlashBling(bool flash);	//Tells the bling to flash if passed true, else tells it to stay solid
};

#endif
