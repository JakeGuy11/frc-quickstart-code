#pragma once

enum AutoState {
    INIT = 0,
    INITIAL_WAIT = 5000,
    SPIN = 8000,
    SPIN_UP_SHOOTER = 9000,
    SHOOT = 13000,
    FINISHED = -1
};

class MechaPhoenixAuto {
    public:
        MechaPhoenixAuto(double startMillis);

        void autoUpdate(double currentSystemTime);

        double getElapsedTime();
        AutoState getState();

    private:
        double autoStartTime;
        double autoCurrentTime;
        double elapsedTime;

        AutoState currentState = AutoState::INIT;
};