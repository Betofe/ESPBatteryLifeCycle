// 
// 
// 

#include "ArduinoC.h"

void Setting::init() {


	// kalman variables
	varVolt = 1.12184278324081E-05;  // variance determined using excel and reading samples of raw sensor data
	varProcess = 1e-8;
	Pc = 0.0;
	G = 0.0;
	P = 1.0;
	Xp = 0.0;
	Zp = 0.0;
	Xe = voltage;
	sensorVal = analogRead(sensorPin);     // read the value on AnalogIn pin 0 and store it in a variable
	voltage = (((sensorVal * 3.3) / 4095) * 2.55);
	save = 0;
	MyflagOne = false;
	MyflagTwo = false;

	EEPROM.begin(EEPROM_SIZE);
	save = EEPROM.read(0);
	Serial.print("Cycle ");
	Serial.println(save);
}
void Setting::run() {
	// Measures the value of the potentiometer
	int sensorVal = analogRead(sensorPin);     // read the value on AnalogIn pin 0 and store it in a variable
	float voltage = (((sensorVal * 3.3) / 4095) * 2.55);  // convert the ADC reading to voltage

	// Serial.println(voltage);

	  // kalman process
	Pc = P + varProcess; //Predict the next variance
	G = Pc / (Pc + varVolt);    // Computer the kalman gain
	P = (1 - G) * Pc; // Update variance estimation
	Xp = Xe; // Predict the next state
	Zp = Xp; // Predict the next state
	Xe = G * (voltage - Zp) + Xp;   // Update the Kalman state estimation
	z = map(Xe, 0, 8.4, 0, 100);




	if (z >= 70 && z < 90) {
		MyflagOne = true;
	}
	if (z >= 90 && z <= 100) {
		MyflagTwo = true;

	}


	if ((MyflagOne == true) && (MyflagTwo == true) && z >= 90) {

		save = EEPROM.read(0);
		save += 1;
		EEPROM.write(0, save);
		EEPROM.commit();
		Serial.print("New Cycle ");
		Serial.println(save);

		MyflagTwo = false;
		MyflagOne = false;

	}
}

