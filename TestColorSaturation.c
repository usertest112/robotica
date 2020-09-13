#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)

task main()
{

	while(true){

		int colorIzq = getColorSaturation(sensorIzquierdo);
		int colorDer = getColorSaturation(sensorDerecho);
		int colorCen = getColorSaturation(sensorCentro);

		displayCenteredBigTextLine ( 1 ,  "SenIzqSat %d", colorIzq );
		displayCenteredBigTextLine ( 3 ,  "SenDerSat %d", colorDer );
		displayCenteredBigTextLine ( 5 ,  "SenDerSat %d", colorCen );

	}

}
