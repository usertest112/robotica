task main()
{
  int VEL = 30;
  int SAL = 0;
	int IDEAL = 25;
	int PERRO = 0;
	int SEN = 0;
	int ERROR = 0;
	int KP = 1.1;
	int DT = 10;
	int KD = 0;
	int DERI = 0;

	/*VALOR ENTRE BLANCO Y NEGRO*/
	setMotorSpeed(motorB, 10);
	setMotorSpeed(motorC, 10);
  wait1Msec(2000);




while(true){
	SEN = getColorReflected(S3);
	ERROR = (IDEAL - SEN);
	DERI = (ERROR - PERRO) / DT;
	SAL = KP * ERROR + KD * DERI;

	if (SEN <= IDEAL){
	  setMotorSpeed(motorB, VEL + SAL);
    setMotorSpeed(motorC, VEL - SAL);
     }
    else if (SEN >= IDEAL){
	  setMotorSpeed(motorB, VEL - SAL);
    setMotorSpeed(motorC, VEL + SAL);
    }
    wait1Msec(DT);
    PERRO = ERROR;

}

}
