#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sender.h"


BatteryParameters batterySensorReadings[MAX_READINGS];  //stores all sensor readings for sending

BatteryParameters* readSensor(char* sensorReadingsFilePath) {
    FILE *fp;
    char readBuffer[30];
    fp = fopen(sensorReadingsFilePath, "r");
    if ( fp == NULL ) {
        printf( "failed to open file" ) ;
    }
    else {
        int item = 0;
       while (fgets(readBuffer, 30, fp))
       {
            char *batteryParameter = strtok(readBuffer, ",");   //split line
            while (batteryParameter) { //stores battery parameters
                batterySensorReadings[item].soc = atof(batteryParameter);
                batteryParameter = strtok(NULL, ",");

                batterySensorReadings[item].temperature = atof(batteryParameter);
                batteryParameter = strtok(NULL, ",");
                //battery state
                if (batterySensorReadings[item].soc < 20.0)
                {
                    batterySensorReadings[item].battStat = DISCHARGE;
                } else if (batterySensorReadings[item].soc > 80.0){
                    batterySensorReadings[item].battStat = OVERCHARGE;
                }
                if (batterySensorReadings[item].temperature < -20.0)
                {
                    batterySensorReadings[item].battStat = FREEZING;
                } else if (batterySensorReadings[item].temperature > 100.0){
                    batterySensorReadings[item].battStat = OVERHEATING;
                }
                item++;
            }
       }
        fclose(fp) ;
    }
        return batterySensorReadings;
}

void sendToConsole(BatteryParameters* parameters, int streamSize) {
    for(int item = 0; item < streamSize; item++) {
        printf("%f,%f\n", parameters[item].soc, batterySensorReadings[item].temperature);
    }
}

