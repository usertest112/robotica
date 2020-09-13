#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)

task main()
{

	int resultIzq = 0;
	int resultDer = 0;
	int resultCen = 0;



	while(true){

		int colorIzqRef = getColorReflected(sensorIzquierdo);
		int colorDerRef = getColorReflected(sensorDerecho);
		int colorCenRef = getColorReflected(sensorCentro);

		int colorIzqAmb = getColorAmbient(sensorIzquierdo);
		int colorDerAmb = getColorAmbient(sensorDerecho);
		int colorCenAmb = getColorAmbient(sensorCentro);

		int colorIzqSat = getColorSaturation(sensorIzquierdo);
		int colorDerSat = getColorSaturation(sensorDerecho);
		int colorCenSat = getColorSaturation(sensorCentro);

		resultIzq = colorIzqRef - colorIzqSat + colorIzqAmb;
		resultDer = colorDerRef - colorDerSat + colorDerAmb;
		resultCen = colorCenRef - colorCenSat + colorCenAmb;

		displayCenteredBigTextLine ( 1 ,  "SenIzq %d", resultIzq );
		displayCenteredBigTextLine ( 3 ,  "SenDer %d", resultDer );
		displayCenteredBigTextLine ( 5 ,  "SenCen %d", resultCen );

		sleep(100);

		//eraseDisplay();

	}

}
