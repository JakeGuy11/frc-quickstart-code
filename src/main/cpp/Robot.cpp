// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#define FEED_BUTTON 5

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  initPDP();
  initMotorControllers(NeutralMode::Brake, NeutralMode::Coast);
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
  // Set all our motors to nothing
  mRight.Set(VictorSPXControlMode::PercentOutput, 0.0);
  mLeft.Set(VictorSPXControlMode::PercentOutput, 0.0);
  lastDriveRight = 0.0;
  lastDriveLeft = 0.0;

  mShoot.Set(VictorSPXControlMode::PercentOutput, 0.0);
  mFeed.Set(VictorSPXControlMode::PercentOutput, 0.0);
  lastShooterState = false;
  lastFeederState = false;
}

void Robot::TeleopPeriodic() {
  // This is where all our fun stuff goes :)
  // Read the joystick, calculate the drive stuff
  double x = stick.GetX();  // In terms of arcade drive, this is speed
  double y = stick.GetY();  // In terms of arcade drive, this is turn

  double leftPower = (y + x) / 2;
  double rightPower = (y - x) / 2;

  // Update the LEFT drive
  if (leftPower != lastDriveLeft) {
    // Update the LEFT drive
    mLeft.Set(VictorSPXControlMode::PercentOutput, leftPower * S_LEFT_DRIVE);
    lastDriveLeft = leftPower;
  }

  // Update the RIGHT drive
  if (rightPower != lastDriveRight) {
    // Update the RIGHT drive
    mRight.Set(VictorSPXControlMode::PercentOutput, rightPower * S_RIGHT_DRIVE);
    lastDriveRight = rightPower;
  }

  // Update the Trigger and stuff
  bool trigger = stick.GetTrigger();
  bool thumbButton = stick.GetRawButton(FEED_BUTTON);

  // Update the SHOOTER
  if (trigger != lastShooterState) {
    // Update the SHOOTER
    mShoot.Set(VictorSPXControlMode::PercentOutput, trigger * S_SHOOTER_MOTOR);
    lastShooterState = trigger;
  }

  // Update the FEEDER
  if (thumbButton != lastFeederState) {
    // Update the FEEDER
    mFeed.Set(VictorSPXControlMode::PercentOutput, thumbButton * S_FEEDER_MOTOR);
    lastFeederState = thumbButton;
  } 
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::initPDP() {
  // Begin initialization
  frc::SmartDashboard::PutString("InitMessage", "Initializing...");

  double v = pdp.GetVoltage();
  double temp = pdp.GetTemperature();

  std::ostringstream initMsg;
  initMsg << temp << "°C @ " << v << "V";

  // Print the new message
  frc::SmartDashboard::PutString("InitMessage", initMsg.str());
}

void Robot::initMotorControllers(NeutralMode driveNeutralMode, NeutralMode scoreNeutralMode) {
  // Do all the attachment stuff here
  // Set the neutral modes
  mRight.SetNeutralMode(driveNeutralMode);
  mRight2.SetNeutralMode(driveNeutralMode);
  mLeft.SetNeutralMode(driveNeutralMode);
  mLeft2.SetNeutralMode(driveNeutralMode);
  

  mShoot.SetNeutralMode(scoreNeutralMode);
  mFeed.SetNeutralMode(scoreNeutralMode);

  // Set the inversions
  mRight.SetInverted(false);
  mRight2.SetInverted(false);
  mLeft.SetInverted(true);
  mLeft2.SetInverted(true);

  mShoot.SetInverted(false);
  mFeed.SetInverted(false);

  // Set some follow stuff
  mRight2.Follow(mRight);
  mLeft2.Follow(mLeft);
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
