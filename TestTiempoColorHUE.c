#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
task main()
{
 int tiempoLectura = 1;

	while(tiempoLectura > -1){

		int colorIzq = getColorHue(sensorIzquierdo);
		int colorDer = getColorHue(sensorDerecho);

		displayCenteredBigTextLine ( 1 ,  "SenIzqHUE %d", colorIzq );
		displayCenteredBigTextLine ( 3 ,  "SenDerHUE %d", colorDer );
		displayCenteredBigTextLine ( 5 ,  "tiempoLectura %d", tiempoLectura );

		tiempoLectura--;
		sleep(1000);
	}

}
