#include <Wire.h>
#include <DS1307.h>

DS1307 clock;

void init_clock();
void printTime();
void setDateRTC(int day, int month, int year);
void setHeureRTC(int h, int m, int s);