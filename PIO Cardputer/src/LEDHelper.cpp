#include "LEDHelper.h"

// Constructor
LEDHelper::LEDHelper() : np(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800) {}

// Initialize the NeoPixel
void LEDHelper::begin() {
    np.begin();
    np.setBrightness(0);
}

// Set the LED color based on the enum
void LEDHelper::setLedColor(LedColor color) {
    switch (color) {
        case RED:
            np.setPixelColor(0, np.Color(255, 0, 0));  // Red color
            break;
        case GREEN:
            np.setPixelColor(0, np.Color(29, 135, 32));  // Green color
            break;
        case BLUE:
            np.setPixelColor(0, np.Color(35, 110, 213));  // Orange color
            break;
    }
    np.show();  // Update the LED after setting the color
}

// Update the NeoPixel LED (show the color)
void LEDHelper::updateLed() {
    np.show();  // Update the LED display with current color
}
