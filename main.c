#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sender.h"

int main() {
    readSensor("sensors.txt");
    sendToConsole(batterySensorReadings, 50);

    return 0;
}

