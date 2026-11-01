#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 26

const float TEMP_LIMIT = 30.0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  delay(2000);

  Serial.println();
  Serial.println("=== ESP32 SENSE, DECIDE & ACT ===");
  Serial.println("Temperature Monitoring Lab");
  Serial.println("DHT22: GPIO 4");
  Serial.println("LED: GPIO 26");
  Serial.println("Temperature limit: 30 C");
  Serial.println("--------------------------------");
}

void loop() {

  // 1. SENSE
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 2. VALIDATE
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("ERROR: Failed to read DHT22.");

    // Safe state
    digitalWrite(LED_PIN, LOW);

    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  // 3. DECIDE
  if (temperature > TEMP_LIMIT) {

    // 4. ACT
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Status: ALERT");
    Serial.println("Action: LED ON");

  } else {

    digitalWrite(LED_PIN, LOW);

    Serial.println("Status: NORMAL");
    Serial.println("Action: LED OFF");
  }

  Serial.println("--------------------------------");

  // 5. WAIT AND REPEAT
  delay(2000);
}