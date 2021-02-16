//Listing 4.1
#include "DHT.h"
// connecting the DTH library
#define DHTPIN 22
// connection pin of the DATA contact
#define DHTTYPE DHT22
// DHT 22 sensor
#define INTERVAL_GET_DATA 2000
// measurement interval, ms
DHT dht (DHTPIN, DHTTYPE);
// create an instance of the DHT object
unsigned long millis_int1 = 0;
// variable for the measurement interval

void setup () {
	Serial.begin (9600);
	// start the serial port
	dht.begin (); // start DHT
}
void loop () {
	if (millis () - millis_int1> = INTERVAL_GET_DATA) {
		int humidity = get_data_humidity ();
		// receive data from DHT11
		Serial.print ("humidity =");
		// output to the serial port monitor
		Serial.println (humidity);
		millis_int1 = millis ();
		// start counting the interval
	}
}
int get_data_humidity () {
	int h = dht.readHumidity ();
	return h;
}
