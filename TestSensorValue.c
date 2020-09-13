#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)

task main()
{

	while(true){

		displayCenteredBigTextLine ( 1 ,  "SenIzq %d", SensorValue[S1] );
		displayCenteredBigTextLine ( 3 ,  "SenDer %d", SensorValue[S2] );
		displayCenteredBigTextLine ( 5 ,  "SenCen %d", SensorValue[S3] );

	}

}
