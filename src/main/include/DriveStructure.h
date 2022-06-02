#pragma once

#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/NeutralMode.h>

typedef ctre::phoenix::motorcontrol::can::VictorSPX VictorSPX;
typedef ctre::phoenix::motorcontrol::NeutralMode NeutralMode;

class DriveStructure {
    private:
        VictorSPX *rMotor;
        VictorSPX *rMotor2;
        VictorSPX *lMotor;
        VictorSPX *lMotor2;

        VictorSPX *sMotor;
        VictorSPX *fMotor;
    
    public:
        DriveStructure(int rID, int r2ID, int lID, int l2ID, int sID, int fID);
        void setDriveNeutralModes(NeutralMode modes);
        void setScoreNeutralModes(NeutralMode modes);
        
        void feed(double amount);
        void shoot(double amount);
        void drive(double x, double y);
};