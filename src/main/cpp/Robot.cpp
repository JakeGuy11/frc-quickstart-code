// Copyright (c) 2022, JakeGuy11 and FRC Team 7722

#include "Robot.h"

// TODO: put in separate file (someone who knows more about headers n stuff can do that)
double mapValueFromZeroOne(double inValue, double minOut, double maxOut) {
  return minOut + ((maxOut - minOut) * inValue);
}

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  initPDP();
  initMotorControllers(NeutralMode::Brake, NeutralMode::Brake);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *\
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { }

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
  autoManager = MechaPhoenixAuto(frc::Timer::GetFPGATimestamp().value());
  fmt::print("Hold on, shit's about to get messy :)");
  fmt::print("(I haven't tested the auto yet, move everything out of the way!)");
}

void Robot::AutonomousPeriodic() {
  autoManager.autoUpdate(frc::Timer::GetFPGATimestamp().value());

  switch (autoManager.getState()) {
    case AutoState::INIT:
      // Do nothing
      break;
    case AutoState::INITIAL_WAIT:
      // Still do nothing :)
      break;
    case AutoState::SPIN:
      // Spin the robot SLOWLY
      mRight.Set(VictorSPXControlMode::PercentOutput, 0.3);
      mLeft.Set(VictorSPXControlMode::PercentOutput, -0.3);
      break;
    case AutoState::SPIN_UP_SHOOTER:
      // Turn on the shooter motor
      mRight.Set(VictorSPXControlMode::PercentOutput, 0.0);
      mLeft.Set(VictorSPXControlMode::PercentOutput, 0.0);

      mShoot.Set(VictorSPXControlMode::PercentOutput, 0.8);
      break;
    case AutoState::SHOOT:
      // Turn on the feeder to actually fire a ball
      mShoot.Set(VictorSPXControlMode::PercentOutput, 0.8);
      mFeed.Set(VictorSPXControlMode::PercentOutput, 0.8);
      break;
    case AutoState::FINISHED:
      // no thoughts head empty
      mRight.Set(VictorSPXControlMode::PercentOutput, 0.0);
      mLeft.Set(VictorSPXControlMode::PercentOutput, 0.0);
      mShoot.Set(VictorSPXControlMode::PercentOutput, 0.0);
      mFeed.Set(VictorSPXControlMode::PercentOutput, 0.0);
      break;
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
  double x = stick.GetX() * S_JOYSTICK;  // In terms of arcade drive, this is turn
  double y = -stick.GetY() * S_JOYSTICK;  // In terms of arcade drive, this is speed

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
  bool shoot = stick.GetTrigger();
  bool feed = stick.GetRawButton(FEED_BUTTON);

  bool retractShoot = stick.GetRawButton(SHOOT_RETRACT_BUTTON);
  bool retractFeed = stick.GetRawButton(FEED_RETRACT_BUTTON);

  int shootValue;
  int feedValue;

  // Update the mode
  if (stick.GetRawButton(SOFT_MODE_BUTTON)) hardMode = false;
  else if (stick.GetRawButton(HARD_MODE_BUTTON)) hardMode = true;

  // Update the *values* for shoot and feed
  if (retractShoot) shootValue = -1;
  else if (shoot) shootValue = 1;
  else shootValue = 0;

  if (retractFeed) feedValue = -1;
  else if (feed) feedValue = 1;
  else feedValue = 0;

  // Update the SHOOTER
  if (shootValue != lastShooterState) {
    // Update the SHOOTER
    if (hardMode) mShoot.Set(VictorSPXControlMode::PercentOutput, shootValue * S_SHOOTER_MOTOR_HARD);
    else mShoot.Set(VictorSPXControlMode::PercentOutput, shootValue * S_SHOOTER_MOTOR_SOFT);
    lastShooterState = shootValue;
  }

  // Update the FEEDER
  if (feedValue != lastFeederState) {
    // Update the FEEDER
    if (hardMode) mFeed.Set(VictorSPXControlMode::PercentOutput, feedValue * S_FEEDER_MOTOR_HARD);
    else mFeed.Set(VictorSPXControlMode::PercentOutput, feedValue * S_SHOOTER_MOTOR_SOFT);
    lastFeederState = feedValue;
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
