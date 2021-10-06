#ifndef SteppersOnShift_h
#define SteppersOnShift_h

// library interface description

class SteppersOnShift{
	private:
		int dataPin;   // on arduino
		int latchPin;  //on arduino
		int clockPin;  //on arduino
		int motorPins[4];	// on register
		int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
		bool registers[8];
		
		//methods
		void setRegisterPin(int index, int value);
		void clearRegisters();
		void writeRegisters();
		
	  
	public:
		SteppersOnShift( int dataPin, int latchPin, int clockPin, int motorPin1, int motorPin2, int motorPin3,int motorPin4);
	  	void MoveForward(int motorSpeed);
	  	void MoveBackward(int motorSpeed);
	  	
};


#endif

