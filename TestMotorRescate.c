#pragma config(Sensor, S1,     sensorIzquierdo, sensorEV3_Color)
#pragma config(Sensor, S2,     sensorDerecho,  sensorEV3_Color)
#pragma config(Sensor, S3,     sensorCentro,   sensorEV3_Color)
#pragma config(Sensor, S4,     sensorUItrasonic, sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorIzquierdo, tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorDerecho,  tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          motorRescate,  tmotorEV3_Medium, PIDControl, encoder)
task main()
{
while(true){

	setMotorSpeed(motorRescate, 50);

}


}
