// To get the realtime data from the ESP8266 

#include <MQ135.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

//Access point authentication details
const char *ssid =  "Edith";  
const char *pass =  "hellothere";
//API access tokens
long myChannelNumber = 1957363;
const char myWriteAPIKey[] = "0DTUGE61R105IENY";
 
 
DHT dht(D5, DHT11);
WiFiClient client;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
  Serial.print("initializing Data to 0");
}
 
void loop() {
  MQ135 gasSensor = MQ135(A0);
  float h = (float) dht.readHumidity();
  float t = (float) dht.readTemperature();
  float airQuality = gasSensor.getPPM();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  Serial.println("Air Quality: "+ (String)airQuality);
  ThingSpeak.setField( 1, t);
  ThingSpeak.setField( 2, h);
  ThingSpeak.setField(3,airQuality);
  ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
  delay(2000);
}
