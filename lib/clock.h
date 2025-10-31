#include <Wire.h>
#include <DS1307.h>

DS1307 clock;

void init_clock();
void printTime();
void setDateRTC(int day, int month, int year);
void setHeureRTC(int h, int m, int s);
void getDS1307Time(byte *second, byte *minute, byte *hour, byte *day, byte *month, byte *year);