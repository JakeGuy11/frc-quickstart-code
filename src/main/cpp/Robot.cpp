// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "CanID.h"

#include <iostream>
#include <sstream>
#include <string>

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/NeutralMode.h>

typedef ctre::phoenix::motorcontrol::can::VictorSPX VictorSPX;
typedef ctre::phoenix::motorcontrol::NeutralMode NeutralMode;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // Begin initialization
  frc::SmartDashboard::PutString("InitMessage", "Initializing...");

  // Read some PDP stats
  frc::PowerDistribution pdp{ID_PDP, TYPE_PDP};

  double v = pdp.GetVoltage();
  double temp = pdp.GetTemperature();

  std::ostringstream initMsg;
  initMsg << temp << "°C @ " << v << "V";

  // Print the new message
  frc::SmartDashboard::PutString("InitMessage", initMsg.str());
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  // Init all the Motor Controllers
  VictorSPX leftMotor(ID_LMOTOR1);
  VictorSPX leftMotor2(ID_LMOTOR2);

  VictorSPX rightMotor(ID_RMOTOR1);
  VictorSPX rightMotor2(ID_RMOTOR2);

  VictorSPX motorS(ID_SHOOTER);
  VictorSPX motorF(ID_FEEDER);

  // Set the neutral modes
  leftMotor.SetNeutralMode(NeutralMode::Brake);
  leftMotor2.SetNeutralMode(NeutralMode::Brake);
  rightMotor.SetNeutralMode(NeutralMode::Brake);
  rightMotor2.SetNeutralMode(NeutralMode::Brake);

  motorS.SetNeutralMode(NeutralMode::Coast);
  motorF.SetNeutralMode(NeutralMode::Coast);

  // Set the inversions
  leftMotor.SetInverted(false);
  leftMotor2.SetInverted(false);
  rightMotor.SetInverted(true);
  rightMotor2.SetInverted(true);

  motorS.SetInverted(false);
  motorF.SetInverted(false);

  // Set some follow stuff
  leftMotor2.Follow(leftMotor);
  rightMotor2.Follow(rightMotor);
}

void Robot::TeleopPeriodic() {
  // This is where all our fun stuff goes :)
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
