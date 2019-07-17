#include "shared.h"
#include <SPI.h>
#include "RF24.h"


// RF24
RF24 nRF(9, 10);  // init pins CE, CS

// OneWire
const unsigned long SENSOR_VALUES_SEND_INTERVAL = 2UL * 5UL * 1000UL;			// other sensor notifications interval
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
	nRF.setPALevel(RF24_PA_HIGH);
	nRF.openWritingPipe(RF_OUTSIDE_ADDRESS);

	// settle time
	delay(2000);

	Serial.println(F("Nastartovano"));
}

void sendTemp(int id, float value)
{
	Serial.println("Odesilam teplotu cidla " + String(id) + ": " + String(value));

	if (!nRF.write(&id, sizeof(id)))
	{
		Serial.println(F("Chyba pri odesilani 1!"));
	}
	delay(10);
	if (!nRF.write(&value, sizeof(value)))
	{
		Serial.println(F("Chyba pri odesilani 2!"));
	}
	Serial.println(F("Odeslano"));
}

void loop()
{
	unsigned long time = millis();

	if ((time - lastTemperatureSensorValuesSent) > SENSOR_VALUES_SEND_INTERVAL)
	{
		sendTemp(RF_SENSOR_OUTSIDE_TEMPERATURE_ID, 15);
		lastTemperatureSensorValuesSent = time;
	}
}
