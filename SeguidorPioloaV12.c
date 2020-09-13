#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Sensor, S4,     sensorUltrasonido, sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          motorRescate,  tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int colorSensorIzquierdo(tSensors sIzquierdo){

	int colorIzquierdo = 0;
	int colorBlanco = 0;

	colorIzquierdo = getColorReflected(sIzquierdo);

	//PREGUNTA SI EL SENSOR IZQUIERDO ESTA EN EL BLANCO
	//SE TOMA COMO VALOR DE REFERENCIA EN BLANCO
	//COMO VALOR SUPERIOR AL 27
	if(colorIzquierdo > 12)												{colorBlanco = 0;} 		//SE RETORNA 0 -> COLOR BLANCO;
	if(colorIzquierdo >= 4 && colorIzquierdo <= 11){colorBlanco = 2;}	  //SE RETORNA 2 -> COLOR POSIBLE VERDE;
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
	if(colorDerecho > 12)                      {colorBlanco = 0;}        //SE RETORNA 0 -> COLOR BLANCO;
	if(colorDerecho >= 7 && colorDerecho <= 11){colorBlanco = 2;}        //SE RETORNA 2 -> COLOR POSIBLE VERDE
	if(colorDerecho >= 2 && colorDerecho <= 6)  {colorBlanco = 1;}        //SE RETORNA 1 -> COLOR NEGRO;


	return colorBlanco;
}

int colorRGBSensorIzquierdo(tSensors sIzquierdo){

	int colorSensor = 2;
	int colorHUE = 0;
	int tiempoLectura = 1000;

	if(getColorReflected(sIzquierdo) < 20){//PREGUNTA SI EL VALOR REFLEJADO ES MENOR QUE 20 (SI NO ES BLANCO)
		while(tiempoLectura > -1){colorHUE = getColorHue(sIzquierdo); tiempoLectura--;}//GUARDA LA LECTURA DE COLOR
		if(colorHUE >= 105 && colorHUE <= 115){colorSensor = 3;}else{colorSensor = 1;}//VERIFICA SI EL COLOR ES VERDE O NEGRO
	}else{colorSensor = 2;}

	return colorSensor;
}

int colorRGBSensorDerecho(tSensors sDerecho){

	int colorSensor = 2;
	int colorHUE = 0;
	int tiempoLectura = 1000;

	if(getColorReflected(sDerecho) < 27 ){//PREGUNTA SI EL VALOR REFLEJADO ES MENOR QUE 27 (SI NO ES BLANCO)
		while(tiempoLectura > -1){colorHUE = getColorHue(sDerecho); tiempoLectura--;}//GUARDA LA LECTURA DE COLOR
		if(colorHUE >= 150 && colorHUE <= 175){colorSensor = 3;}else{colorSensor = 1;}//VERIFICA SI EL COLOR ES VERDE O NEGRO
	}else{colorSensor = 2;}


	return colorSensor;

}

task main(){

	int velocidadAvance = 25;
	int colorIzq = 0;
	int colorDer = 0;
	int colorIzqRGB = 0;
	int colorDerRGB = 0;
	int controlLineaNegra = 0;
	int colorIzqReflected = 0;
	int colorDerReflected = 0;
	int colorCenReflected = 0;
	int giroObstaculo = 0;
	float distanciaCM = 0;

	while(true){
//----------------------------------------------------INICIO-SEGUIDOR-DE-LINEA--------------------------------------------------------------------
		seguidorLinea://ETIQUETA DEL SEGUIDOR DE LINEA
			colorIzqReflected = getColorReflected(sensorIzquierdo);
			colorDerReflected = getColorReflected(sensorDerecho);
			colorCenReflected = getColorReflected(sensorCentro);

			controlLineaNegra = round((((colorIzqReflected - colorDerReflected)/2)+8)*1.6/15);

			if(controlLineaNegra >= 4){controlLineaNegra = 3;}
			if(controlLineaNegra <= -4){controlLineaNegra = -3;}

			switch (controlLineaNegra){
			case 3:
				setMotorSpeed(motorIzquierdo, 99);
				setMotorSpeed(motorDerecho, -99);
				break;
			case 2:
				setMotorSpeed(motorIzquierdo, 66);
				setMotorSpeed(motorDerecho, -66);
				break;
			case 1:
				setMotorSpeed(motorIzquierdo, 33);
				setMotorSpeed(motorDerecho, -33);
				break;
			case 0:
				setMotorSpeed(motorIzquierdo, 40);
				setMotorSpeed(motorDerecho, 40);
				break;
			case -1:
				setMotorSpeed(motorIzquierdo, -33);
				setMotorSpeed(motorDerecho, 33);
				break;
			case -2:
				setMotorSpeed(motorIzquierdo, -66);
				setMotorSpeed(motorDerecho, 66);
				break;
			case -3:
				setMotorSpeed(motorIzquierdo, -99);
				setMotorSpeed(motorDerecho, 99);
				break;
			}
//--------------------------------------------------------------FIN-SEGUIDOR-DE-LINEA-------------------------------------------------------------
//-------------------------------------------------------INICIO-DETECCION-DE-OBSTACULOS-----------------------------------------------------------
			distanciaCM = getUSDistance(sensorUltrasonido);//SE GUARDA LA DISTANCIA EN UNA VARIABLE

			if(distanciaCM < 5){//SE PREGUNTA SI LA DISTANCIA ES MENOR QUE 5CM, ENTONCES
				stopAllMotors();//SE PARA EL ROBOT
				giroObstaculo = random(1);//VARIABLE QUE SIRVE PARA QUE EL ROBOT ELIJA DE MANERA ALEATORIA EL GIRO PARA ESQUIVAR EL OBSTACULO
				sleep(750);//ESPERA 0,750s
				if(giroObstaculo == 0){//SI LA VARIABLE giroObstaculo ES 0 ENTONCES LO ESQUIVAR POR LA DERECHA.
					backward(0.1, rotations, 25);
					turnRight(0.7, rotations, 25);
					while(getColorReflected(sensorDerecho) > 10){//EL ROBOT GIRA HASTA QUE EL SENSOR DERECHO VEA LA LINEA NEGRA.
						setMotorSpeed(motorIzquierdo, 10);
						setMotorSpeed(motorDerecho, 30);
					}
					setMotorSyncTime(motorIzquierdo, motorDerecho, 100, 0, 100);//GIRA A LA IZQUIERDA DURANTE 0,275s PARA ACOMODAR EL ROBOT
					sleep(275);
					backward(0.3, rotations, 25);//VUELVE PARA ATRAS PARA DEJARLO MAS CENTRADO AL ROBOT
				}else{//SI LA VARIABLE giroObstaculo ES 1 ENTONCES LO ESQUIVAR POR LA IZQUIERDA.
					backward(0.1, rotations, 25);
					turnLeft(0.7, rotations, 25);
					while(getColorReflected(sensorIzquierdo) > 10){//EL ROBOT GIRA HASTA QUE EL SENSOR IZQUIERDO VEA LA LINEA NEGRA.
						setMotorSpeed(motorIzquierdo, 30);
						setMotorSpeed(motorDerecho, 10);
					}
					setMotorSyncTime(motorIzquierdo, motorDerecho, -100, 0, 100);//GIRA A LA DERECHA DURANTE 0,275s PARA ACOMODAR EL ROBOT
					sleep(275);
					backward(0.3, rotations, 25);//VUELVE PARA ATRAS PARA DEJARLO MAS CENTRADO AL ROBOT
				}
			}
//------------------------------------------------FIN-DETECCION-DE-OBSTACULOS---------------------------------------------------------------------
//------------------------------------------------INICIO-DETECCION-DE-VERDES----------------------------------------------------------------------
			colorIzq = colorSensorIzquierdo(sensorIzquierdo);
			colorDer = colorSensorDerecho(sensorDerecho);

			if (colorIzq  == 2 ||  colorDer == 2){

				if(colorIzq == 2){//COMPROBACION DE VERDE

					displayCenteredBigTextLine(3,"POS VERDE IZQ");
					stopMultipleMotors(motorDerecho, motorIzquierdo);//FRENA EL ROBOT
					forward(0.05, rotations, velocidadAvance); //AVANZA
					colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);//COMPRUEBA SI EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
					displayCenteredBigTextLine(3,"colorIzq %d",colorIzqRGB);
					if(colorIzqRGB == 1 || colorIzqRGB == 2){
						if(colorIzqRGB == 1){
							colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
							if(colorDerRGB == 1){
								setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 100);
								sleep(275);
								goto seguidorLinea;
							}else{
								if(colorIzqRGB == 1){
									setMotorSyncTime(motorIzquierdo, motorDerecho, -100, 0, 100);
									sleep(275);
									goto seguidorLinea;
								}else{
									setMotorSyncTime(motorIzquierdo, motorDerecho, 100, 0, 100);
									sleep(275);
									goto seguidorLinea;
								}
							}
						}
					}else{
						if(colorIzqRGB == 3){
							stopMultipleMotors(motorDerecho, motorIzquierdo);//FRENO EL ROBOT
							colorDerRGB = colorRGBSensorDerecho(sensorDerecho);//GUARDA EL RGB EN LA VARIABLE colorDerRGB
							sleep(500);
								if(colorDerRGB == 3){//VERIFICA SI TAMBIEN EL SENSOR DERECHO ESTA SOBRE EL VERDE
									displayCenteredBigTextLine(3,"DOBLE VERDE");//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
									forward(0.3, rotations, 25);
									turnLeft(2.5, rotations, 25);
									forward(0.5, rotations, 25);
								}else{
									//SINO SE GIRA HACIA LA IZQUIERDA
									displayCenteredBigTextLine(3,"VERDE IZQ");
									forward(0.35, rotations, 25);
									turnLeft(1.1, rotations, 25);
									forward(0.15, rotations, 25);
								}
						}else{
							backward(0.05, rotations, 25);
						}
					}
				}

				if(colorDer == 2){ //COMPROBACION DE VERDE

					displayCenteredBigTextLine(3,"POS VERDE DER");
					stopMultipleMotors(motorDerecho, motorIzquierdo);  //FRENA EL ROBOT
					forward(0.05, rotations, velocidadAvance); //AVANZA
					colorDerRGB = colorRGBSensorDerecho(sensorDerecho);
					displayCenteredBigTextLine(3,"colorDer %d",colorDerRGB);
					//COMPRUEBA SI EL SENSOR DERECHO ESTA SOBRE EL VERDE
					if(colorDerRGB == 1 || colorDerRGB == 2){
						if(colorDerRGB == 1){
							colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);
							if(colorDerRGB == 1){
								setMotorSyncTime(motorIzquierdo, motorDerecho, 0, 0, 100);
								sleep(275);
								goto seguidorLinea;
							}else{
								if(colorDerRGB == 1){
									setMotorSyncTime(motorIzquierdo, motorDerecho, 100, 0, 100);
									sleep(275);
									goto seguidorLinea;
								}else{
									setMotorSyncTime(motorIzquierdo, motorDerecho, -100, 0, 100);
									sleep(275);
									goto seguidorLinea;
								}
							}
						}
					}else{
						if(colorDerRGB == 3){
							stopMultipleMotors(motorDerecho, motorIzquierdo);//FRENO EL ROBOT
							colorIzqRGB = colorRGBSensorIzquierdo(sensorIzquierdo);	//GUARDA EL RGB EN LA VARIABLE colorIzqRGB.
							sleep(500);
								if(colorIzqRGB == 3){	//VERIFICA SI TAMBIEN EL SENSOR IZQUIERDO ESTA SOBRE EL VERDE
									displayCenteredBigTextLine(3,"DOBLE VERDE");//SI LA CONDICION ES VERDADERA ENTONCES ES DOBLE VERDE
									forward(0.3, rotations, 25);
									turnRight(2.5, rotations, 25);
									forward(0.5, rotations, 25);
								}else{
									//SINO SE GIRA HACIA LA DERECHA
									displayCenteredBigTextLine(3,"VERDE DER");
									forward(0.35, rotations, 25);
									turnRight(1, rotations, 25);
									forward(0.15, rotations, 25);
								}
						}else{
							backward(0.05, rotations, 25);
						}
					}
				}

			}
//----------------------------------------------------FIN-DETECCION-DE-VERDES--------------------------------------------------------------------
//---------------------------------------------------INICIO-CODIGO-PARA-RESCATE------------------------------------------------------------------
/*
		playTone(1000, 3);
		stopAllMotors();
		sleep(5000);
		forward(2, rotations, 100);
*/
//---------------------------------------------------FIN-CODIGO-PARA-RESCATE---------------------------------------------------------------------
	}//endWhileInfinity

}
