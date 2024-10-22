#include <M5Cardputer.h>  // Include M5Cardputer library for M5Stack-specific functionality
#include <lvgl.h>         // Include LVGL library
#include "ui.h"

#include "Config.h"       // Config file with external declarations
#include <SD.h>           // SD card library for reading config
#include <SPI.h>
#include <FS.h>

#include "WiFiHelper.h"
#include "WeatherHelper.h"

// Create buffers for LVGL display
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[240 * 10];  // Buffer size for 1/10th of screen (240 width)
static lv_color_t buf2[240 * 10];  // Second buffer for double buffering

// Function to set up the LVGL environment
void lvgl_setup() {
    // Initialize the LVGL library
    lv_init();

    // Initialize the display buffer with two buffers for smoother rendering
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, 240 * 10);

    // Set up the display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    // Flush callback to send rendered buffer to the M5Cardputer display
    disp_drv.flush_cb = [](lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
        uint32_t w = area->x2 - area->x1 + 1;
        uint32_t h = area->y2 - area->y1 + 1;

        M5.Display.startWrite();
        M5.Display.setAddrWindow(area->x1, area->y1, w, h);
        M5.Display.pushColors((uint16_t *)&color_p->full, w * h, true);
        M5.Display.endWrite();

        lv_disp_flush_ready(disp_drv);  // Inform LVGL that flushing is done
    };

    // Set the screen resolution
    disp_drv.hor_res = 240;  // Horizontal resolution
    disp_drv.ver_res = 135;  // Vertical resolution
    disp_drv.draw_buf = &draw_buf;

    // Register the display driver
    lv_disp_drv_register(&disp_drv);
}

// SD card pins
#define SD_SCK 40
#define SD_MISO 39
#define SD_MOSI 14
#define SD_SS 12
#define SD_SPI_FREQ 1000000  // Example frequency, adjust as needed

SPIClass *hspi = new SPIClass(HSPI);  // SPI for SD card

// Global variables for configuration
String WIFI_SSID = "";
String WIFI_PASSWORD = "";
String TIME_ZONE = "";
String API_KEY = "";
String LOCATION = "";

// Global variable to store the current LCD brightness
int currentBrightness = 128;  // Initialize brightness to half (range 0-255)

// Declare global variables for NTP and weather checks
unsigned long lastNTPTimeCheck = 0;  // To track when NTP was last checked
const unsigned long ntpTimeCheckInterval = 10000;  // 10 seconds interval for NTP time check

// Global variables for tab views
lv_obj_t *ui_tabview;
lv_obj_t *ui_tab_data;
lv_obj_t *ui_tab_stat;

// Function prototypes for controlling the green LED and stopping the LED
void blinkGreenLED();
void stopLED();
void connectToWiFi();
void loadConfigFromSD();
bool initializeSDCard();

// Global variables to track data fetch status
static bool weatherFetched = false;
static bool ntpFetched = false;

// Function to update the battery level bar based on the current battery voltage
void updateBatteryBar() {
    // Get the current battery voltage
    float batteryVoltage = M5.Power.getBatteryVoltage() / 1000.0; // Convert mV to V

    // Normalize the battery voltage to a percentage (assume 3.2V - 4.2V is 0% - 100%)
    int batteryPercentage = (int)(((batteryVoltage - 3.3) / (4.2 - 3.3)) * 100);
    
    // Ensure the battery percentage is within 0-100 range
    batteryPercentage = constrain(batteryPercentage, 0, 100);

    // Update the LVGL battery bar UI with the new value
    lv_bar_set_value(ui_Bar_battery, batteryPercentage, LV_ANIM_ON);

   // Serial debug output
    Serial.print("Battery Voltage: ");
    Serial.print(batteryVoltage, 2);  // Print voltage in volts with 2 decimal places
    Serial.print("V, Battery Percentage: ");
    Serial.print(batteryPercentage);
    Serial.println("%");
}


void batteryTask(void *pvParameters) {
    while (true) {
        // Update the battery bar every 10 seconds
        updateBatteryBar();  // Your existing function to update the battery bar
        vTaskDelay(10000 / portTICK_PERIOD_MS);  // Delay 10 seconds between updates
    }
}

// Tick handler function for LVGL (called every 10ms)
void lv_tick_task(void *arg) {
    while (1) {
        lv_tick_inc(10);  // Increment LVGL tick by 10ms
        vTaskDelay(pdMS_TO_TICKS(10));  // Delay 10ms
    }
}

void setup() {
    // Initialize M5Cardputer hardware
    Serial.begin(115200);
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    cfg.serial_baudrate = 115200;  // Set serial baud rate
    M5.begin(cfg);

    if (!initializeSDCard()) {
        Serial.println("Failed to initialize SD card");
        return;
    }

    loadConfigFromSD();  // Load config from SD card

    // Output loaded configuration values
    Serial.println("WiFi SSID: " + WIFI_SSID);
    Serial.println("WiFi Password: " + WIFI_PASSWORD);
    Serial.println("Time Zone: " + TIME_ZONE);
    Serial.println("API Key: " + API_KEY);
    Serial.println("Location: " + LOCATION);

    // Set the initial brightness
    M5.Lcd.setBrightness(currentBrightness);  // Set initial brightness to half (128)

    // Initialize LVGL and the display setup
    lvgl_setup();

    ui_init();

    walking_Animation(ui_Img_stat, 0);
    thumpsup_Animation(ui_Img_data, 0);

    // Create FreeRTOS tasks for WiFi, Weather, and Battery in the background
    xTaskCreatePinnedToCore(wifiTask, "wifiTask", 4096, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(batteryTask, "batteryTask", 4096, NULL, 1, NULL, 1);

    // Create a FreeRTOS task for handling LVGL ticks
    xTaskCreatePinnedToCore(lv_tick_task, "lv_tick_task", 4096, NULL, 5, NULL, 1);
}

void loop() {
    // Handle LVGL tasks (this should be called regularly to update the screen)
    lv_timer_handler();
    delay(5);  // Small delay to prevent overloading the CPU

    // Periodically fetch time from NTP server (non-blocking)
    if (millis() - lastNTPTimeCheck >= ntpTimeCheckInterval) {
        fetchNTPTime();  // Fetch time every 10 seconds
        lastNTPTimeCheck = millis();  // Reset NTP time check timer
    }

    // Handle keyboard input for changing LCD brightness and LVGL tab views
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            // Get the current state of the keys
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            // Loop through the word vector to check for the pressed keys
            for (char key : status.word) {
                // If "/" key is pressed, switch to ui_tab_data
                if (key == '/') {
                    lv_tabview_set_act(ui_Tab_main, 1, LV_ANIM_ON);  // Switch to ui_tab_data (index 1)
                    M5Cardputer.Speaker.tone(4000, 100);
                }
                // If "," key is pressed, switch to ui_tab_stat
                if (key == ',') {
                    lv_tabview_set_act(ui_Tab_main, 0, LV_ANIM_ON);  // Switch to ui_tab_stat (index 0)
                    M5Cardputer.Speaker.tone(4000, 100);
                }

                // Adjust LCD brightness using ';' and '.'
                if (key == ';') {  // Increase brightness
                    currentBrightness = constrain(currentBrightness + 25, 0, 255);  // Increase by 25, max 255
                    M5.Lcd.setBrightness(currentBrightness);  // Update LCD brightness
                    Serial.printf("Brightness increased to: %d\n", currentBrightness);
                    M5Cardputer.Speaker.tone(4000, 100);
                }
                if (key == '.') {  // Decrease brightness
                    currentBrightness = constrain(currentBrightness - 25, 0, 255);  // Decrease by 25, min 0
                    M5.Lcd.setBrightness(currentBrightness);  // Update LCD brightness
                    Serial.printf("Brightness decreased to: %d\n", currentBrightness);
                    M5Cardputer.Speaker.tone(4000, 100);
                }
            }
        }
    }

    M5Cardputer.update();  // Update the M5Stack system
}

// Function to initialize SD card
bool initializeSDCard() {
    hspi->begin(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
    if (!SD.begin(SD_SS, *hspi, SD_SPI_FREQ)) {
        Serial.println("SD card initialization failed");
        return false;
    }
    Serial.println("SD card initialized successfully");
    return true;
}


// Function to load configuration from SD card
void loadConfigFromSD() {
    File configFile = SD.open("/config.txt", FILE_READ);
    if (!configFile) {
        Serial.println("Failed to open config file");
        return;
    }

    char line[128];  // Buffer to store each line
    while (configFile.available()) {
        memset(line, 0, sizeof(line));
        configFile.readBytesUntil('\n', line, sizeof(line) - 1);
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\r\n");

        if (key && value) {
            if (strcmp(key, "WIFI_SSID") == 0) WIFI_SSID = String(value);
            else if (strcmp(key, "WIFI_PASSWORD") == 0) WIFI_PASSWORD = String(value);
            else if (strcmp(key, "TIME_ZONE") == 0) TIME_ZONE = String(value);
            else if (strcmp(key, "API_KEY") == 0) API_KEY = String(value);
            else if (strcmp(key, "LOCATION") == 0) LOCATION = String(value);
        }
    }
    configFile.close();
    Serial.println("Configuration loaded from SD card.");
}