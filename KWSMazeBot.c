#pragma systemFile

bool ProgFinnished;

#define   DATALOG_SERIES_0    0
#define   DATALOG_SERIES_1    1
#define   DATALOG_SERIES_2    2
#define   DATALOG_SERIES_3    3
#define   DATALOG_SERIES_4    4
#define   DATALOG_SERIES_5    5
#define   DATALOG_SERIES_6    6
#define   DATALOG_SERIES_7    7
#define   DATALOG_SERIES_8    8

long gyroValue;
long gyroError;

int   global_1 = 0;
int   global_2 = 0;
int   global_3 = 0;
int   global_4 = 0;
int   global_5 = 0;
int   global_6 = 0;
int   global_7 = 0;
int   global_8 = 0;

void DataCollection () /* ignore values on bottom of screen only graph values are valid */
{
	int loops = 0;
	datalogClear();
	while(true)
	{
		global_1 = getGyroHeading(Gyro); //series 1
		global_2 = gyroValue; // 2
		global_3 = gyroError; // 3
		//	global_4 = getColorHue(BallColor); //4
		global_5 = getMotorSpeed(RightMotor); //5
		global_6 = getMotorSpeed(LeftMotor); //6
		//	global_7 = getMotorSpeed(Intake); //7
		//	global_8 = getMotorSpeed(CubeClaw); //8

		datalogDataGroupStart();
		datalogAddValue( DATALOG_SERIES_0, global_1);
		datalogAddValue( DATALOG_SERIES_1, global_2 );
		datalogAddValue( DATALOG_SERIES_2, global_3 );
		datalogAddValue( DATALOG_SERIES_3, global_4 );
		datalogAddValue( DATALOG_SERIES_4, global_5 );
		datalogAddValue( DATALOG_SERIES_5, global_6 );
		datalogAddValue( DATALOG_SERIES_6, global_7 );
		datalogAddValue( DATALOG_SERIES_7, global_8 );
		datalogDataGroupEnd();

		wait1Msec(10);
		datalogAddValueWithTimeStamp( DATALOG_SERIES_3, global_3++ );
		wait1Msec(10);
		datalogAddValueWithTimeStamp( DATALOG_SERIES_3, global_3++ );

		// Repeat sequence every 360 loops
		if(loops++ == 360)
			loops = 0;

		// loop delay
		wait1Msec(10);
	}
}

/*void GyroValueReset(){
	gyroValue=0;
	gyroError=0;
	resetGyro(Gyro);
}*/

void gyrodrift()
{
	long rate;
	long angle, lastAngle;
	lastAngle = 0;
	gyroError=0;
	// Change sensitivity, this allows the rate reading to be higher
	setGyroSensitivity(Gyro, gyroNormalSensitivity);
	//Reset the gyro sensor to remove any previous data.
	resetGyro(Gyro);
	wait1Msec(1000);
	repeat (forever) {
		rate = getGyroRate(Gyro);
		angle = getGyroDegrees(Gyro);
		// If big rate then ignore gyro changes
		if( abs( rate ) < 2 )
		{
			if( angle != lastAngle )
				gyroError += lastAngle - angle;
		}
		lastAngle = angle;
		gyroValue = angle + gyroError;
		wait1Msec(10);
	}
}

void DisplayVars() {
	displayTextLine(line1,"Gyro=%d",getGyroDegrees(Gyro));
	displayTextLine(line2, "Distance=%d",getDistanceValue(Ultrasonic));
	displayVariableValues(line3,getMotorSpeed(RightMotor));
	displayVariableValues(line4,getMotorSpeed(LeftMotor));
	//displayVariableValues(line4,global_2);
	//displayVariableValues(line5,global_3);

}

void mazeBotLeft(int speed = 50) {
	gyroValue=0;
	resetGyro(Gyro);
	while (getGyroDegrees(Gyro) > 91 || getGyroDegrees(Gyro) < 89) {
		setMotorSpeed(LeftMotor, speed);
		setMotorSpeed(RightMotor, -speed);
	}
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor, 0);
}

void mazeBotRight(int speed = 50) {
	gyroValue=0;
	resetGyro(Gyro);
	while (getGyroDegrees(Gyro) < -91 || getGyroDegrees(Gyro) > -89) {
		setMotorSpeed(LeftMotor, -speed);
		setMotorSpeed(RightMotor, speed);
	}
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor, 0);
}

void mazeBotStop(){
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor,0);
}

void mazeBotDrive (int speed) {
	setMotorSpeed(LeftMotor, -speed);
	setMotorSpeed(RightMotor, -speed);
}

/*void mazeBotDegrees(int BotDegree ,int speed = 50) {
	resetGyro(Gyro);
	if (BotDegree>0) {
		//if Right Deg
	while (gyroValue > (BotDegree+1) || gyroValue < (BotDegree-1)) {
		setMotorSpeed(LeftMotor, -speed);
		setMotorSpeed(RightMotor, speed);
	}
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor, 0);
} else {
	//if Left Deg
	while (gyroValue < -(BotDegree+1) || gyroValue > -(BotDegree-1)) {
		setMotorSpeed(LeftMotor, speed);
		setMotorSpeed(RightMotor, -speed);
	}
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor, 0);
}
}
*/
