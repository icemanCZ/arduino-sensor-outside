#include "homeiot_shared.h"
#include "nRF24L01.h"
#include "RF24.h"


// RF24
RF24 nRF(9, 10);  // init pins CE, CS

// OneWire
const unsigned long SENSOR_VALUES_SEND_INTERVAL = 60UL * 2UL * 1000UL;			// other sensor notifications interval
unsigned long lastTemperatureSensorValuesSent = 0;								// time from last temperature sensor notification


void setup()
{
	// serial line communication with 9600 baud
	Serial.begin(9600);

	Serial.println(F("Startuji"));

	// begin nRF24 communication
	Serial.println(F("  RF24"));
	nRF.begin();
	nRF.stopListening();
	initRF(nRF);
	nRF.openWritingPipe(RF_OUTSIDE_ADDRESS);

	// settle time
	delay(2000);


	//Serial.println(F("Nastaveni nRF21: "));
	//fdevopen(&serial_putc, 0);
	//nRF.printDetails();
	//Serial.println(F(""));

	Serial.println(F("Nastartovano"));
}

void loop()
{
	unsigned long time = millis();

	if ((time - lastTemperatureSensorValuesSent) > SENSOR_VALUES_SEND_INTERVAL)
	{
		sendTemp(nRF, RF_SENSOR_OUTSIDE_TEMPERATURE_ID, 15.0);
		lastTemperatureSensorValuesSent = time;
	}
}
