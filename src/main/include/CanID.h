#include <frc/PowerDistribution.h>

// The Joystick (not technically CAN but shut up)
#define JOYSTICK_PORT 0

// Other CAN Devices
#define ID_PDP 0
#define TYPE_PDP frc::PowerDistribution::ModuleType::kCTRE

// Motor Controllers
#define ID_RMOTOR1 10 
#define ID_RMOTOR2 11

#define ID_LMOTOR1 12
#define ID_LMOTOR2 13

#define ID_SHOOTER 14
#define ID_FEEDER 15