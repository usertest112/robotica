#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int colorSensorIzquierdo(tSensors sIzquierdo){

	int colorIzquierdo = 0;
	int colorBlanco = 0;

	colorIzquierdo = getColorReflected(sIzquierdo);

	//PREGUNTA SI EL SENSOR IZQUIERDO ESTA EN EL BLANCO
	//SE TOMA COMO VALOR DE REFERENCIA EN BLANCO
	//COMO VALOR SUPERIOR AL 27
	if(colorIzquierdo > 10)												{colorBlanco = 0;} 		//SE RETORNA 0 -> COLOR BLANCO;
	if(colorIzquierdo >= 4 && colorIzquierdo <= 9){colorBlanco = 2;}	  //SE RETORNA 2 -> COLOR POSIBLE VERDE;
	if(colorIzquierdo >= 1 && colorIzquierdo <= 3){colorBlanco = 1;}		//SE RETORNA 1 -> COLOR NEGRO


	return colorBlanco;
}

int colorSensorDerecho(tSensors sDerecho){

	int colorDerecho = 0;
	int colorBlanco = 0;


	colorDerecho = getColorReflected(sDerecho);

	//PREGUNTA SI EL SENSOR DERECHO ESTA EN EL BLANCO
	//SE TOMA COMO VALOR DE REFERENCIA EN BLANCO
	//COMO VALOR SUPERIOR AL 45
	if(colorDerecho > 10)                      {colorBlanco = 0;}        //SE RETORNA 0 -> COLOR BLANCO;
	if(colorDerecho >= 7 && colorDerecho <= 9){colorBlanco = 2;}        //SE RETORNA 2 -> COLOR POSIBLE VERDE
	if(colorDerecho >= 2 && colorDerecho <= 6) {colorBlanco = 1;}        //SE RETORNA 1 -> COLOR NEGRO;


	return colorBlanco;
}

int colorRGBSensorIzquierdo(tSensors sIzquierdo){

	int colorSensor = 2;
	int colorHUE = 0;
	int tiempoLectura = 1000;

	if(getColorReflected(sIzquierdo) < 35){
		while(tiempoLectura > -1){colorHUE = getColorHue(sIzquierdo); tiempoLectura--;}
		if(colorHUE >= 103 && colorHUE <= 115){colorSensor = 3;}else{colorSensor = 1;}
	}else{colorSensor = 2;}

	return colorSensor;
}

int colorRGBSensorDerecho(tSensors sDerecho){

	int colorSensor = 2;
	int colorHUE = 0;
	int tiempoLectura = 1000;

	if(getColorReflected(sDerecho) < 35 ){
		while(tiempoLectura > -1){colorHUE = getColorHue(sDerecho); tiempoLectura--;}
		if(colorHUE >= 162 && colorHUE <= 174){colorSensor = 3;}else{colorSensor = 1;}
	}else{colorSensor = 2;}


	return colorSensor;

}

task main(){

	int velocidadAvance = 15;
	int minMotorSpeed = -15;
	int colorIzq = 0;
	int colorDer = 0;
	int colorIzqRGB = 0;
	int colorDerRGB = 0;
	int controlLineaNegra = 0;
	int colorIzqReflected = 0;
	int colorDerReflected = 0;
	int colorCenReflected = 0;

	while (true)
	{
		colorIzqReflected = getColorReflected(sensorIzquierdo);
		colorDerReflected = getColorReflected(sensorDerecho);
		colorCenReflected = getColorReflected(sensorCentro);

		controlLineaNegra = round((((colorIzqReflected - colorDerReflected)/2)+6)*2/15);

		if(controlLineaNegra >= 4){controlLineaNegra = 3;}
		if(controlLineaNegra <= -4){controlLineaNegra = -3;}

		switch (controlLineaNegra)
		{
		case 3:
			setMotorSpeed(motorIzquierdo, velocidadAvance*2.5);
			setMotorSpeed(motorDerecho, minMotorSpeed*2.5);
			break;
		case 2:
			setMotorSpeed(motorIzquierdo, velocidadAvance*2);
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
			setMotorSpeed(motorDerecho, velocidadAvance*2);
			break;
		case -3:
			setMotorSpeed(motorIzquierdo, minMotorSpeed*2.5);
			setMotorSpeed(motorDerecho, velocidadAvance*2.5);
			break;
		}

		if(colorIzqReflected <= 3 && colorCenReflected <= 10){
			setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
			sleep(3000);
			forward(1, rotations, velocidadAvance);
		}

		if(colorDerReflected <= 6 && colorCenReflected <= 10){
			setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
			sleep(3000);
			forward(1, rotations, velocidadAvance);
		}

		colorIzq = colorSensorIzquierdo(sensorIzquierdo);
		colorDer = colorSensorDerecho(sensorDerecho);

		if (colorIzq  == 2 ||  colorDer == 2)
		{

			if(colorIzq == 2){
				//playTone(1000, 3);
				//COMPROBACION DE VERDE
				displayCenteredBigTextLine(3,"POS VERDE IZQ");
				//AVANZA HACIA ADELANTE
				//forward(0.05, rotations, velocidadAvance);
				//FRENA EL ROBOT
				stopMultipleMotors(motorDerecho, motorIzquierdo);
				//setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
				//playTone(1000, 3);
				//////////////sleep(3000);
				//GUARDA EL RGB EN LA VARIABLE colorIzqRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
				forward(0.07, rotations, velocidadAvance);
				//////////////sleep(500);
				colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
				displayCenteredBigTextLine(3,"colorIzq %d",colorIzqRGB);
				if(colorIzqRGB == 1 || colorIzqRGB == 2){
					//stopMultipleMotors(motorDerecho, motorIzquierdo);
						if(colorIzqRGB == 1){
							setMotorSpeed(motorDerecho, velocidadAvance*2.5);
							setMotorSpeed(motorIzquierdo, minMotorSpeed*2.5);
							sleep(250);
						}else{
							setMotorSpeed(motorDerecho, minMotorSpeed*2.5);
							setMotorSpeed(motorIzquierdo, velocidadAvance*2.5);
							sleep(250);
						}
					}else{
					////////////////sleep(3000);
					//COMPRUEBA SI EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
					if(colorIzqRGB == 3){
						//FRENO EL ROBOT
						stopMultipleMotors(motorDerecho, motorIzquierdo);
						//setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
						//GUARDA EL RGB EN LA VARIABLE colorDerRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
						colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
						//////////////sleep(1000);
						//VERIFICA SI TAmotorIzquierdoIEN EL SENSOR DERECHO ESTA SOBRE EL VERDE
						//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
						if(colorDerRGB == 3){
							displayCenteredBigTextLine(3,"DOBLE VERDE");
							forward(0.3, rotations, velocidadAvance);
							turnLeft(2.5, rotations, velocidadAvance);
							forward(0.5, rotations, velocidadAvance);
							}else{
							//SINO SE GIRA HACIA LA IZQUIERDA
							//playTone(1000, 3);
							displayCenteredBigTextLine(3,"VERDE IZQ");
							forward(0.3, rotations, velocidadAvance);
							turnLeft(1.1, rotations, velocidadAvance);
							forward(0.3, rotations, velocidadAvance);
						}
						}else{
						backward(0.14, rotations, velocidadAvance);
					}
				}
			}

			if(colorDer == 2){
				//playTone(1000, 3);
				//COMPROBACION DE VERDE
				displayCenteredBigTextLine(3,"POS VERDE DER");
				//AVANZA HACIA ADELANTE
				//forward(0.05, rotations, velocidadAvance);
				//FRENA EL ROBOT
				stopMultipleMotors(motorDerecho, motorIzquierdo);
				//setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
				//playTone(1000, 3);
				//////////////sleep(3000);
				//GUARDA EL RGB EN LA VARIABLE colorDerRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
				forward(0.07, rotations, velocidadAvance);
				//////////////sleep(500);
				colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
				displayCenteredBigTextLine(3,"colorDer %d",colorDerRGB);
				if(colorDerRGB == 1 || colorDerRGB == 2){
					//stopMultipleMotors(motorDerecho, motorIzquierdo);
						if(colorDerRGB == 1){
							setMotorSpeed(motorDerecho, minMotorSpeed*2.5);
							setMotorSpeed(motorIzquierdo, velocidadAvance*2.5);
							sleep(250);
						}else{
							setMotorSpeed(motorDerecho, velocidadAvance*2.5);
							setMotorSpeed(motorIzquierdo, minMotorSpeed*2.5);
							sleep(250);
						}
					}else{
					//////////////sleep(3000);
					//COMPRUEBA SI EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
					if(colorDerRGB == 3){
						//FRENO EL ROBOT
						stopMultipleMotors(motorDerecho, motorIzquierdo);
						//setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 0);
						//GUARDA EL RGB EN LA VARIABLE colorIzqRGB ESPERANDO 1,8s PARA TOMAR BIEN LA GAMA RBG
						colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
						////////////sleep(1000);
						//VERIFICA SI TAMBIEN EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
						//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
						if(colorIzqRGB == 3)
						{
							displayCenteredBigTextLine(3,"DOBLE VERDE");
							forward(0.3, rotations, velocidadAvance);
							turnRight(2.5, rotations, velocidadAvance);
							forward(0.5, rotations, velocidadAvance);
							}else{
							//SINO SE GIRA HACIA LA DERECHA
							//playTone(1000, 3);
							displayCenteredBigTextLine(3,"VERDE DER");
							forward(0.3, rotations, velocidadAvance);
							turnRight(1.1, rotations, velocidadAvance);
							forward(0.3, rotations, velocidadAvance);
						}
						}else{
						backward(0.14, rotations, velocidadAvance);
					}
				}

			}

		}

	}

}