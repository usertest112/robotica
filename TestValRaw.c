#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)

task main()
{

	while(true){

		displayCenteredTextLine ( 1 ,  "SenIzqRaw %d", SensorRaw[S1] );
		displayCenteredTextLine ( 2 ,  "SenDerRaw %d", SensorRaw[S2] );
		displayCenteredTextLine ( 3 ,  "SenCenRaw %d", SensorRaw[S3] );
		displayCenteredTextLine ( 4 ,  "SenIzqVal %d", SensorValue[S1] );
		displayCenteredTextLine ( 5 ,  "SenDerVal %d", SensorValue[S2] );
		displayCenteredTextLine ( 6 ,  "SenCenVal %d", SensorValue[S3] );

	}

}
