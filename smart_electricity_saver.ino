/*
  SMART ELECTRICITY SAVER
  ECE - 2nd Year Mini Project
  Controller : Arduino Uno
  Meter      : PZEM-004T (confirm library/model compatibility)
  Display    : 16x2 I2C LCD
  Alert      : Active buzzer module

  Low-voltage pin map:
    PZEM TX -> Arduino D10 (SoftwareSerial RX)
    PZEM RX -> Arduino D11 (SoftwareSerial TX)
    LCD SDA -> A4, LCD SCL -> A5
    Buzzer  -> D7

  SAFETY: PZEM AC-side wiring must follow the exact module manual
  and be completed by a qualified person. Never connect mains to
  Arduino pins or a breadboard.
*/

#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// Change 0x27 to 0x3F if that is your LCD backpack address.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// SoftwareSerial constructor order: Arduino RX, Arduino TX.
SoftwareSerial pzemSerial(10, 11);
PZEM004Tv30 pzem(pzemSerial);

const byte BUZZER_PIN = 7;
const float COST_PER_KWH = 7.00;        // EXAMPLE ONLY: set your local tariff
const float POWER_LIMIT_WATTS = 500.0;  // Alert threshold; adjust for your project

unsigned long lastReadMs = 0;
unsigned long lastPageMs = 0;
const unsigned long READ_INTERVAL_MS = 1000;
const unsigned long PAGE_INTERVAL_MS = 3000;

float voltage = NAN;
float current = NAN;
float power = NAN;
float energy = NAN;
float estimatedCost = NAN;
byte displayPage = 0;
bool meterDataValid = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);
  pzemSerial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Electric");
  lcd.setCursor(0, 1);
  lcd.print("Saver Starting");
  delay(1500);
  lcd.clear();

  Serial.println(F("Smart Electricity Saver started"));
}

void loop() {
  const unsigned long now = millis();

  if (now - lastReadMs >= READ_INTERVAL_MS) {
    lastReadMs = now;
    readMeter();
    updateAlert();
    printSerialData();
  }

  if (now - lastPageMs >= PAGE_INTERVAL_MS) {
    lastPageMs = now;
    displayPage = (displayPage + 1) % 3;
    showDisplayPage();
  }
}

void readMeter() {
  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();

  // Treat missing/invalid readings as a communication or meter error.
  meterDataValid = !isnan(voltage) && !isnan(current) &&
                   !isnan(power) && !isnan(energy);

  if (meterDataValid) {
    estimatedCost = energy * COST_PER_KWH;
  } else {
    estimatedCost = NAN;
    Serial.println(F("ERROR: No valid PZEM data. Check model, wiring and library."));
  }

  showDisplayPage();
}

void updateAlert() {
  if (meterDataValid && power >= POWER_LIMIT_WATTS) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void showDisplayPage() {
  lcd.clear();

  if (!meterDataValid) {
    lcd.setCursor(0, 0);
    lcd.print("Meter Data Error");
    lcd.setCursor(0, 1);
    lcd.print("Check PZEM link");
    return;
  }

  if (displayPage == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Voltage: ");
    lcd.print(voltage, 1);
    lcd.print("V");
    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(current, 2);
    lcd.print("A");
  } else if (displayPage == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Power: ");
    lcd.print(power, 1);
    lcd.print("W");
    lcd.setCursor(0, 1);
    lcd.print("Energy: ");
    lcd.print(energy, 3);
    lcd.print("kWh");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Cost: Rs ");
    lcd.print(estimatedCost, 2);
    lcd.setCursor(0, 1);
    if (power >= POWER_LIMIT_WATTS) {
      lcd.print("HIGH POWER ALERT");
    } else {
      lcd.print("Usage Normal");
    }
  }
}

void printSerialData() {
  if (!meterDataValid) return;

  Serial.print(F("Voltage: "));
  Serial.print(voltage, 1);
  Serial.print(F(" V | Current: "));
  Serial.print(current, 2);
  Serial.print(F(" A | Power: "));
  Serial.print(power, 1);
  Serial.print(F(" W | Energy: "));
  Serial.print(energy, 3);
  Serial.print(F(" kWh | Est. cost: Rs "));
  Serial.println(estimatedCost, 2);
}
