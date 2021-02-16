\\Listing 4.2
	// connect the DTH library
	#include "DHT.h"
	// constants
	#define DHTPIN 4 // pin (D2) connect the DATA pin
	#define DHTTYPE DHT22 // DHT 22 sensor
	#define INTERVAL_GET_DATA 2000 // measurement interval, ms
	// create an instance of the DHT object
	DHT dht (DHTPIN, DHTTYPE);
	// variable for the measurement interval
	unsigned long millis_int1 = 0;
	void setup () {
		Serial.begin (9600); // start the serial port
		dht.begin (); // start DHT
	}
	void loop () {
		if (millis () - millis_int1> = INTERVAL_GET_DATA) {
			// receive data from DHT11
			int humidity = get_data_humidity ();
			// output to the serial port monitor
			Serial.print ("humidity =");
			Serial.println (humidity);
			// start counting the interval
			millis_int1 = millis ();
		}
	}
	int get_data_humidity () {
		int h = dht.readHumidity ();
		return h;
	}
