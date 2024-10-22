#ifndef WEATHERHELPER_H
#define WEATHERHELPER_H

#include <ArduinoJson.h>

// Function to fetch weather data
void fetchWeatherData();

// Helper function to parse JSON data and update the UI
void updateWeatherUI(const String &jsonData);

// Add this line for the FreeRTOS Weather task
void weatherTask(void *pvParameters);

#endif // WEATHERHELPER_H
