#ifndef CURRENT_MEASUREMENTS_H
#define CURRENT_MEASUREMENTS_H

#define MAX_READINGS 50

// Battery state of charge:
// DISCHARGE soc < 20%
// OVERCHARGE soc > 80%
// OVERHEATING temperature > 100
// FREEZING temperature < -20
enum batteryStatus{BATTERY_OK, DISCHARGE = 2, OVERCHARGE = 4, OVERHEATING = 8, FREEZING = 16};

typedef struct BatteryParameters{
  float soc;                // state of charge 0.0 - 100.0
  float temperature;        // temperature -40.0 to 140.0
  unsigned int battStat;    //battery status flags. see batteryStatus enum
}BatteryParameters;

BatteryParameters batterySensorReadings[MAX_READINGS];
#endif