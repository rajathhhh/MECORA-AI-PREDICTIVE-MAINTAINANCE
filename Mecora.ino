#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

#define MPU_ADDR 0x68
#define TEMP_PIN 4
#define IN1 26
#define IN2 27

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

float baseline = 0;
unsigned long faultStart = 0;

int16_t read16() {
  return (Wire.read() << 8) | Wire.read();
}

void readAccel(int16_t &ax, int16_t &ay, int16_t &az) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  ax = read16();
  ay = read16();
  az = read16();
}

float getVibration() {
  const int samples = 100;

  float sx = 0, sy = 0, sz = 0;
  int16_t ax, ay, az;

  for (int i = 0; i < samples; i++) {
    readAccel(ax, ay, az);
    sx += ax;
    sy += ay;
    sz += az;
    delay(5);
  }

  float mx = sx / samples;
  float my = sy / samples;
  float mz = sz / samples;

  float sum = 0;

  for (int i = 0; i < samples; i++) {
    readAccel(ax, ay, az);

    float dx = ax - mx;
    float dy = ay - my;
    float dz = az - mz;

    sum += dx * dx + dy * dy + dz * dz;
    delay(5);
  }

  return sqrt(sum / samples) / 16384.0;
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  sensors.begin();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  Serial.println();
  Serial.println("================================");
  Serial.println("       AI MACHINE MECHANIC");
  Serial.println("================================");
  Serial.println("SYSTEM CHECK");

  Wire.beginTransmission(MPU_ADDR);

  if (Wire.endTransmission() == 0)
    Serial.println("[OK] MPU9250");
  else
    Serial.println("[ERROR] MPU9250");

  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);

  if (t != DEVICE_DISCONNECTED_C)
    Serial.println("[OK] DS18B20");
  else
    Serial.println("[ERROR] DS18B20");

  Serial.println("[OK] MOTOR");
  Serial.println();

  Serial.println("LEARNING HEALTHY MACHINE...");
  delay(2000);

  float total = 0;

  for (int i = 0; i < 20; i++) {
    float vibration = getVibration();
    total += vibration;

    Serial.print("Learning ");
    Serial.print(i + 1);
    Serial.println("/20");
  }

  baseline = total / 20.0;

  Serial.println();
  Serial.print("HEALTHY BASELINE: ");
  Serial.print(baseline, 4);
  Serial.println(" g");

  Serial.println();
  Serial.println("================================");
  Serial.println("       SYSTEM READY");
  Serial.println("       MONITORING ACTIVE");
  Serial.println("================================");
  Serial.println();
}

void loop() {

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  float vibration = getVibration();
  float score = vibration / baseline;

  bool fault = (temperature >= 50 || score >= 1.50);

  if (fault) {

    if (faultStart == 0)
      faultStart = millis();

    if (millis() - faultStart >= 3000) {

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      Serial.println();
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      Serial.println("       FAULT DETECTED");
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

      if (temperature >= 50 && score >= 1.50)
        Serial.println("CAUSE: TEMPERATURE + VIBRATION");
      else if (temperature >= 50)
        Serial.println("CAUSE: HIGH TEMPERATURE");
      else
        Serial.println("CAUSE: HIGH VIBRATION");

      Serial.println("ACTION: MOTOR STOPPED");
      Serial.println();

      while (true) {
        delay(1000);
      }
    }

  } else {
    faultStart = 0;
  }

  Serial.print("TEMP: ");
  Serial.print(temperature, 1);
  Serial.print(" C   |   VIB: ");
  Serial.print(vibration, 3);
  Serial.print(" g   |   AI SCORE: ");
  Serial.print(score, 2);
  Serial.print("   |   ");

  if (temperature >= 40 || score >= 1.30)
    Serial.println("WARNING");
  else
    Serial.println("NORMAL");

  delay(500);
}
