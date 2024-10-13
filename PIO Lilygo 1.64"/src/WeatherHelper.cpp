#include "WeatherHelper.h"
#include "Config.h"
#include <HTTPClient.h>
#include <lvgl.h>
#include "ui.h"

extern lv_obj_t *ui_Label_temp;
extern lv_obj_t *ui_Label_hum;
extern lv_obj_t *ui_Label_condition;
extern lv_obj_t *ui_Label_winddir;
extern lv_obj_t *ui_Image_compass;
extern lv_obj_t *ui_TextArea_Data;

void fetchWeatherData() {
    // URL for the weather API request
    String url = String("https://api.weatherapi.com/v1/current.json?key=") + API_KEY + "&q=" + LOCATION;

    HTTPClient http;
    http.begin(url);  // Specify the URL
    int httpResponseCode = http.GET();  // Send the request

    if (httpResponseCode > 0) {
        String response = http.getString();  // Get the response payload
        Serial.println(response);  // Print the response (for debugging)
        
        // Pass the JSON data to be parsed and used in the UI
        updateWeatherUI(response);
    } else {
        Serial.printf("Error in HTTP request: %d\n", httpResponseCode);
    }

    http.end();  // Close connection
}

// Helper function to parse JSON and update the LVGL UI elements
void updateWeatherUI(const String &jsonData) {
    // Initialize a JSON document
    DynamicJsonDocument doc(2048);

    // Parse the JSON data
    DeserializationError error = deserializeJson(doc, jsonData);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    // Extract weather data
    float temp_c = doc["current"]["temp_c"];
    int humidity = doc["current"]["humidity"];
    const char* condition = doc["current"]["condition"]["text"];
    const char* wind_dir = doc["current"]["wind_dir"];
    int wind_degree = doc["current"]["wind_degree"];
    const char* last_updated = doc["current"]["last_updated"];
    float wind_kph = doc["current"]["wind_kph"];
    float pressure_mb = doc["current"]["pressure_mb"];
    float feelslike_c = doc["current"]["feelslike_c"];
    float heatindex_c = doc["current"]["heatindex_c"];
    float dewpoint_c = doc["current"]["dewpoint_c"];
    float uv = doc["current"]["uv"];

    lv_bar_set_value(ui_Bar_Temp, temp_c, LV_ANIM_ON); 
    lv_bar_set_value(ui_Bar_Hum, humidity, LV_ANIM_ON);
    lv_bar_set_value(ui_Bar_FL, feelslike_c, LV_ANIM_ON); 
    lv_bar_set_value(ui_Bar_HI, heatindex_c, LV_ANIM_ON); 

    // Format and update the temperature label (T:36°C)
    char tempStr[16];
    snprintf(tempStr, sizeof(tempStr), "T:%d°C", (int)round(temp_c));  // Round and cast to int for display
    lv_label_set_text(ui_Label_temp, tempStr);

    // Format and update the humidity label (H:47%)
    char humStr[16];
    snprintf(humStr, sizeof(humStr), "H:%d%%", humidity);
    lv_label_set_text(ui_Label_hum, humStr);

    // Update the condition label (Sunny, Rainy, etc.)
    lv_label_set_text(ui_Label_condition, condition);
    // Update wind direction label (N, NW, etc.)
    // lv_label_set_text(ui_Label_winddir, wind_dir);

    // Format and update the wind speed (e.g., 21.2 k/h)
    char windStr[16];
    snprintf(windStr, sizeof(windStr), "%.1fk/h", wind_kph);  // Show 1 decimal place
    lv_label_set_text(ui_Label_windkph, windStr);

    // Rotate the compass image based on the wind degree
    lv_img_set_angle(ui_Image_compass, wind_degree * 10);  // LVGL angle uses tenths of degrees

    // Update raw data to ui_TextArea_Data
    char rawData[256];
    snprintf(rawData, sizeof(rawData),
            "Last Updated: %s\n"
            "Wind: %.1f kph\n"
            "Direction: %s\n"  // Add wind direction here
            "Pressure: %.1f mb\n"
            "Feels Like: %.1f°C\n"
            "Heat Index: %.1f°C\n"
            "Dew Point: %.1f°C\n"
            "UV Index: %.1f",
            last_updated, wind_kph, wind_dir, pressure_mb, feelslike_c, heatindex_c, dewpoint_c, uv);
    lv_textarea_set_text(ui_TextArea_Data, rawData);
}
