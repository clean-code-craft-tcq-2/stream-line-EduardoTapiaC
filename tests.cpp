#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sender.h"

TEST_CASE("Read sensors") {
  char sensors[] = "50.0,80.0\n";
  batterySensorReadings[0] ={.soc = 50.0, .temperature = 80.0, .battStat = BATTERY_OK};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
}

TEST_CASE("battery undercharge") {
  char sensors[] = "0.0,80.0\n";
  batterySensorReadings[0] ={.soc = 0.0, .temperature = 80.0, .battStat = DISCHARGE};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
}

TEST_CASE("battery overcharge") {
  char sensors[] = "100.0,80.0\n";
  batterySensorReadings[0] ={.soc = 100.0, .temperature = 80.0, .battStat = OVERCHARGE};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
}

TEST_CASE("battery Overheating") {
  char sensors[] = "50.0,110.0\n";
  batterySensorReadings[0] ={.soc = 50.0, .temperature = 110.0, .battStat = OVERHEATING};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
}

TEST_CASE("battery Freezing") {
  char sensors[] = "50.0,-20.0\n";
  batterySensorReadings[0] ={.soc = 50.0, .temperature = -20.0, .battStat = FREEZING};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
}

TEST_CASE("Read Multiple sensors") {
  char sensors[] = "10.0,20.0\n70.1,60.0\n50.0,120.0\n";
  batterySensorReadings[0] ={.soc = 10.0, .temperature = 20.0, .battStat = DISCHARGE};
  batterySensorReadings[1] ={.soc = 70.1, .temperature = 60.0, .battStat = BATTERY_OK};
  batterySensorReadings[2] ={.soc = 50.0, .temperature = 120.0, .battStat = OVERHEATING};
  BatteryParameters result = readSensor(sensors);
  REQUIRE(result.battStat == batterySensorReadings[0].battStat);
  REQUIRE(result.soc == batterySensorReadings[0].soc);
  REQUIRE(result.temperature == batterySensorReadings[0].battStat);
  REQUIRE(result.battStat == batterySensorReadings[1].battStat);
  REQUIRE(result.soc == batterySensorReadings[1].soc);
  REQUIRE(result.temperature == batterySensorReadings[1].battStat);
  REQUIRE(result.battStat == batterySensorReadings[2].battStat);
  REQUIRE(result.soc == batterySensorReadings[2].soc);
  REQUIRE(result.temperature == batterySensorReadings[2].battStat);
}

TEST_CASE("test sender output csv format") {
  char result[] = "50.0,51.0\n52.0,53.0\n";
  REQUIRE(strcmp(sendConsole(batterySensorReadings), result) == 0);
}