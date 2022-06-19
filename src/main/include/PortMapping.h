#include <frc/PowerDistribution.h>

// Joystick mapping stuff
#define JOYSTICK_PORT 0
#define FEED_BUTTON 2
#define SHOOT_RETRACT_BUTTON 4
#define FEED_RETRACT_BUTTON 3
#define SOFT_MODE_BUTTON 10
#define HARD_MODE_BUTTON 11

// Other CAN Devices
#define ID_PDP 0
#define TYPE_PDP frc::PowerDistribution::ModuleType::kCTRE

// Motor Controllers
#define ID_RMOTOR1 12
#define ID_RMOTOR2 13

#define ID_LMOTOR1 10
#define ID_LMOTOR2 11

#define ID_SHOOTER 15
#define ID_FEEDER 16