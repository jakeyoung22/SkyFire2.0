#ifndef PNEUMATICS_H
#define PNEUMATICS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author WindRiver
 */
class Pneumatics: public Subsystem {
private:
	Compressor *m_compressor;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Pneumatics();
	void InitDefaultCommand();
	void Start();
	bool TankFull();
};

#endif
