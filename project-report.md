# SMART ELECTRICITY SAVER
## Mini Project Report – ECE 2nd Year

**Student Name:** ____________________  
**Roll Number:** ____________________  
**Department:** Electronics and Communication Engineering  
**College:** ____________________  
**Project Guide:** ____________________  
**Academic Year:** ____________________

## Abstract

The Smart Electricity Saver is an Arduino Uno based electricity monitoring and alert system. A PZEM-004T energy-meter module measures voltage, current, active power and accumulated energy for a connected electrical load. The measured values are sent to the Arduino through a serial interface and displayed on a 16x2 I2C LCD. The system estimates the electricity cost using a configurable cost per kilowatt-hour and activates a buzzer when power consumption exceeds a preset threshold. The prototype aims to make electricity usage easier to understand and encourage energy-conscious behaviour.

## 1. Objectives

- Measure important electrical parameters of a connected load.
- Display readings in an understandable format.
- Estimate energy cost from accumulated kWh.
- Alert the user when power exceeds a configured limit.
- Demonstrate sensor interfacing, serial communication and embedded programming.

## 2. Hardware and Software

Hardware: Arduino Uno, compatible PZEM-004T meter and CT/interface, 16x2 I2C LCD, active buzzer module, low-voltage wiring and a safe enclosure.

Software: Arduino IDE, PZEM004Tv30-compatible library, LiquidCrystal_I2C library and embedded C++.

## 3. Methodology

The PZEM energy meter senses the electrical parameters according to its own installation requirements. It transmits measurements to the Arduino. The Arduino validates the readings, calculates an approximate cost, updates the LCD and compares active power against a preset threshold. The buzzer is activated when the threshold is reached.

## 4. Expected Outcome

The prototype should display valid voltage, current, power and energy readings when correctly installed and connected. It should estimate cost from the configured tariff and activate an alert above the configured power threshold. Actual results must be recorded after supervised testing.

## 5. Applications

- Educational energy-monitoring demonstrations.
- Monitoring an individual appliance or test load.
- Awareness of electricity consumption in homes and laboratories.
- Foundation for future IoT-based energy monitoring.

## 6. Future Scope

- Add Wi-Fi monitoring using an ESP32 or communication module.
- Store daily/monthly readings and generate usage graphs.
- Add multi-load monitoring.
- Add tariff slabs and a more complete bill estimator.
- Investigate certified automatic load control with appropriate protection and professional design.

## 7. Conclusion

The Smart Electricity Saver demonstrates how a microcontroller and energy-meter module can monitor electrical usage, present useful measurements and alert users to high power consumption. It provides a practical introduction to embedded systems and energy monitoring.

## Safety Statement

AC mains can cause fatal electric shock and fire. The mains-side meter and load connections must be installed in a properly rated enclosure by a qualified person. Never work on exposed live conductors. The Arduino and its low-voltage peripherals must remain appropriately isolated from mains circuits.
