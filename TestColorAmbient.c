#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
task main()
{

	while(true){

		int colorIzq = getColorAmbient(sensorIzquierdo);
		int colorDer = getColorAmbient(sensorDerecho);

		displayCenteredBigTextLine ( 2 ,  "SenIzqAmb %d", colorIzq );
		displayCenteredBigTextLine ( 5 ,  "SenDerAmb %d", colorDer );

	}

}
