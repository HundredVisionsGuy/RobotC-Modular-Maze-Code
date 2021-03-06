#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float diameter = 2.75; // Set the diameter of the wheel here

float getDegrees(float distance)
{
	float degrees = (distance / (PI * diameter)) * 360;
	return degrees;
}

void rightTurn(int deg)
{
	resetGyro(gyroSensor); // first reset gyro
	// adjust degrees for +- 3 degrees
	deg -= 3;

	repeatUntil (getGyroHeading(gyroSensor) > deg) {
		if (getGyroHeading(gyroSensor) < deg - 30) {
			turnRight(10, degrees, 20);
		}
		else {
			turnRight(2, degrees, 10);
		}
	}
}

void leftTurn(int deg)
{
	resetGyro(gyroSensor); // first reset gyro
	wait10Msec(10);

	// get target heading [current heading - degrees + error]
	int targetHeading = -deg + 3;

	repeatUntil (getGyroHeading(gyroSensor) <= targetHeading) {
		if (getGyroHeading(gyroSensor) > targetHeading + 30) {
			turnLeft(10, degrees, 20);
		}
		else {
			turnLeft(2, degrees, 10);
		}
	}
}

task main()
{
	// Maze Challenge
	// by Hundred Visions Guy

	// Wait until the touch sensor is pressed
	waitUntil (getTouchValue(touchSensor) == true);
	wait(400, milliseconds);

	// Reset gyro to 0 degrees heading and wait 1/2 second before moving
	resetGyro(gyroSensor);
	wait(.5, seconds);

	// Drive forward 19 inches
	forward(getDegrees(19), degrees, 30);

	// Turn right 90 degrees
	rightTurn(90);

	// Drive forward 9.5 inches
	forward(getDegrees(9.5), degrees, 30);

	// Turn left 90 degrees
	rightTurn(90);

	// Drive forward 9.5 inches
	forward(getDegrees(9.5), degrees, 30);

	// Try turning left 180 degrees
	leftTurn(180);
}
