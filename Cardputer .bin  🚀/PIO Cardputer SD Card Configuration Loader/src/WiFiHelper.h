#ifndef WIFIHELPER_H
#define WIFIHELPER_H

#include <WiFi.h>
#include <time.h>

// Function declarations
void setupWiFi();
bool isWiFiConnected();
void fetchNTPTime();

// Add this line for the FreeRTOS WiFi task
void wifiTask(void *pvParameters);

#endif // WIFIHELPER_H
