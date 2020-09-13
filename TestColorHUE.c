#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
task main()
{

	while(true){

		int colorIzq = getColorHue(sensorIzquierdo);
		int colorDer = getColorHue(sensorDerecho);

		displayCenteredBigTextLine ( 2 ,  "SenIzqHUE %d", colorIzq );
		displayCenteredBigTextLine ( 5 ,  "SenDerHUE %d", colorDer );

	}

}
