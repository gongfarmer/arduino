#include <SHT1x.h>

#define sensorPin 18
#define clockPin 19
#define pumpPin 4

SHT1x th_sensor(sensorPin, clockPin);

void setup() {
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting up");
}

void loop() {
  float humidity;

  // Read humidity from sensor.
  // My sensor reads about 9 under the display value.
  humidity = 10 + th_sensor.readHumidity();
  Serial.print("humidity: ");
  Serial.println(humidity);

  // Decide whether to pump
  // if (humidity < 39.0) {  // This number is for days 1-18
  if (humidity < 61.0) {  // This number is for days 19-20
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
