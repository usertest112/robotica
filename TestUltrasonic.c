#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Sensor, S4,     sensorUItrasonic, sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          motorRescate,  tmotorEV3_Medium, PIDControl, encoder)
task main()
{
	bool limiteUltrasonic = true;
	while(limiteUltrasonic){
		if(getUSDistance(sensorUItrasonic)<= 5){
			stopAllMotors();
			sleep(2000);
			forward(0.05, rotations, 20);
			turnLeft(1.2, rotations, 20);
			forward(1.5, rotations, 20);
			turnRight(1.2, rotations, 20);
			forward(3.5, rotations, 20);
			turnRight(1.2, rotations, 20);
			forward(1.5, rotations, 20);
			turnLeft(1.2, rotations, 20);
			forward(0.05, rotations, 20);
		}else{
			setMotorSpeed(motorIzquierdo, 20);
			setMotorSpeed(motorDerecho, 20);
		}


	}


}
