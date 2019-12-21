
#include <SPI.h>
#include <UIPEthernet.h>
byte mac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31};
IPAddress server(172,16,34,3);  // numeric IP for Google (no DNS)
IPAddress ip(172,16,34,51);
unsigned long echo = 0;
int ultraSoundSignal = 3; // Ultrasound signal pin
int ultraSoundSignalIN = 2; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;

EthernetClient client;

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ;
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  Serial.println("connecting...");

 
}
unsigned long ping(){
pinMode(ultraSoundSignal, OUTPUT); // Switch signalpin to output
digitalWrite(ultraSoundSignal, LOW); // Send low pulse
delayMicroseconds(2); // Wait for 2 microseconds
digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
delayMicroseconds(15); // Wait for 15 microseconds
digitalWrite(ultraSoundSignal, LOW); // Holdoff
pinMode(ultraSoundSignalIN, INPUT); // Switch signalpin to input
digitalWrite(ultraSoundSignalIN, HIGH); // Turn on pullup resistor
// please note that pulseIn has a 1sec timeout, which may
// not be desirable. Depending on your sensor specs, you
// can likely bound the time like this — marcmerlin
// echo = pulseIn(ultraSoundSignal, HIGH, 38000)
echo = pulseIn(ultraSoundSignalIN, HIGH); //Listen for echo
//Serial.println(echo);
ultrasoundValue = (echo / 58.138);
return ultrasoundValue;

}
void loop()
{
   if (client.connect(server, 80)) {
    Serial.println("connected");
    int x = 0;
    x = ping();
    Serial.println(x);
    // Make a HTTP request:
    Serial.println("connected");
  client.println("GET /watermodule/TanksReading/"+String(x)+"/1/ HTTP/1.1");
  client.println("Host: 172.16.34.3");
  client.println("User-Agent: Arduino/1.0");
  client.println("Content-Type: application/json;");
   client.println("Connection: close");
  client.println("Authorization: Token 95bb3cbadc29617b6c4103f46ee50afaec82644f");
//  client.print("Content-Length: ");
//  client.println(measureJson(doc));
//   serializeJson(doc, client);
//  Serial.println(doc)
  delay(5000);
  }
 
 
 
 
  else {
  }
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}
