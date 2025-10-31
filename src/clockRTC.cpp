#include "../lib/clock.h"

void init_clock() {
    Serial.begin(9600);
    clock.begin();
    clock.fillByYMD(2025, 10, 22);
    clock.fillByHMS(9, 49, 30);
    clock.fillDayOfWeek(WED);
    clock.setTime();
}

void setDateRTC(int day, int month, int year) {
    clock.fillByYMD(year, month, day); // format (année, mois, jour)
    clock.setTime();
    Serial.print("Date RTC réglée : ");
    Serial.print(day); Serial.print("/"); Serial.print(month); Serial.print("/"); Serial.println(year);
}

void setHeureRTC(int h, int m, int s) {
    clock.fillByHMS(h, m, s);
    clock.setTime();
    Serial.print("Heure RTC réglée : ");
    Serial.print(h); Serial.print(":"); Serial.print(m); Serial.print(":"); Serial.println(s);
}

void printTime() {
    clock.getTime();
    Serial.print(clock.hour, DEC);
    Serial.print(":");
    Serial.print(clock.minute, DEC);
    Serial.print(":");
    Serial.print(clock.second, DEC);
    Serial.print("	");
    Serial.print(clock.month, DEC);
    Serial.print("/");
    Serial.print(clock.dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(clock.year + 2000, DEC);
    Serial.print(" ");
    Serial.print(clock.dayOfMonth);
    Serial.print("*");
    switch (clock.dayOfWeek) {
        case MON:
            Serial.print("MON");
            break;
        case TUE:
            Serial.print("TUE");
            break;
        case WED:
            Serial.print("WED");
            break;
        case THU:
            Serial.print("THU");
            break;
        case FRI:
            Serial.print("FRI");
            break;
        case SAT:
            Serial.print("SAT");
            break;
        case SUN:
            Serial.print("SUN");
            break;
    }
    Serial.println(" ");
}
