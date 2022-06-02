#include "DriveStructure.h"

DriveStructure::DriveStructure(int rID, int r2ID, int lID, int l2ID, int sID, int fID) {
    // Attach all the Motor Controllers
    VictorSPX leftMotor(lID);
    VictorSPX leftMotor2(l2ID);

    VictorSPX rightMotor(rID);
    VictorSPX rightMotor2(r2ID);

    VictorSPX motorS(sID);
    VictorSPX motorF(fID);

    rMotor = &rightMotor;
}