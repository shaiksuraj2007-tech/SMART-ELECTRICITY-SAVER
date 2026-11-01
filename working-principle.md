# Working Principle

1. The electrical load is measured by the PZEM-004T energy-meter module installed according to its model-specific manual.
2. The meter calculates electrical quantities such as voltage, current, active power and accumulated energy.
3. The PZEM communicates the readings to the Arduino Uno through its TTL serial interface.
4. The Arduino reads the values, checks for invalid/missing data and calculates an estimated cost:

   **Estimated cost = Energy (kWh) × Configured cost per kWh**

5. A 16x2 I2C LCD displays voltage/current, power/energy and estimated cost on rotating pages.
6. If active power reaches or exceeds the configured threshold, the Arduino activates the buzzer.

## What makes it an electricity saver?

The prototype gives the user visibility of energy usage and an alert for high consumption. The user can then switch off unnecessary appliances or change usage habits. This first version does not automatically disconnect or control the load.

## Measurement terms

- **Voltage (V):** electrical potential difference.
- **Current (A):** rate of electric charge flow.
- **Active power (W):** rate at which electrical energy is being used.
- **Energy (kWh):** accumulated electrical energy over time.
- **Estimated cost:** approximate energy charge using a manually configured tariff.

## Limitations

The displayed estimate does not include tariff slabs, fixed charges, taxes or provider-specific billing rules. Accuracy depends on the meter model, correct installation and calibration.
