#include "WeatherHelper.h"
#include "Config.h"
#include <HTTPClient.h>
#include <lvgl.h>
#include "ui.h"


extern lv_obj_t *ui_Label_temp;
extern lv_obj_t *ui_Label_hum;


void weatherTask(void *pvParameters) {
    Serial.println("Weather Task started");
    while (true) {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Fetching weather data...");
            fetchWeatherData();  // Fetch the weather data
        }
        vTaskDelay(300000 / portTICK_PERIOD_MS);  // Delay 5 minutes between weather fetches
    }
}


void fetchWeatherData() {
    String url = String("https://api.weatherapi.com/v1/current.json?key=") + API_KEY + "&q=" + LOCATION;

    HTTPClient http;
    http.begin(url);  // Specify the URL
    int httpResponseCode = http.GET();  // Send the request

    if (httpResponseCode > 0) {
        String response = http.getString();  // Get the response payload
        Serial.println(response);  // Print the response for debugging

        // Pass the JSON data to be parsed and used in the UI
        updateWeatherUI(response);
    } else {
        Serial.printf("Error in HTTP request: %d\n", httpResponseCode);
        if (httpResponseCode == -1) {
            Serial.println("Check your WiFi connection or API key.");
        }
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
    float feelslike_c = doc["current"]["feelslike_c"];
    float heatindex_c = doc["current"]["heatindex_c"];


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

}
