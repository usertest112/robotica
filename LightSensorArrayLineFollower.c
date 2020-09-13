#pragma config(Sensor, S1,     MSLSA,          sensorEV3_GenericI2C)
#pragma config(Motor,  motorB,          MB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          MC,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "mindsensors-lightsensorarray.h"

task main()
{

	int Target = -6;
	int TurnMultiple = 1.5;
	int variableControlMitad1 = 4;
	int variableControlMitad2 = -4;
	int LS4LS1 = 0;
	int LS8LS4 = 0;
	int potenciaMotor = 0;

	while(true){

	  tByteArray signalstr;
	  //tByteArray LS4LS1;
	  //tByteArray LS8LS4;
	  tByteArray valorReflejado;
	  MSLSAinit(MSLSA);
    //if (!MSLSAreadSensors(MSLSA, &signalstr[1])){
	    for (short i = 0; i < 7; i+=2) {
	      //displayTextLine(i/2+3, "S: %3d S: %3d", (short)signalstr[i], (short)signalstr[i+1]);
	    	valorReflejado[i] = (short)signalstr[i];
	    }
	    for (short x = 0; x < 3; x++){
	    		if (variableControlMitad1 != 0){
	    			LS4LS1 = valorReflejado[x] * variableControlMitad1;
	    		}
	    		variableControlMitad1--;
	    }
	    for (short j = 4; j < 7; j++){
	    		if (variableControlMitad2 != 0){
	    			LS8LS4 = valorReflejado[j] * variableControlMitad2;
	    		}
	    		variableControlMitad2++;
	    }
	    potenciaMotor = Target - (LS4LS1 + LS8LS4) * TurnMultiple;
	    setMotorSync(MB, MC, 0, potenciaMotor);
	    //setMotorSpeed()
    //}

	}


}