#pragma config(Sensor, S1,     cc1,            sensorEV3_Color)
#pragma config(Sensor, S2,     cc2,            sensorEV3_Color)
#pragma config(Motor,  motorA,          mma,           tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          mmb,           tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          mmc,           tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorD,          mmd,           tmotorEV3_Large, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
	while(true){
			if (cc1 <=40){


			setMotorSpeed(mma, -50 );
		}



		if (cc2 <=40){

			setMotorSpeed(mmb,50 );

		}

		if (cc2 >=40 && cc1 >=40){
	}

}
}