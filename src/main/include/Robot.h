// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include "CanID.h"
#include "Sensitivity.h"

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/NeutralMode.h>
typedef ctre::phoenix::motorcontrol::can::VictorSPX VictorSPX;
typedef ctre::phoenix::motorcontrol::VictorSPXControlMode VictorSPXControlMode;
typedef ctre::phoenix::motorcontrol::NeutralMode NeutralMode;
typedef frc::PowerDistribution PowerDistribution;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

  void initPDP();
  void initMotorControllers(NeutralMode driveNeutralMode, NeutralMode scoreNeutralMode);

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  frc::Joystick stick{JOYSTICK_PORT};

  VictorSPX mRight      {ID_RMOTOR1};
  VictorSPX mRight2     {ID_RMOTOR2};
  VictorSPX mLeft       {ID_LMOTOR1};
  VictorSPX mLeft2      {ID_LMOTOR2};

  VictorSPX mShoot      {ID_SHOOTER};
  VictorSPX mFeed       {ID_FEEDER};
  PowerDistribution pdp {ID_PDP, TYPE_PDP};

  bool lastShooterState;
  bool lastFeederState;
  double lastDriveRight;
  double lastDriveLeft;

};
