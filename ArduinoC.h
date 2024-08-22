// ArduinoC.h
#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#define EEPROM_SIZE 1

class Setting {
private:
	const int sensorPin = 35;  // named constant for the pin the sensor is connected to
	float varVolt; // variance determined using excel and reading samples of raw sensor data
	float varProcess; //variance Process
	float Pc; // Next variance predictor
	float G; // Kalman Gain
	float P; // update variance estimator
	float Xp; // Next state predictor
	float Zp; // Next state predictor
	float Xe; // Kalman Estimator
	float voltage;
	int sensorVal;
	bool MyflagOne;
	bool MyflagTwo;
	int save;
	int z; //voltage in percentage
public:
	void init();
	void run();
};

