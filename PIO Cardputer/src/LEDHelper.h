#ifndef LEDHELPER_H
#define LEDHELPER_H

#include <Adafruit_NeoPixel.h>

// Define the pin and number of LEDs
#define PIN_LED 21
#define NUM_LEDS 1

// Enum for LED colors or effects
enum LedColor { RED, GREEN, BLUE };

// LED Helper class to manage NeoPixel
class LEDHelper {
public:
    LEDHelper();  // Constructor

    // Function to initialize the NeoPixel LED
    void begin();

    // Function to set the LED color
    void setLedColor(LedColor color);

    // Function to update the NeoPixel display (np.show)
    void updateLed();

private:
    Adafruit_NeoPixel np;  // NeoPixel object

    // Helper function to generate rainbow colors across 0-255 positions of the color wheel
    uint32_t Wheel(byte WheelPos);
};

#endif  // LEDHELPER_H
