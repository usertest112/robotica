task main()
{
  int VEL = 30;
  //int KD = ;
	int IDEAL = 40;
	/*VALOR ENTRE BLANCO Y NEGRO*/
while(true){
	int SEN = getColorReflected(S3);
	/*kp sen - el valor en el que se tiene que mantener x un numerox*/
	wait1Msec(0);
		int KP = (IDEAL-SEN) * 1.75 ;
	if (SEN <= IDEAL){
	  setMotorSpeed(motorB, VEL + KP);
    setMotorSpeed(motorC, VEL - KP);
     }
    else if (SEN >= IDEAL){
	  setMotorSpeed(motorB, VEL - KP);
    setMotorSpeed(motorC, VEL + KP);
    }
}
}
