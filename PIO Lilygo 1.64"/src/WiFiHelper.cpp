#include "WiFiHelper.h"
#include "Config.h"  // Include the config for SSID, PASSWORD, TIME_ZONE
#include <lvgl.h>

extern lv_obj_t *ui_Label_Time;   // External reference to time label
extern lv_obj_t *ui_Label_date;   // External reference to date label

// Function to set up asynchronous, non-blocking WiFi connection
void setupWiFi() {
    // Initiate WiFi connection
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Asynchronous, non-blocking loop to wait for WiFi connection
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
}

// Function to fetch time from NTP server and update UI labels
void fetchNTPTime() {
    if (WiFi.status() == WL_CONNECTED) {
        struct tm timeInfo;
        if (getLocalTime(&timeInfo)) {
            // Format the time in HH:MM (12-hour format)
            char timeString[6];  // HH:MM format
            strftime(timeString, sizeof(timeString), "%I:%M %p", &timeInfo);  // %I for 12-hour format

            // Format the date in "Day, Month Date, Year" format
            char dateString[32];  // Fri, Sep 20, 2024
            strftime(dateString, sizeof(dateString), "%a, %b %d, %Y", &timeInfo);  // %a for day, %b for month, %d for day of the month, %Y for year

            // Update LVGL labels with the formatted time and date
            lv_label_set_text(ui_Label_Time, timeString);  // Update time label
            lv_label_set_text(ui_Label_date, dateString);  // Update date label

            Serial.printf("Time: %s, Date: %s\n", timeString, dateString);
        } else {
            Serial.println("Failed to obtain NTP time.");
        }
    } else {
        Serial.println("WiFi not connected. Cannot fetch NTP time.");
    }
}
