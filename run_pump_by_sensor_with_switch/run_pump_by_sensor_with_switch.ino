// Author: Fraser Hanson
// Date: 2019
// Purpose: Maintain humidity in the incubator by running a pump when the humidity is too low.
// 
// Target humidity is set to one of two values:
//   On days 1-18, the humidity must be around 39.
//   On days 19-20, the humidity must be around 61.
// Switch does not progressively adjust humidity! ONLY these 2 values are settable.
// User must adjust the switch on the correct day.

#include <SHT1x.h>

#define sensorPin 18
#define clockPin 19
#define pumpPin 4
#define HUMIDITY_MIN 39.0
#define HUMIDITY_MAX 61.0
#define ANALOG_MAX 906

SHT1x th_sensor(sensorPin, clockPin);

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting up");
}

// Choose a target humidity based on the setting of the rotary switch.
// Input is rotary switch value (found by experimentation):
//      906 left full (const ANALOG_MAX)
//      453 middle is 453
//        0 right full
//  Left means less humidity, so full left must return HUMIDITY_MIN
float analogToHumidity(int value) {  
  return HUMIDITY_MAX - value * ((HUMIDITY_MAX - HUMIDITY_MIN) / ANALOG_MAX);
}

void loop() {
  // Read humidity from sensor, and target humidity from switch.
  // My sensor reads about 9 under the incubator's displayed value.
  float humidity = 10 + th_sensor.readHumidity();
  float targetHumidity = analogToHumidity(analogRead(A0));

  // Print the current humidity situation
  Serial.print("analog: ");
  Serial.print(analogRead(A0));
  Serial.print("  humidity: ");
  Serial.print(humidity);
  Serial.print(" / target: ");
  Serial.println(targetHumidity);
  return;

  // Decide whether to pump
  if (humidity < targetHumidity) {
    Serial.print("pump on!\n");
    digitalWrite(pumpPin, HIGH); // switch pump on
    delay(5000); // let pump run for a few seconds
    Serial.print("pump off. letting things settle for 30 seconds...\n");
    digitalWrite(pumpPin, LOW); // switch pump off
    delay(30000);
  } else {
    delay(5000);
  }
}
