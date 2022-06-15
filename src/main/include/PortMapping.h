#include <frc/PowerDistribution.h>

// Joystick mapping stuff
#define JOYSTICK_PORT 0
#define SHOOT_BUTTON 0 // Trigger
#define FEED_BUTTON 2
#define SHOOT_RETRACT_BUTTON 6
#define FEED_RETRACT_BUTTON 7

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