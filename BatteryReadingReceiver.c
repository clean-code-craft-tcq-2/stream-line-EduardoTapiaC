#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "BatteryReadingReceiver.h"

float* ComputeSMA(float data[])
{
    float sum = 0.0;
    float average[NO_OF_READINGS] = {0};
    for(int i=0; i<NO_OF_READINGS; i++)
        {
            if(i<5) sum += data[i];
            else sum = sum + data[i] - data[i-5];
            average[i] = sum/5;
        }
        return average;
}

float ComputeMax(float data[])
{
    float Maximum = data[0];
    for(int i=1; i<NO_OF_READINGS; i++)
    {
        if(Maximum < data[i])
        {
            Maximum = data[i];
        }
    }
    return Maximum;
}

float ComputeMin(float data[])
{
    float Minimum = data[0];
    for(int i=1; i<NO_OF_READINGS; i++)
    {
        if(Minimum > data[i])
        {
            Minimum = data[i];
        }
    }
    return Minimum;
}

void ReadBatteryReadingsfromConsole(float* SOC, float* Temperature)
{
    for(int i=0; i<NO_OF_READINGS; i++)
    {
        scanf("%f ,%f",&SOC[i],&Temperature[i]);
    }
}

void PrintComputedReadingsOnConsole(float *BMSParameter, float MaxValue, float Minvalue, float* SMA)
{
  int readingIndex = 0;
  printf("Data received from sender\n");
  
  for(readingIndex = 0; readingIndex < NO_OF_READINGS; readingIndex++)
  {
    printf("Current Value: %f, SMA of last 5 Values: %f\n",BMSParameter[readingIndex], SMA[readingIndex]);
  }
  printf("Max value: %f, Min value: %f\n",MaxValue,Minvalue);
 
}

void BatteryReceiver(float* SOC, float* Temperature)
{
  ReadBatteryReadingsfromConsole(SOC, Temperature);
  PrintComputedReadingsOnConsole(SOC,ComputeMax(SOC),ComputeMin(SOC),ComputeSMA(SOC));
  PrintComputedReadingsOnConsole(Temperature,ComputeMax(Temperature),ComputeMin(Temperature),ComputeSMA(Temperature));
}