//Listing 4.6
	// list of pins for connecting to s0, s1, s2 multiplexer
	// D5, D7, D8 (GPIO 14, 13, 15)
	int pins [] = {14, 13, 15};
	// Array of binary numbers defining 
	//the number of the selected in/out
	// 4051 microcircuits, from 1 to 8.
	int bin [] = {B000,B001,B010,B011,B100,B101,B110,B111};
	// service variables
	int row;
	int r0 = 0;
	int r1 = 0;
	int r2 = 0;
	int avalue = 0;
	void setup (void) {
		// inputs to connect to multiplexer as OUTPUT
		for (int i = 0; i <3; i ++) {
			pinMode (pins [i], OUTPUT);
		}
		// start the serial port
		Serial.begin (9600);
	}
	void loop (void) {
		for (int i = 0; i <8; i ++) {
			// select multiplexer input
			row = bin [i];
			r0 = row & 0x01;
			r1 = (row >> 1) & 0x01; //
			r2 = (row >> 2) & 0x01; //
			digitalWrite (pins [i], r0);
			digitalWrite (pins [i], r1);
			digitalWrite (pins [i], r2);
			// get data from A0
			Avalue = analogRead (A0);
			// output to the serial port monitor
			Serial.print ("analog input ="); 
			Serial.print (i);
			Serial.println ("="); 
			Serial.println (avalue);
		}
		// pause
		delay (2000);
	}
