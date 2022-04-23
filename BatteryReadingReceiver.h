#define NO_OF_READINGS 50

float ComputeSMA(float data[]);
float ComputeMax(float data[]);
float ComputeMin(float data[]);

void ReadBatteryReadingsfromConsole(float* SOC, float* Temperature);
void BatteryReceiver(float* SOC, float* Temperature);
void PrintComputedReadingsOnConsole(float *BMSParameter, float MaxValue, float Minvalue, float SMA);