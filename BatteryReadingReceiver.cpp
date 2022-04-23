#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "BatteryReadingReceiver.h"

TEST_CASE("Tests to check whether sensor data is read from console") 
{
  float Temperature[NO_OF_READINGS] = {0};
  float SOC[NO_OF_READINGS] = {0};
  float Current_MaxValue, Current_MinValue, Current_SMAValue, expectedMaxValue, expectedMinValue, expectedSMAValue;
  
  BatteryReceiver(SOC, Temperature);
  float expectedoutput[2][2] = {{50,50.5}, {51,75}};
  for(int i=0;i<2;i++)
  {
      
    REQUIRE(SOC[i] == expectedoutput[i][0]);
    REQUIRE(Temperature[i] == expectedoutput[i][1]);
  }
  
  // Verify Max, Min values are correct for parameter SOC
  expectedMaxValue = 98.000000;
  expectedMinValue = 1.000000;
  Current_MaxValue = ComputeMax(SOC);
  Current_MinValue = ComputeMin(SOC);
  REQUIRE(Current_MaxValue == expectedMaxValue);
  REQUIRE(Current_MinValue == expectedMinValue);
    
  // Verify Max, Min values are correct for parameter Temperature
  expectedMaxValue = 139.441;
  expectedMinValue = -34.000000;
  Current_MaxValue = ComputeMax(TemperatureSOC);
  Current_MinValue = ComputeMin(Temperature);
  REQUIRE(Current_MaxValue == expectedMaxValue);
  REQUIRE(Current_MinValue == expectedMinValue);
}