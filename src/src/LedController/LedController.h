#ifndef LedController_h_
#define LedController_h_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "LedVisualization/LedVisualizationBase.h"
#include "LedVisualization/SolidColor/LedVisualizationSolidColor.h"

class LedController
{
public:
    LedController(int dataPin, int numLeds);
    ~LedController();
    void handle();

    void setSolidColor(uint8_t r, uint8_t g, uint8_t b);

private:
    static const uint8_t gamma8Correction[];

    int numLeds;
    int dataPin;

    LedVisualizationBase *currentVisualization = NULL;
    ulong nextCheck = 0;

    // This is not ideal. We got two representations of the LEDs. But this way it's easiest to have a seperation between LED library and animation logic.
    // The arrays might become quite large, for 150 pixels it is 150 (Pixels) * 3 (RGB) * 2 (currentedValues and strip). That is 900 bytes of memory. But
    // since the ESP32 has 520kb of RAM, we should be fine here.
    LedValue *currentLedValues;
    Adafruit_NeoPixel *strip;

    void logDebug(String message);
    void calculateRgbToRgbw(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *w);
    void setPixels();
};

#endif