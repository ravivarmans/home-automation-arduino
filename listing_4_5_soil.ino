//Listing 4.5
	#define INTERVAL_GET_DATA 2000 // measurement interval, ms
	#define SOILMOISTUREPIN A8 // pin for connecting contact A0
	// full watering value
	#define MINVALUESOILMOISTURE 220
	// critical dryness value
	#define MAXVALUESOILMOISTURE 900
	// variable for the measurement interval
	unsigned long millis_int1 = 0;
	void setup (void) {
		// start the serial port
		Serial.begin (9600);
	}
	void loop (void) {
		if (millis () - millis_int1> = INTERVAL_GET_DATA) {
			// get data from SoilMoisture sensor
			float moisture = get_data_soilmoisture ();
			// output to the serial port monitor
			Serial.print ("soilmoisture ="); Serial.println (moisture);
			Serial.println ("%");
			// start counting interval
			millis_int1 = millis ();
		}
	}
	// get data from SoilMoisture sensor
	float get_data_soilmoisture () {
		// get the value from the analog output of the sensor
		int avalue = analogRead (SOILMOISTUREPIN);
		// scale the value to percent
		avalue = constrain (avalue, MINVALUESOILMOISTURE, MAXVALUESOILMOISTURE);
		int moisture = map (avalue, MINVALUESOILMOISTURE,
		MAXVALUESOILMOISTURE, 100,0);
		return (float) moisture;
	}
