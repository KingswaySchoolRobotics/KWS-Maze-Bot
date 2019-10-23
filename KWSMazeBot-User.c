#pragma config(UserModel, "D:/Github/KWS-Maze-Bot/KWSMazeBot.h")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "KWSMazeBot.c"

task gyroTask(){
	while (true){
		gyrodrift();
}}

task Display(){
	while(true){
		DisplayVars();
}}

task Data(){
	while(true){
		DataCollection();
}}
task main()
{

	setMotorBrakeMode(LeftMotor, motorBrake);
	setMotorBrakeMode(RightMotor, motorBrake);

	ProgFinnished = false;
	startTask(gyroTask);
	startTask(Display);
	startTask(Data);
	delay(500);
	playSound(soundHeadlightsOn);
	while (!ProgFinnished) {
		global_1 = getGyroHeading(Gyro); //series 1
		global_2 = gyroValue; // 2
		global_3 = gyroError; // 3
		global_5 = getMotorSpeed(RightMotor); //5
		global_6 = getMotorSpeed(LeftMotor); //6
		//insert MazeBot code here

		//End of MazeBot Code
		ProgFinnished = true;
	}
}
