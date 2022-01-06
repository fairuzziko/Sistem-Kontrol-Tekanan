#include <HX710B.h>

#define inletValvePin 6
#define pumpPin 5
#define exhaustValvePin 7
const int DOUT = 3;   //sensor data pin
const int SCLK  = 9;   //sensor clock pin

int change = 3;
int sensor_value = 0;

HX710B pressure_sensor; 

void setup() {
  Serial.begin(115200);
  pinMode(inletValvePin, OUTPUT);
  pinMode(exhaustValvePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pressure_sensor.begin(DOUT, SCLK);
}

void loop() {
  if(Serial.available()) {
      byte command=Serial.read();
      if(command==97) {      // 'f'
        change=1;
      }
      else if (command==98){
        change=2;
      }
      else if (command==99){
        change=3;
      }
  }
  
  if (change==1) {
    digitalWrite(LED_BUILTIN, HIGH); //inlet
    digitalWrite(inletValvePin,LOW); // turn pressure valve HIGH
    analogWrite(pumpPin,255); // make sure pump is on
    digitalWrite(exhaustValvePin,HIGH); // turn exhaust valve LOW
  }
  
  else if (change==3) { //exhaust pump low
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
    analogWrite(pumpPin,0); // make sure pump is on
    digitalWrite(exhaustValvePin,LOW); // turn exhaust valve LOW
  }

  else if (change==2){ //hold
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
    analogWrite(pumpPin, 0);  // make sure pump is on
    digitalWrite(exhaustValvePin,HIGH); // turn exhaust valve LOW
  }

  
  if (pressure_sensor.is_ready()) {
    Serial.print("PSI: ");
    Serial.println(pressure_sensor.psi());
  }
  
}
