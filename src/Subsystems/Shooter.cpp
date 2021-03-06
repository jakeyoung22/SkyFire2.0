#include "Shooter.h"
#include "SmartDashboard/SmartDashboard.h"
#include "../Robotmap.h"
#include "../Commands/CmdTestShooterMotors.h"

Shooter::Shooter() : PIDSubsystem("Shooter", Kp, Ki, Kd, Kf)
{
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	
	m_frontMotor = new Victor(PWM_FRONT_SHOOTER_MOTOR);
	m_middleMotor = new Victor(PWM_MIDDLE_SHOOTER_MOTOR );
	m_backMotor = new Victor(PWM_BACK_SHOOTER_MOTOR);
	m_frontEncoder = new Encoder(GPIO_FRONT_SHOOTER_ENCODER_A, GPIO_FRONT_SHOOTER_ENCODER_B);
	m_frontEncoder->SetDistancePerPulse( 1 / SHOOTER_FRONT_ENC_CPR );
	m_frontEncoder->SetReverseDirection( true );
	
	m_frontEncoder->Start();


	m_solPusher = new DoubleSolenoid(SOL_PUSHER_SHOOT, SOL_PUSHER_RETRACT);
	m_bling = new Relay(RELAY_BLING);
	//m_cameraLED = new Relay(RELAY_CAMERA_LED);
	m_cameraLED = new Relay(RELAY_CAMERA_LED);


	//PushDisc(false);
	
	m_shooterRawSpeed = SHOOTER_RAW_SPEED;
	
	//	We're scaling the input in ReturnPIDInput to be between 0 & 1
	//	by dividing the FrontMotorSpeed by the maximum
	SetInputRange( 0, SHOOTER_SPEED_MAX);
	Disable();
	
	m_running = false;
	
	m_frontMotor->SetSafetyEnabled( SAFETY_ENABLED );
	m_middleMotor->SetSafetyEnabled( SAFETY_ENABLED );
	m_backMotor->SetSafetyEnabled( SAFETY_ENABLED );



	m_flashBling = false;
	m_blingOn = false;
	Pusher(retract);
}

double Shooter::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
#if PID
	float t = FrontMotorSpeed();
	cout << "Actual Speed: " << t << std::endl;
	return (FrontMotorSpeed()/SHOOTER_SPEED_MAX );
#else
	return 1;
#endif
}

void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	
#if PID
	cout << "PID Output Speed: " << output << std::endl;
	SetRawMotorSpeed( output );
#endif
}


void Shooter::InitDefaultCommand()
{
	//	No default command
	//fix me: For testing, etc. Only... this needs to die quick.  No default command.
	//If uncommented in the future, remove the space from "fix me" above.
	//SetDefaultCommand( new CmdTestShooterMotors() );
}
Shooter::e_pusher Shooter::Pusher()
{
	return m_pusher;
}

bool Shooter::GetBlingOn() {
	return m_blingOn;
}

bool Shooter::GetBlingFlashing() {
	return m_flashBling;
}
float Shooter::FrontMotorSpeed()
{
	if (m_frontEncoder != NULL)
		return m_frontEncoder->GetRate();
	else
		return 0;
}

bool  Shooter::OkayToShoot()
{
	return (FrontMotorSpeed() > SHOOTER_OKAY_TO_SHOOT);
}

bool Shooter::CameraLit() {
	return m_cameraLED->Get() == Relay::kForward;
}

float Shooter::FrontMotorRawSpeed()
{
	return m_frontMotor->Get();
}

float Shooter::FrontMotorTargetSpeed()
{
	return m_shooterRawSpeed;
}

//	Methods

//	Sets the motors to spinning.
//
//	Note that frontSpeed should be a SetPoint for an encoder rate to be managed by the PID
void Shooter::RunMotors( float frontSpeed )
{
#if PID
	SetSetpoint( frontSpeed );
	Enable();
	m_blingOn = true;
	m_flashBling = true;
#else
	SetRawMotorSpeed( m_shooterRawSpeed );
	m_running = true;
	m_blingOn = true;
	m_flashBling = true;
	
#endif
}

//	This will be internally used by the PID setter.
//	It should not be called directly by commands, except for testing/debugging
void Shooter::SetRawMotorSpeed( float frontSpeed )
{
	cout << "SetRawMotorSpeed(" << frontSpeed << ")" << std::endl;
	if (frontSpeed > 1) frontSpeed = 1;
	m_frontMotor->SetSpeed( frontSpeed );
	m_middleMotor->SetSpeed( frontSpeed * SHOOTER_SPEED_FACTOR);
	m_backMotor->SetSpeed( frontSpeed * SHOOTER_SPEED_FACTOR * SHOOTER_SPEED_FACTOR );
}
void Shooter::StopMotors()
{
	cout << "Stopping Motors... Did you kill someone?" << std::endl;
	//	Turn off PID control of the front motor.  Not sure if that stops it, so...
#if PID
	Disable();
	m_blingOn = false;
	m_flashBling = false;
#else
	m_running = false;
	m_blingOn = false;
	m_flashBling = false;
#endif
	//	Stop both motors as well.  m_backMotor->SetSpeed( backSpeed );
	m_frontMotor->StopMotor();
	m_middleMotor->StopMotor();
	m_backMotor->StopMotor();
}

void Shooter::SetCameraLED(bool lit) {
	m_cameraLED->Set(lit ? Relay::kForward : Relay::kReverse);
}


void Shooter::Pusher(Shooter::e_pusher value)
{
	switch(value)
	{
		case retract:
			m_solPusher->Set(DoubleSolenoid::kReverse);
			break;
		case shoot:
			m_solPusher->Set(DoubleSolenoid::kForward);
			break;
		default:
			m_solPusher->Set(DoubleSolenoid::kOff);
			break;
	}

	m_pusher = value;
}

void Shooter::ShowMotorSpeed()
{
#if !SDMD
	SmartDashboard::PutNumber( "Shooter Speed", FrontMotorSpeed() );
	cout << "Shooter Speed:" << FrontMotorSpeed()<< std::endl;
#endif
}

/*void Shooter::ShowDiscLoaded()
{
#if !SDMD
	//SmartDashboard::PutString( "Disc Loaded", HaveDisc() ? "Yes" : "No" );
#endif
}
*/
void Shooter::PlaceSensorsOnLiveWindow(LiveWindow *lw)
{
	lw->AddActuator("Shooter", "Front Motor", m_frontMotor );
	lw->AddSensor( "Shooter", "Encoder", m_frontEncoder );
		
	//lw->AddActuator("Shooter", "Disc Pusher", m_solPusher );
}

void Shooter::IncreaseShooterSpeed()
{
	m_shooterRawSpeed += SHOOTER_SPEED_INCREMENT;
	if(m_shooterRawSpeed > 1.0f)
	{
		m_shooterRawSpeed = 1.0f;
	}
}

void Shooter::DecreaseShooterSpeed()
{
	m_shooterRawSpeed -= SHOOTER_SPEED_INCREMENT;
	if(m_shooterRawSpeed < 0.0f)
	{
		m_shooterRawSpeed = 0.0f;
	}
}

void Shooter::SetBackMotorOnly( float speed )
{
	cout << "SetBackMotorOnly(" << speed << ")" << std::endl;
	if (speed > 1)
		speed = 1;
	else if (speed < -1)
		speed = -1;
	
	m_backMotor->SetSpeed( speed  );
	m_frontMotor->StopMotor();
	m_middleMotor->StopMotor();
}

void Shooter::MotorSpeedToggle()
{
	if(m_shooterRawSpeed != SHOOTER_RAW_SPEED)
	{
		m_shooterRawSpeed = SHOOTER_RAW_SPEED;
	}
	else
	{
		m_shooterRawSpeed = SHOOTER_SLOW_SPEED;
	}
	
	if(FrontMotorRawSpeed() > 0.0f)
	{
		RunMotors();
	}
		
}



void Shooter::UpdateBling() {
	if(m_blingOn && (!m_flashBling || (m_flashBling && DriverStation::GetInstance()->GetPacketNumber() % 12 >= 6))) {
		m_bling->Set(Relay::kForward);
	}
	else {
		m_bling->Set(Relay::kReverse);
	}
}

void Shooter::SetBlingOn(bool blingOn) {
	m_blingOn = blingOn;
}

void Shooter::SetFlashBling(bool flash) {
	m_flashBling = flash;


}



#define SHOOTER_SPEED_FRONT_LOCAL   (SHOOTER_SPEED_MAX * 0.85f)
#define SHOOTER_ADJ_SCALE_LOCAL     0.20f

void Shooter::PeriodicCheck()
{
#if false
	
	if (m_running)
	{
		//	Calculate raw error, negative is over target, positive under
		float error = SHOOTER_SPEED_FRONT_LOCAL - FrontMotorSpeed(); 
		
		//	Turn that into a ratio 
		float factor = error / SHOOTER_SPEED_FRONT_LOCAL;
		
		//	Tone it down a bit
		factor *= SHOOTER_ADJ_SCALE_LOCAL;
		
		if (factor > 0.05f)
			factor = 0.05f;
		else if (factor < -0.05f)
			factor = -0.05f;

		//	Adjust the speed by the factor
		m_shooterRawSpeed += (factor );
		
		//	And apply it
		SetRawMotorSpeed( m_shooterRawSpeed );
	}
#endif
	
#if false
	
	if (m_shooterRawSpeed > 0.05f && FrontMotorSpeed() > 90.0f )
	{
	if (FrontMotorSpeed() < 99.0f)
		m_shooterRawSpeed += 0.005f;
	else if (FrontMotorSpeed() > 101.0f)
		m_shooterRawSpeed -= 0.005f;
	
	SetRawMotorSpeed( m_shooterRawSpeed );
	}
#endif
}


