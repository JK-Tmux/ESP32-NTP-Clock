/*
 * ESP32 NTP Clock
 * ----------------
 * Synchronizes time from pool.ntp.org via Wi-Fi
 * and displays the current Pacific Time (PST/PDT) [Can be altered to any time zone, see comments below]
 * on a TM1637 4-digit seven-segment display.
 */

#include <WiFi.h>
#include <TM1637Display.h>
#include <time.h>

#define CLK 22
#define DIO 21

// Change SSID & Password 
const char* ssid = "Enter SSID here";
const char* password = "Enter Password here";

TM1637Display display(CLK, DIO);

void setup() {
    display.setBrightness(7);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) delay(500);

// Replace the time zone string below with your own.
// A list of common POSIX time zone strings can be found here:
// https://github.com/yuan910715/Esp8266_Wifi_Matrix_Clock/blob/master/posix.md

configTzTime("PST8PDT,M3.2.0,M11.1.0", "pool.ntp.org"); 

    struct tm t;
    while (!getLocalTime(&t)) delay(500);
}

void loop() {
    struct tm t;

    if (getLocalTime(&t)) {
        static bool colon;

        display.showNumberDecEx(
            ((t.tm_hour % 12 ?: 12) * 100) + t.tm_min,
            (colon = !colon) ? 0x40 : 0,
            true
        );
    }

    delay(500);
}