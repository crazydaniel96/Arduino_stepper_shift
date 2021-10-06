#include "Arduino.h"
#include "SteppersOnShift.h"

SteppersOnShift::SteppersOnShift( int dataPin, int latchPin, int clockPin, int motorPin1, int motorPin2, int motorPin3,int motorPin4){

  	this->dataPin = dataPin;
	this->latchPin = latchPin;
	this->clockPin = clockPin;
	this->motorPins[0] = motorPin1;
	this->motorPins[1] = motorPin2;
	this->motorPins[2] = motorPin3;
	this->motorPins[3] = motorPin4;
	
	pinMode(dataPin, OUTPUT);
  	pinMode(latchPin, OUTPUT);
  	pinMode(clockPin, OUTPUT);
  
	clearRegisters();
}


void SteppersOnShift::MoveForward(int motorSpeed){
	
	int i, countsperrev = 512, count = 0; // count=count of steps made, countsperrev=number of steps per full revolution

	//Serial.println("stepper ON");
  	while(count < countsperrev ){
    	
    	for(i = 7; i >= 0; i--){
			setRegisterPin(this->motorPins[0], bitRead(this->lookup[i], 0));
			setRegisterPin(this->motorPins[1], bitRead(this->lookup[i], 1));
			setRegisterPin(this->motorPins[2], bitRead(this->lookup[i], 2));
			setRegisterPin(this->motorPins[3], bitRead(this->lookup[i], 3));
			writeRegisters();
			delay(motorSpeed);
	  	}
	  	count++;
  	}
  	clearRegisters();
	
}

void SteppersOnShift::MoveBackward(int motorSpeed){
	
	int i, countsperrev = 512, count = 0; // count=count of steps made, countsperrev=number of steps per full revolution

	//Serial.println("stepper ON");
  	while(count < countsperrev )
    	
    	for(i = 7; i >= 0; i--){
			setRegisterPin(this->motorPins[3], bitRead(this->lookup[i], 0));
			setRegisterPin(this->motorPins[2], bitRead(this->lookup[i], 1));
			setRegisterPin(this->motorPins[1], bitRead(this->lookup[i], 2));
			setRegisterPin(this->motorPins[0], bitRead(this->lookup[i], 3));
			writeRegisters();
			delayMicroseconds(motorSpeed);
	  	}
	  	count++;
	  	
  	clearRegisters();
	
}


void SteppersOnShift::setRegisterPin(int index, int value){
  this->registers[index] = value;
}

void SteppersOnShift::clearRegisters(){
  for(int i = 7; i >=  0; i--){
     this->registers[i] = LOW;
  }
  writeRegisters();
} 

//Set and display registers
void SteppersOnShift::writeRegisters(){

  digitalWrite(this->latchPin, LOW);

  for(int i = 7; i >=  0; i--){
    digitalWrite(this->clockPin, LOW);

    digitalWrite(this->dataPin, this->registers[i]);
    digitalWrite(this->clockPin, HIGH);

  }
  
  digitalWrite(this->latchPin, HIGH);
}


