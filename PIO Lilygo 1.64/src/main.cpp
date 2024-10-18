#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include "Arduino_DriveBus_Library.h"
#include "pin_config.h"
#include <ui.h>

#include "WiFiHelper.h"
#include "WeatherHelper.h"

unsigned long lastBatteryCheck = 0;
const unsigned long batteryCheckInterval = 10000;  // Check battery every 10 seconds

unsigned long lastNTPTimeCheck = 0;
const unsigned long ntpTimeCheckInterval = 10000;  // 10 seconds interval for NTP check

unsigned long lastWeatherCheck = 0;
const unsigned long weatherCheckInterval = 300000;  // 5 minutes (300,000 ms)

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

Arduino_DataBus *bus = new Arduino_ESP32QSPI(
    LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_SDIO0 /* SDIO0 */, LCD_SDIO1 /* SDIO1 */,
    LCD_SDIO2 /* SDIO2 */, LCD_SDIO3 /* SDIO3 */);

Arduino_GFX *gfx = new Arduino_CO5300(bus, LCD_RST /* RST */,
                                      0 /* rotation */, false /* IPS */, LCD_WIDTH, LCD_HEIGHT,
                                      20 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

std::shared_ptr<Arduino_IIC_DriveBus> IIC_Bus =
    std::make_shared<Arduino_HWIIC>(IIC_SDA, IIC_SCL, &Wire);

void Arduino_IIC_Touch_Interrupt(void);

// Initialize the FT3168 touch controller object with the I2C bus and device address.
std::unique_ptr<Arduino_IIC> FT3168(new Arduino_FT3x68(IIC_Bus, FT3168_DEVICE_ADDRESS,
                                                       TP_RST, TP_INT, Arduino_IIC_Touch_Interrupt));

void Arduino_IIC_Touch_Interrupt(void)
{
    FT3168->IIC_Interrupt_Flag = true;
}

// Initialize the SY6970 charging controller object with the I2C bus and device address
std::unique_ptr<Arduino_IIC> SY6970(new Arduino_SY6970(IIC_Bus, SY6970_DEVICE_ADDRESS,
                                                       DRIVEBUS_DEFAULT_VALUE, DRIVEBUS_DEFAULT_VALUE));

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (FT3168->IIC_Interrupt_Flag == true)
    {
        FT3168->IIC_Interrupt_Flag = false;

        int32_t touch_x = FT3168->IIC_Read_Device_Value(FT3168->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_X);
        int32_t touch_y = FT3168->IIC_Read_Device_Value(FT3168->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_Y);
        uint8_t fingers_number = FT3168->IIC_Read_Device_Value(FT3168->Arduino_IIC_Touch::Value_Information::TOUCH_FINGER_NUMBER);

        if (fingers_number > 0)
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = touch_x;
            data->point.y = touch_y;
        }
        else
        {
            data->state = LV_INDEV_STATE_REL;
        }
    }
}

void my_rounder_cb(lv_disp_drv_t *disp_drv, lv_area_t *area)
{
    if (area->x1 % 2 != 0)
        area->x1 += 1;
    if (area->y1 % 2 != 0)
        area->y1 += 1;

    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    if (w % 2 != 0)
        area->x2 -= 1;
    if (h % 2 != 0)
        area->y2 -= 1;
}

// Assuming lv_obj_t pointers for each tab
lv_obj_t *ui_tab_time;
lv_obj_t *ui_tab_weather;
lv_obj_t *ui_tab_data;
lv_obj_t *tabview;

// Function to handle tab changes
void tab_change_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *tabview = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        uint16_t tab_index = lv_tabview_get_tab_act(tabview);
        
        // Clear previous animations to ensure they restart correctly
        lv_anim_del_all();  // This will delete all ongoing animations. Alternatively, you can delete animations for specific objects.

        switch (tab_index) {
            case 0: // ui_tab_time
                // Play walking animation for time tab
                walking_Animation(ui_Image_time, 0);
                break;

            case 1: // ui_tab_weather
                // Play walking animation for weather tab
                walking_Animation(ui_Image_time, 0);
                break;

            case 2: // ui_tab_data
                // Play thumbsup animation for data tab
                thumbsup_Animation(ui_Image_weather, 0);
                break;

            default:
                break;
        }
    }
}


void lvgl_initialization(void)
{
    lv_init();

    lv_color_t *buf_1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    lv_color_t *buf_2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    while ((!buf_1) || (!buf_2))
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        delay(1000);
    }

    lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, LCD_WIDTH * 40);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.rounder_cb = my_rounder_cb;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = 1; // Double-buffered full pixel refresh
    lv_disp_drv_register(&disp_drv);

    /*Initialize the input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // Initialize tabview and create tabs
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);
    ui_tab_time = lv_tabview_add_tab(tabview, "Time");
    ui_tab_weather = lv_tabview_add_tab(tabview, "Weather");
    ui_tab_data = lv_tabview_add_tab(tabview, "Data");

    // Attach the event handler to the tabview
    lv_obj_add_event_cb(tabview, tab_change_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

}

void setupSY6970();
void readBatteryStatus();
int getBatteryPercentage(float voltage);

int32_t battery_voltage;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting Setup...");

    pinMode(LCD_EN, OUTPUT);
    digitalWrite(LCD_EN, HIGH);

    if (FT3168->begin() == false)
    {
        Serial.println("FT3168 initialization failed");
        delay(2000);
    }
    else
    {
        Serial.println("FT3168 initialization successful");
    }

    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->Display_Brightness(255);

    lvgl_initialization();
    ui_init();  // Initialize the user interface

    setupSY6970();  // Initialize the SY6970 chip

    // Initial battery reading
    readBatteryStatus();

    walking_Animation(ui_Image_time, 0);
    walking_Animation(ui_Image_weather, 0);
    thumbsup_Animation(ui_Image_data, 0);

    setupWiFi();  // Connect to WiFi

    // Fetch and update weather data
    fetchWeatherData();
}

void loop() {
    lv_timer_handler();  // Efficiently handle LVGL tasks (non-blocking)

    // Periodically fetch time from NTP server (non-blocking)
    if (millis() - lastNTPTimeCheck >= ntpTimeCheckInterval) {
        fetchNTPTime();  // Fetch time every 10 seconds
        lastNTPTimeCheck = millis();  // Reset NTP time check timer
    }

    // Periodically update battery status without blocking the UI
    if (millis() - lastBatteryCheck >= batteryCheckInterval) {
        readBatteryStatus();  // Read battery voltage and charging status

        // Use the updated battery_voltage value to calculate the percentage
        int battery_percentage = getBatteryPercentage(battery_voltage / 1000.0);  // Convert to volts
        Serial.printf("Battery Percentage: %d%%\n", battery_percentage);

        // Update the battery bar UI with non-blocking animation
        lv_bar_set_value(ui_Bar_battery, battery_percentage, LV_ANIM_ON);  // Update the bar with animation

        lastBatteryCheck = millis();  // Reset the battery check timer
    }

    // Periodically fetch weather data and update UI
    if (millis() - lastWeatherCheck >= weatherCheckInterval) {
        fetchWeatherData();  // Fetch and update weather data every 10 minutes
        lastWeatherCheck = millis();  // Reset the weather check timer
    }
}

void setupSY6970() {
    Serial.println("Starting SY6970 initialization");

    while (!SY6970->begin()) {
        Serial.println("SY6970 initialization failed, retrying...");
        delay(2000);
    }
    Serial.println("SY6970 initialization successful");

    // Activate ADC Measurement
    while (!SY6970->IIC_Write_Device_State(SY6970->Arduino_IIC_Power::Device::POWER_DEVICE_ADC_MEASURE,
                                           SY6970->Arduino_IIC_Power::Device_State::POWER_DEVICE_ON)) {
        Serial.println("Failed to activate ADC Measurement, retrying...");
        delay(2000);
    }
    Serial.println("ADC Measurement activated successfully");
}

int voltageToPercentage(float voltage) {
    const float minVoltage = 3.0;  // Battery empty
    const float maxVoltage = 4.2;  // Battery fully charged
    const int hysteresisThreshold = 3;  // Slightly larger hysteresis threshold in percentage

    // Clamp the voltage to be within the expected range
    voltage = max(minVoltage, min(maxVoltage, voltage));

    // Define non-linear voltage to percentage relationship (approximate values)
    int percentage = 0;

    if (voltage <= 3.0) return 0;
    if (voltage >= 4.2) return 100;
    
    if (voltage < 3.5) {
        percentage = (int)((voltage - 3.0) / (3.5 - 3.0) * 10);  // 0% to 10%
    } else if (voltage < 3.7) {
        percentage = 10 + (int)((voltage - 3.5) / (3.7 - 3.5) * 30);  // 10% to 40%
    } else if (voltage < 3.9) {
        percentage = 40 + (int)((voltage - 3.7) / (3.9 - 3.7) * 20);  // 40% to 60%
    } else if (voltage < 4.0) {
        percentage = 60 + (int)((voltage - 3.9) / (4.0 - 3.9) * 20);  // 60% to 80%
    } else if (voltage < 4.1) {
        percentage = 80 + (int)((voltage - 4.0) / (4.1 - 4.0) * 10);  // 80% to 90%
    } else {
        percentage = 90 + (int)((voltage - 4.1) / (4.2 - 4.1) * 10);  // 90% to 100%
    }

    // Hysteresis: Only update if the percentage changes significantly (by more than hysteresisThreshold)
    static int lastPercentage = -1;
    static float lastVoltage = -1;

    // Check if voltage change is meaningful (e.g., more than 20 mV difference)
    if (lastVoltage == -1 || abs(voltage - lastVoltage) > 0.02 || abs(percentage - lastPercentage) > hysteresisThreshold) {
        lastPercentage = percentage;
        lastVoltage = voltage;  // Update voltage reference for future comparisons
    }

    return lastPercentage;
}

void readBatteryStatus() {
    // Read battery voltage from the device
    battery_voltage = SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_BATTERY_VOLTAGE);

    // Convert battery_voltage from mV to V
    float voltage = battery_voltage / 1000.0;

    // Calculate the battery percentage using the non-linear mapping
    int battery_percentage = voltageToPercentage(voltage);

    // Print out the battery percentage and voltage
    Serial.printf("Battery Voltage: %.2f V (%d mV), Battery Percentage: %d%%\n", voltage, battery_voltage, battery_percentage);

    // Update the battery bar in the UI
    lv_bar_set_value(ui_Bar_battery, battery_percentage, LV_ANIM_ON);
}


int getBatteryPercentage(float voltage) {
    const float minVoltage = 3.0;  // Battery empty
    const float maxVoltage = 4.2;  // Battery fully charged
    const int hysteresisThreshold = 2;  // Hysteresis threshold in percentage

    // Clamp the voltage to be within the expected range
    voltage = max(minVoltage, min(maxVoltage, voltage));

    // Calculate the battery percentage using linear interpolation
    int percentage = (int)((voltage - minVoltage) / (maxVoltage - minVoltage) * 100);

    // Hysteresis: Only update if the percentage changes significantly (by more than hysteresisThreshold)
    static int lastPercentage = -1;  // Ensure lastPercentage retains value between calls
    if (lastPercentage == -1 || abs(percentage - lastPercentage) > hysteresisThreshold) {
        lastPercentage = percentage;
    }

    return lastPercentage;
}

