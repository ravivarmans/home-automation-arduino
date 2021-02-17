//Listing 4.4
// constants
#define DSD18B20PIN 5 
// pin for connecting the DATA contact (D1, GPIO5)
#define INTERVAL_GET_DATA 2000 // measurement interval, ms
// connect the library
// http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <OneWire.h>
// create a OneWire instance
OneWire ds (DSD18B20PIN);
// variable for the measurement interval
unsigned long millis_int1 = 0;
void setup (void) {
Serial.begin (9600);  // start the serial port
}
void loop () {
if (millis () - millis_int1> = INTERVAL_GET_DATA) {
// receive data from DS18B20
float temp = get_data_ds18b20 ();
// output to the serial port monitor
if (temp <100) {
	Serial.print ("temp ="); Serial.println (temp);
}
// start counting interval
millis_int1 = millis ();
// start counting interval
millis_int1 = millis ();
}
}
float get_data_ds18b20 (void) {
byte i;
byte present = 0;
byte type_s;
byte data [12];
byte addr [8];
float fTemp;
if (! ds.search (addr)) {
	Serial.println ("No more addresses.");
	Serial.println ();
	ds.reset_search ();
	delay (250);
	return 999;
}
Serial.print ("ROM =");
for (i = 0; i <8; i ++) {
	Serial.write ('');
	Serial.print (addr [i], HEX);
}
if (OneWire :: crc8 (addr, 7)! = addr [7]) {
	Serial.println ("CRC is not valid!");
	return 999;
}
Serial.println ();
// the first ROM byte indicates which chip
switch (addr [0]) {
case 0x10:
	Serial.println ("Chip = DS18S20"); // or old DS1820
	type_s = 1;
break;
case 0x28:
	Serial.println ("Chip = DS18B20");
	type_s = 0;
break;
case 0x22:
	Serial.println ("Chip = DS1822");
	type_s = 0;
break;
default:
	Serial.println ("Device is not a DS18x20 family device.");
	return 999;
}
ds.reset ();
ds.select (addr);
// start the temperature conversion by the sensor
ds.write (0x44, 1);
delay (1000); // wait 750 ms
present = ds.reset ();
ds.select (addr);
ds.write (0xBE);
// read the sensor RAM
for (i = 0; i <9; i ++) {
	data [i] = ds.read ();
	Serial.print (data [i], HEX);
	Serial.print ("");
}
// translate the received data into a temperature value
int16_t raw = (data [1] << 8) | data [0];
if (type_s) {
	raw = raw << 3;
if (data [7] == 0x10) {
	raw = (raw & 0xFFF0) + 12 - data [6];
}
} else {
	byte cfg = (data [4] & 0x60);
if (cfg == 0x00) raw = raw & ~ 7;
else if (cfg == 0x20) raw = raw & ~ 3;
else if (cfg == 0x40) raw = raw & ~ 1;
}
fTemp = (float) raw / 16.0;
return fTemp;
}
