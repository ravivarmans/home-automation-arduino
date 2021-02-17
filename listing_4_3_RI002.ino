\\Listing 4.3
	#define INTERVAL_GET_DATA 2000 // measurement interval, ms
	#define DS18B20PIN 23 // pin for connecting the DATA contact
	// connect the OneWire library
	#include <OneWire.h>
	// create a OneWire object
	OneWire ds (DS18B20PIN);
	// variable for the measurement interval
	unsigned long millis_int1 = 0;
	void setup (void) {
		// start the serial port
		Serial.begin (9600);
	}
	void loop (void) {
		if (millis () - millis_int1> = INTERVAL_GET_DATA) {
			// receive data from DS18B20
			float temp = get_data_ds18b20 ();
			// output to the serial port monitor
			if (temp <100) {
				Serial.print ("temp ="); Serial.println (temp);
			}
			// start counting interval
			millis_int1 = millis ();
		}
	}
	// receive data from the DS18B20 sensor
	float get_data_ds18b20 () {
		byte i;
		byte present = 0;
		byte data [12];
		byte addr [8];
		int Temp;
		float fTemp = 0.0;
		if (! ds.search (addr)) {
			Serial.print ("No more addresses. \ N");
			ds.reset_search ();
			return 999;
		}
		// output to monitor unique address of 1-Wire device
		for (i = 0; i <8; i ++) {
			Serial.print (addr [i], HEX);
			Serial.print ("");
		}
		if (OneWire :: crc8 (addr, 7)! = addr [7]) {
			Serial.print ("CRC is not valid! \ N");
			return 999; DIGITAL TEMPERATURE SENSOR RI002 37
		}
		if (addr [0]! = 0x28) {
			Serial.print ("Device is not a DS18S20 family \N");
			return 999;
		}
		ds.reset ();
		ds.select (addr);
		// start the temperature conversion by the sensor
		ds.write (0x44,1);
		delay (750); // wait 750 ms
		present = ds.reset ();
		ds.select (addr);
		ds.write (0xBE);
		// read the sensor RAM
		for (i = 0; i <9; i ++) {
			data [i] = ds.read ();
		}
		Temp = ((data [1] << 8) + data [0]);
		// convert to float value
		fTemp = 1.0 * Temp/16+(float (Temp% 16))*1.0/16;
		return fTemp;
	}
