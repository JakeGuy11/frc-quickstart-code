#include "Autonomous.h"

// Create a new autonomous manager
MechaPhoenixAuto::MechaPhoenixAuto(double startMillis) : 
    autoStartTime(startMillis), 
    autoCurrentTime(startMillis), 
    elapsedTime(0) { 
        this->autoUpdate(startMillis);
}

// Update some time stuff
void MechaPhoenixAuto::autoUpdate(double currentSystemTime) {
    autoCurrentTime = currentSystemTime;
    elapsedTime = currentSystemTime - autoStartTime;
}

// Get the elapsed time
double MechaPhoenixAuto::getElapsedTime() {
    return elapsedTime;
}

// Get which state we're in
AutoState MechaPhoenixAuto::getState() {
    if (elapsedTime < AutoState::INITIAL_WAIT) {
        currentState = AutoState::INITIAL_WAIT;
        return currentState;
    } else if (elapsedTime < AutoState::SPIN) {
        currentState = AutoState::SPIN;
        return currentState;
    } else if (elapsedTime < AutoState::SPIN_UP_SHOOTER) {
        currentState = AutoState::SPIN_UP_SHOOTER;
        return currentState;
    } else if (elapsedTime < AutoState::SHOOT) {
        currentState = AutoState::SHOOT;
        return currentState;
    } else {
        currentState = AutoState::FINISHED;
        return currentState;
    }
}