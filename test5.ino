#include < NewPing.h >

#define TRIGGER_PIN 3 //Trig
#define ECHO_PIN 2    //Echo
#define MAX_DIST 200  //200 centimeter

int led = 13;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(50); //50 millisecond delay
  unsigned int ultrSonic = sonar.ping();

  if ((ultrSonic / US_ROUNDTRIP_CM) < 5) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
