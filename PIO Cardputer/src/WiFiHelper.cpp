#include "WiFiHelper.h"
#include "WeatherHelper.h"
#include "Config.h"
#include <lvgl.h>
#include "LEDHelper.h"

extern lv_obj_t *ui_Label_Time;   // External reference to time label
extern lv_obj_t *ui_Label_date;   // External reference to date label

// Initialize LEDHelper object
LEDHelper led;

// Function to connect to WiFi and indicate status using the NeoPixel LED
void wifiTask(void *pvParameters) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        led.setLedColor(RED);  // Set to red while connecting
    }

    Serial.println("\nWiFi connected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    led.setLedColor(BLUE);  // Set to blue after connection

    // Set up NTP and time zone
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    setenv("TZ", TIME_ZONE, 1);
    tzset();

    Serial.println("NTP and timezone set.");

    // Ensure weatherTask is created only once
    xTaskCreate(weatherTask, "Weather Task", 4096, NULL, 1, NULL);

    vTaskDelete(NULL);  // Delete the WiFi task
}

// Function to set up asynchronous, non-blocking WiFi connection
void setupWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);  // Small delay to avoid spamming the Serial output
        Serial.print(".");
    }

    Serial.println("\nWiFi connected successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set up NTP and time zone
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");  // Set NTP servers
    setenv("TZ", TIME_ZONE, 1);  // Set the time zone from Config.h
    tzset();  // Apply the time zone settings

    Serial.println("NTP and timezone set.");
}


// Function to fetch time from NTP server and update UI labels
void fetchNTPTime() {
    if (WiFi.status() == WL_CONNECTED) {
        struct tm timeInfo;
        if (getLocalTime(&timeInfo)) {
            // Format the time in HH:MM (12-hour format)
            char timeString[6];
            strftime(timeString, sizeof(timeString), "%I:%M %p", &timeInfo);  // %I for 12-hour format and %p for AM/PM

            // Format the date in Day, Month Date, Year format
            char dateString[32];
            strftime(dateString, sizeof(dateString), "%a, %b %d, %Y", &timeInfo);

            // Update the LVGL labels
            lv_label_set_text(ui_Label_Time, timeString);  // Update time label
            lv_label_set_text(ui_Label_date, dateString);  // Update date label

            Serial.printf("Time: %s, Date: %s\n", timeString, dateString);

            led.setLedColor(GREEN);  // Green color

        } else {
            Serial.println("Failed to obtain NTP time.");
        }
    } else {
        Serial.println("WiFi not connected. Cannot fetch NTP time.");

        led.setLedColor(RED);  // Set LED to red while trying to connect
    }
}
