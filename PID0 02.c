task main()
{
	//int KD = ;
	int IDEAL = 50 ;
	/*VALOR ENTRE BLANCO Y NEGRO*/
	setMotorSpeed(motorB, 10);
	setMotorSpeed(motorC, 10);
  wait1Msec(2000);




while(true){
	int SEN = getColorReflected(S3);
	/*kp sen - el valor en el que se tiene que mantener x un numerox*/
	wait1Msec(0);
		int KP = (SEN - IDEAL) * 1.3 ;
	if (SEN <= IDEAL){
	  setMotorSpeed(motorB, 50 + KP);
    setMotorSpeed(motorC, 50 - KP);
     }
    else if (SEN >= IDEAL){
	  setMotorSpeed(motorB, 50 - KP);
    setMotorSpeed(motorC, 50 + KP);
    }
}

}
