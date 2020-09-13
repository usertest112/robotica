#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)

int colorSensorIzquierdo(tSensors sIzquierdo){

	int colorIzquierdo = 0;
	int colorSensor = 0;

	colorIzquierdo = getColorReflected(sIzquierdo);

	if(colorIzquierdo > 60)													{colorSensor = 0;} 		//SE RETORNA 0 -> COLOR BLANCO;
	if(colorIzquierdo >= 10 && colorIzquierdo <= 60){colorSensor = 2;}	   //SE RETORNA 2 -> COLOR POSIBLE VERDE;
	if(colorIzquierdo >= 2 && colorIzquierdo <= 10) {colorSensor = 1;}		//SE RETORNA 1 -> COLOR NEGRO

	return colorSensor;
}

int colorSensorDerecho(tSensors sDerecho){

	int colorDerecho = 0;
	int colorSensor = 0;

	colorDerecho = getColorReflected(sDerecho);

	if(colorDerecho > 60)                       {colorSensor = 0;}        //SE RETORNA 0 -> COLOR BLANCO;
	if(colorDerecho >= 10 && colorDerecho <= 60){colorSensor = 2;}        //SE RETORNA 2 -> COLOR POSIBLE VERDE
	if(colorDerecho >= 2 && colorDerecho <= 10) {colorSensor = 1;}        //SE RETORNA 1 -> COLOR NEGRO;

	return colorSensor;
}

int colorRGBSensorIzquierdo(tSensors sIzquierdo){

	int colorSensor = 2;
	int colorHUE = 0;

	if(getColorReflected(sIzquierdo) < 60){
		colorHUE = getColorHue(sIzquierdo);
		if(colorHUE < 185){colorSensor = 3;}else{colorSensor = 1;}
	}else{colorSensor = 2;}

	return colorSensor;
}

int colorRGBSensorDerecho(tSensors sDerecho){

	int colorSensor = 2;
	int colorHUE = 0;

	if(getColorReflected(sDerecho) < 60){
		colorHUE = getColorHue(sDerecho);
		if(colorHUE < 40){colorSensor = 3;}else{colorSensor = 1;}
	}else{colorSensor = 2;}

	return colorSensor;
}

task main()
{

	int velocidadAvance = 20;
	int velocidadRetroceso = -20;
	int colorIzq = 0;
	int colorDer = 0;
	int colorIzqRGB = 0;
	int colorDerRGB = 0;
	int controlLineaNegra = 0;
	int colorIzqReflected = 0;
	int colorDerReflected = 0;

	while(true){

		colorIzq = colorSensorIzquierdo(sensorIzquierdo);
		colorDer = colorSensorDerecho(sensorDerecho);

 		colorIzqReflected = getColorReflected(sensorIzquierdo);
		colorDerReflected = getColorReflected(sensorDerecho);

		controlLineaNegra = round((((colorIzqReflected - colorDerReflected)/2)+6)*1.6/15);

		if(controlLineaNegra >= 4){controlLineaNegra = 3;}
		if(controlLineaNegra <= -4){controlLineaNegra = -3;}

		switch (controlLineaNegra)
		{
		case 3:
			setMotorSpeed(motorIzquierdo, velocidadAvance*2.7);
			setMotorSpeed(motorDerecho, velocidadRetroceso*2.7);
			break;
		case 2:
			setMotorSpeed(motorIzquierdo, velocidadAvance*2.5);
			setMotorSpeed(motorDerecho, velocidadAvance/2);
			break;
		case 1:
			setMotorSpeed(motorIzquierdo, velocidadAvance*1.5);
			setMotorSpeed(motorDerecho, velocidadAvance/1.2);
			break;
		case 0:
			setMotorSpeed(motorIzquierdo, velocidadAvance);
			setMotorSpeed(motorDerecho, velocidadAvance);
			break;
		case -1:
			setMotorSpeed(motorIzquierdo, velocidadAvance/1.2);
			setMotorSpeed(motorDerecho, velocidadAvance*1.5);
			break;
		case -2:
			setMotorSpeed(motorIzquierdo, velocidadAvance/2);
			setMotorSpeed(motorDerecho, velocidadAvance*2.5);
			break;
		case -3:
			setMotorSpeed(motorIzquierdo, velocidadRetroceso*2.7);
			setMotorSpeed(motorDerecho, velocidadAvance*2.7);
			break;
		}

		if(colorIzq  == 2 ||  colorDer == 2){

			if(colorIzq == 2){
				forward(0.05, rotations, velocidadAvance);
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
				//playTone(1000, 3);
				//sleep(3000);
				//GUARDA EL RGB EN LA VARIABLE colorIzqRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
				forward(0.05, rotations, velocidadAvance);
				//sleep(500);
				colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
				//displayCenteredBigTextLine(3,"colorIzq %d",colorIzqRGB);
				//sleep(3000);
				//COMPRUEBA SI EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
				if(colorIzqRGB == 3){
					//FRENO EL ROBOT
					setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
					//GUARDA EL RGB EN LA VARIABLE colorDerRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
					colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
					//sleep(1000);
					//VERIFICA SI TAMBIEN EL SENSOR DERECHO ESTA SOBRE EL VERDE
					//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
					if(colorDerRGB == 3){
						//displayCenteredBigTextLine(3,"DOBLE VERDE");
						forward(0.3, rotations, velocidadAvance);
						turnLeft(2.5, rotations, velocidadAvance);
						forward(0.5, rotations, velocidadAvance);
						}else{
						//SINO SE GIRA HACIA LA IZQUIERDA
						playTone(1000, 3);
						//displayCenteredBigTextLine(3,"VERDE IZQ");
						forward(0.3, rotations, velocidadAvance);
						turnLeft(1.3, rotations, velocidadAvance);
						forward(0.5, rotations, velocidadAvance);
						}
					}else{
					backward(0.05, rotations, velocidadAvance);
				}
			}

			if(colorDer == 2){
				forward(0.05, rotations, velocidadAvance);
				//FRENA EL ROBOT
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
				//playTone(1000, 3);
				//sleep(3000);
				//GUARDA EL RGB EN LA VARIABLE colorDerRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
				forward(0.05, rotations, velocidadAvance);
				//sleep(500);
				colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
				//displayCenteredBigTextLine(3,"colorDer %d",colorDerRGB);
				//sleep(3000);
				//COMPRUEBA SI EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
				if(colorDerRGB == 3){
					//FRENO EL ROBOT
					setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
					//GUARDA EL RGB EN LA VARIABLE colorIzqRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
					//colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
					//sleep(1000);
					//VERIFICA SI TAMBIEN EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
					//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
					if(colorIzqRGB == 3)
					{
						//displayCenteredBigTextLine(3,"DOBLE VERDE");//2.6
					  forward(0.3, rotations, velocidadAvance);
						turnRight(2.5, rotations, velocidadAvance);
						forward(0.5, rotations, velocidadAvance);
					}else{
						//SINO SE GIRA HACIA LA DERECHA
						playTone(1000, 3);
						//displayCenteredBigTextLine(3,"VERDE DER");
						forward(0.5, rotations, velocidadAvance);
						turnRight(1.3, rotations, velocidadAvance);
						forward(0.5, rotations, velocidadAvance);
						}
					}else{
					backward(0.05, rotations, velocidadAvance);
				}
			}

		}

	}


}
