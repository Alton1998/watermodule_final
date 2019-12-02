#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
const char *ssid =  "Alton";     // replace with your wifi ssid and wpa2 key
const char *pass =  "123456789";
const char* host = "http://192.168.43.158";
String url="/watermodule/TanksReading/";
WiFiClient client;

unsigned long echo = 0;
int ultraSoundSignal = 5; // Ultrasound signal pin
int ultraSoundSignalIN = 4; // Ultrasound signal pin

unsigned long ultrasoundValue = 0;

void setup()
{
Serial.begin(9600);
pinMode(ultraSoundSignal,OUTPUT);
pinMode(ultraSoundSignalIN,INPUT);
delay(10);
               
Serial.println("Connecting to ");
Serial.println(ssid); 
WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println(WiFi.localIP());

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
  if (WiFi.status() == WL_CONNECTED) {
int x = 0;
x = ping();
Serial.println(x);
delay(250); //delay 1/4 seconds.
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject();
    JSONencoder["id"] =1;
    JSONencoder["Tank_Reading_Recieved"]=x;
    JSONencoder["Tank"]=1;
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://192.168.43.158/watermodule/TanksReading/");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    http.addHeader("Authorization","Token 95bb3cbadc29617b6c4103f46ee50afaec82644f");
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();
  }
  else
  {
    Serial.println("Disconnected");
  }
  delay(5000);
}
