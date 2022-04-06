#define CATCH_CONFIG_MAIN 


#include "test/catch.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sender.h"


float error = 0.0005;
BatteryParameters result[10];
// Write Test environment to probe all states of battery and avoid line duplication.

TEST_CASE("Reading sensors") {
    readSensor("tests.txt");

  SECTION( "read 1 value" ) {
    result[0] = {.soc = 50.0, .temperature = 80.0, .battStat = BATTERY_OK};
    REQUIRE(result[0].battStat == batterySensorReadings[0].battStat);
    REQUIRE((result[0].soc - batterySensorReadings[0].soc) < error);
    REQUIRE((result[0].temperature - batterySensorReadings[0].temperature) < error);
  }
  SECTION("battery discharging") {
    result[1] ={.soc = 0.0, .temperature = 80.0, .battStat = DISCHARGE};
    REQUIRE(result[1].battStat == batterySensorReadings[1].battStat);
    REQUIRE(result[1].soc - batterySensorReadings[1].soc < error);
    REQUIRE(result[1].temperature - batterySensorReadings[1].temperature < error);
  }
  SECTION("battery overcharge") {
    result[2] ={.soc = 100.0, .temperature = 80.0, .battStat = OVERCHARGE};
    REQUIRE(result[2].battStat == batterySensorReadings[2].battStat);
    REQUIRE(result[2].soc - batterySensorReadings[2].soc < error);
    REQUIRE(result[2].temperature - batterySensorReadings[2].temperature < error);
  }

  SECTION("battery Overheating") {
    result[3] ={.soc = 50.0, .temperature = 110.0, .battStat = OVERHEATING};
    REQUIRE(result[3].battStat == batterySensorReadings[3].battStat);
    REQUIRE(result[3].soc - batterySensorReadings[3].soc < error);
    REQUIRE(result[3].temperature - batterySensorReadings[3].temperature < error);
  }

  SECTION("battery Freezing") {
    result[4] ={.soc = 50.0, .temperature = -30.0, .battStat = FREEZING};
    REQUIRE(result[4].battStat == batterySensorReadings[4].battStat);
    REQUIRE(result[4].soc - batterySensorReadings[4].soc < error);
    REQUIRE(result[4].temperature - batterySensorReadings[4].temperature < error);
  }

  SECTION("Read Multiple sensors") {
    result[5] ={.soc = 0.0, .temperature = 20.0, .battStat = DISCHARGE};
    result[6] ={.soc = 70.1, .temperature = 60.0, .battStat = BATTERY_OK};
    result[7] ={.soc = 50.0, .temperature = 120.0, .battStat = OVERHEATING};
    REQUIRE(result[5].battStat == batterySensorReadings[5].battStat);
    REQUIRE(result[5].soc - batterySensorReadings[5].soc < error);
    REQUIRE(result[5].temperature - batterySensorReadings[5].temperature < error);
    REQUIRE(result[6].battStat == batterySensorReadings[6].battStat);
    REQUIRE(result[6].soc - batterySensorReadings[6].soc < error);
    REQUIRE(result[6].temperature - batterySensorReadings[6].temperature < error);
    REQUIRE(result[7].battStat == batterySensorReadings[7].battStat);
    REQUIRE(result[7].soc - batterySensorReadings[7].soc < error);
    REQUIRE(result[7].temperature - batterySensorReadings[7].temperature < error);
  }


}



