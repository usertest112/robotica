#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int colorSensorIzquierdo(tSensors sIzquierdo){

	int colorIzquierdo = 0;
	int colorBlanco = 0;

	colorIzquierdo = getColorReflected(sIzquierdo);

	//PREGUNTA SI EL SENSOR IZQUIERDO ESTA EN EL BLANCO
	if(colorIzquierdo > 84){ //SE TOMA COMO VALOR DE REFERENCIA EN BLANCO COMO VALOR SUPERIOR AL 30
		colorBlanco = 1;//SE RETORNA 1 -> COLOR BLANCO;
		}else if(colorIzquierdo >= 47 && colorIzquierdo <= 84){
		colorBlanco = 2;//SE RETORNA 2 -> COLOR POSIBLE VERDE;
		}else if(colorIzquierdo >= 2 && colorIzquierdo <= 47){
		colorBlanco = 0;//SE RETORNA 0 -> COLOR NEGRO;
	}
	return colorBlanco;
}

int colorSensorDerecho(tSensors sDerecho){

	int colorDerecho = 0;
	int colorBlanco = 0;

	colorDerecho = getColorReflected(sDerecho);

	//PREGUNTA SI EL SENSOR DERECHO ESTA EN EL BLANCO
	if(colorDerecho > 91){//SE TOMA COMO VALOR DE REFERENCIA EN BLANCO COMO VALOR SUPERIOR AL 30
		colorBlanco = 1;//SE RETORNA 1 -> COLOR BLANCO;
		}else if(colorDerecho >= 44 && colorDerecho <= 91){
		colorBlanco = 2;//SE RETORNA 2 -> COLOR POSIBLE VERDE
		}else if(colorDerecho >= 2 && colorDerecho <= 44){
		colorBlanco = 0;//SE RETORNA 0 -> COLOR NEGRO;
	}
	return colorBlanco;
}

int colorRGBSensorIzquierdo(tSensors sIzquierdo){

	//VARIABLES DE CONTROL
	int colorSensor,redChannel,greenChannel,blueChannel = 0;
	//FUNCION QUE GUARDA LOS VALORES RGB EN LAS VARIABLES redChannel - greenChannel - blueChannel
	getColorRGB(sIzquierdo, redChannel, greenChannel, blueChannel);

	//VERIFICA SI LAS VARIABLES TIENEN EL VALOR ESPECIFICADO EN EL RANGO
	//DE VALORES RGB ESPECIFICO PARA CADA COLOR (NEGRO, BLANCO, VERDE)
	/*
	if((redChannel >= 4 && redChannel <= 9) && (greenChannel >= 16 && greenChannel <= 20) && (blueChannel >= 9 && blueChannel <= 14)){
		colorSensor = 1;//COLOR NEGRO
	}

	if((redChannel >= 48 && redChannel <= 53) && (greenChannel >= 18 && greenChannel <= 50) && (blueChannel >= 17 && blueChannel <= 19)){
		colorSensor = 2;//COLOR BLANCO
	}
	*/
	if((redChannel >= 4 && redChannel <= 29) && (greenChannel >= 16 && greenChannel <= 56) && (blueChannel >= 17 && blueChannel <= 68)){
		colorSensor = 3;//COLOR VERDE
	}

	return colorSensor;

}

int colorRGBSensorDerecho(tSensors sDerecho){

	//VARIABLES DE CONTROL
	int colorSensor,redChannel,greenChannel,blueChannel = 0;
	//FUNCION QUE GUARDA LOS VALORES RGB EN LAS VARIABLES redChannel - greenChannel - blueChannel
	getColorRGB(sDerecho, redChannel, greenChannel, blueChannel);

	//VERIFICA SI LAS VARIABLES TIENEN EL VALOR ESPECIFICADO EN EL RANGO
	//DE VALORES RGB ESPECIFICO PARA CADA COLOR (NEGRO, BLANCO, VERDE)
	/*
	if((redChannel >= 6 && redChannel <= 11) && (greenChannel >= 15 && greenChannel <= 19) && (blueChannel >= 2 && blueChannel <= 6)){
		colorSensor = 1;//COLOR NEGRO
	}

	if((redChannel >= 57 && redChannel <= 62) && (greenChannel >= 57 && greenChannel <= 62) && (blueChannel >= 17 && blueChannel <= 18)){
		colorSensor = 2;//COLOR BLANCO
	}
	*/
	if((redChannel >= 4 && redChannel <= 30) && (greenChannel >= 19 && greenChannel <= 64) && (blueChannel >= 13 && blueChannel <= 47)){
		colorSensor = 3;//COLOR VERDE
	}

	return colorSensor;

}

task main()
{

	int velocidadAvance = 30;
	int velocidadRetroceso = -30;
	int colorIzq = 0;
	int colorDer = 0;
	int colorIzqRGB = 0;
	int colorDerRGB = 0;


	while(true){

		colorIzq = colorSensorIzquierdo(sensorIzquierdo);
		colorDer = colorSensorDerecho(sensorDerecho);
		//VERIFICA EL DOBLE BLANCO
		if(colorIzq == 1 && colorDer == 1){
			//DEBUG DISPLAY
			displayCenteredBigTextLine(3,"|");
			//AMBOS MOTORES AVANZAN HACIA ADELANTE
			setMotorSpeed(motorIzquierdo, velocidadAvance);
			setMotorSpeed(motorDerecho, velocidadAvance);
		}
		//VERIFICA EL DOBLE NEGRO
		if(colorIzq == 0 && colorDer == 0){
			//DEBUG DISPLAY
			displayCenteredBigTextLine(3,"+");
			//sleep(500);
			//AMBOS MOTORES AVANZAN HACIA ADELANTE DURANTE 0,7 Seg.
			setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
			sleep(700);
		}
		//VERIFICA SI EL SENSOR IZQUIERDO ESTA EN EL NEGRO Y EL SENSOR DERECHO ESTA EN EL BLANCO
		if(colorIzq == 0 && colorDer == 1){
			//DEBUG DISPLAY
			displayCenteredBigTextLine(3,"<");
			//EL MOTOR IZQUIERDO RETROCEDE MIENTRAS EL MOTOR DERECHO PERMANECE ESTATICO.
			setMotorSpeed(motorIzquierdo, velocidadRetroceso);
			setMotorSpeed(motorDerecho, 0);
		}
		//VERIFICA SI EL SENSOR IZQUIERDO ESTA EN EL BLANCO Y EL SENSOR DERECHO ESTA EN EL NEGRO
		if(colorIzq == 1 && colorDer == 0){
			//DEBUG DISPLAY
			displayCenteredBigTextLine(3,">");
			//EL MOTOR IZQUIERDO PERMANECE ESTATICO MIENTRAS EL MOTOR DERECHO RETROCEDE.
			setMotorSpeed(motorIzquierdo, 0);
			setMotorSpeed(motorDerecho, velocidadRetroceso);
		}
		//VERIFICA SI EL SENSOR IZQUIERDO ESTA DETECTANDO POSIBLE VERDE
		if(colorIzq == 2){
			//SE CHEQUEA CON LA FUNCION EN RGB
			colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
			//SE VERIFICA SI ES COLOR VERDE
			if(colorIzqRGB == 3){
				//DEBUG DISPLAY
				displayCenteredBigTextLine(3,"VERDE IZQ");
				//sleep(1000);
				//PASO 1 - SE AVANZA HACIA ADELANTE DURANTE 0,425 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(425);
				//PASO 2 - SE GIRA HACIA LA IZQUIERDA DURANTE 1,450 Seg. (90�)
				setMotorSyncTime(motorIzquierdo, motorDerecho, 100, 0, velocidadAvance);
				sleep(1450);
				//PASO 3 - SE AVANZA HACIA ADELANTE DURANTE 0,9 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(900);

			}

		}
		//VERIFICA SI EL SENSOR DERECHO ESTA DETECTANDO POSIBLE VERDE
		if(colorDer == 2){
			//SE CHEQUEA CON LA FUNCION EN RGB
			colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
			//SE VERIFICA SI ES COLOR VERDE
			if(colorDerRGB == 3){
				//DEBUG DISPLAY
				displayCenteredBigTextLine(3,"VERDE DER");
				//sleep(1000);
				//PASO 1 - SE AVANZA HACIA ADELANTE DURANTE 0,5 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(500);
				//PASO 2 - SE GIRA HACIA LA DERECHA DURANTE 1,500 Seg. (90�)
				setMotorSyncTime(motorIzquierdo, motorDerecho, -100, 0, velocidadAvance);
				sleep(1500);
				//PASO 3 - SE AVANZA HACIA ADELANTE DURANTE 0,9 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(900);
			}

		}
		//VERIFICA SI AMBOS SENSORES ESTAN DETECTANDO POSIBLE VERDE
		if(colorIzq == 2 && colorDer == 2){
			//SE CHEQUEA CON LA FUNCION EN RGB EN AMBOS SENSORES
		colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
			colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
			//SE VERIFICA SI ES DOBLE VERDE
			if(colorIzqRGB == 3 && colorDerRGB == 3){
				//DEBUG DISPLAY
				displayCenteredBigTextLine(3,"DOBLE VERDE");
				//sleep(1000);
				//PASO 1 - SE AVANZA HACIA ADELANTE DURANTE 0,5 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(500);
				//PASO 2 - SE GIRA HACIA LA DERECHA DURANTE 1,500 Seg. (180�)
				setMotorSyncTime(motorIzquierdo, motorDerecho, 100, 0, velocidadAvance);
				sleep(3000);
				//PASO 3 - SE AVANZA HACIA ADELANTE DURANTE 0,9 Seg.
				setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, velocidadAvance);
				sleep(900);
			}

		}

	}

}
