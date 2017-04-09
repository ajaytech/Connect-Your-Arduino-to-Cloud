
#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//Your keys here
char pubkey[] = "";
//Your keys here
char subkey[] = "sub-c-7d1d2c40-16f9-11e7-b284-02ee2ddab7fe";
char channel[] = "SensorNode";
int a = 0;
void setup()
{
	Serial.begin(9600);
	Serial.println("Serial set up");

	while (!Ethernet.begin(mac)) {
		Serial.println("Ethernet setup error");
		delay(1000);
	}
 printIPAddress();
	Serial.println("Ethernet set up");

	PubNub.begin(pubkey, subkey);
	Serial.println("PubNub set up");
}
void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
void loop()
{
  int a = analogRead(A0);
	Ethernet.maintain();

	EthernetClient *client;
  
	Serial.println("publishing a message");
	client = PubNub.publish(channel, );
	if (!client) {
		Serial.println("publishing error");
		delay(1000);
		return;
	}
	while (client->connected()) {
		while (client->connected() && !client->available()) ; // wait
		char c = client->read();
		Serial.print(c);
	}
	client->stop();
	Serial.println();
	Serial.println("waiting for a message (subscribe)");
	PubSubClient *pclient = PubNub.subscribe(channel);
	if (!pclient) {
		Serial.println("subscription error");
		delay(1000);
		return;
	}
	while (pclient->wait_for_data()) {
		char c = pclient->read();
		Serial.print(c);
	}
	pclient->stop();
	Serial.println();
	Serial.println("retrieving message history");
	client = PubNub.history(channel);
	if (!client) {
		Serial.println("history error");
		delay(1000);
		return;
	}
	while (client->connected()) {
		while (client->connected() && !client->available()) ; // wait
		char c = client->read();
		Serial.print(c);
	}
	client->stop();
	Serial.println();

	delay(10000);
}
