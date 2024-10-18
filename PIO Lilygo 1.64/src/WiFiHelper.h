#ifndef WIFIHELPER_H
#define WIFIHELPER_H

#include <WiFi.h>
#include <time.h>

// Function declarations
void setupWiFi();
bool isWiFiConnected();
void fetchNTPTime();

#endif // WIFIHELPER_H
