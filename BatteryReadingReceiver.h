#define NO_OF_READINGS 50

void ComputeSMA(float data[], float average[]);
float ComputeMax(float data[]);
float ComputeMin(float data[]);

void ReadBatteryReadingsfromConsole(float* SOC, float* Temperature);
void BatteryReceiver(float* SOC, float* Temperature);
void PrintComputedReadingsOnConsole(float *BMSParameter, float MaxValue, float Minvalue, float SMA);