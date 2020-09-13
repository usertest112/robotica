
task main()
{

	int Kp = 10;
	int Ki = 1;
	int Kd = 100;
	int Offset = 45;
	int Tp = 50;
	int Integral = 0;
	int lastError = 0;
	int Derivative = 0;
	int ligthValue = 0;
	int Error = 0;
	int Turn = 0;
	int powerB = 0;
	int powerC = 0;

	while(true){

		ligthValue = getColorReflected(S3);
		Error = Offset - ligthValue;
		Integral = Integral + Error;
		Derivative = Error - lastError;
		Turn = (Kp * Error) + (Ki * Integral) + (Kd * Derivative);
		powerB = Tp + Turn;
		powerC = Tp - Turn;
		setMotorSpeed(motorB, powerB);
		setMotorSpeed(motorC, powerC);
		Error = lastError;

	}

}
