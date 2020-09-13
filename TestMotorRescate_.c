#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Sensor, S4,     sensorUltrasonido, sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          motorRescate,  tmotorEV3_Medium, PIDControl, encoder)

task main()
{

	if(getColorReflected(sensorCentro) > 1){
		stopAllMotors();
		playTone(1000, 3);
		while(getUSDistance(sensorUltrasonido) > 16){
		 setMotorSpeed(motorRescate, -50);
		 sleep(250);
		 setMotorSpeed(motorRescate, 50);
		 sleep(250);
		 setMotorSpeed(motorDerecho, 50);
		 setMotorSpeed(motorIzquierdo, 50);
		 }
	}
}
