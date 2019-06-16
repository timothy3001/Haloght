#ifndef LedSetup_h_
#define LedSetup_h_

#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <esp_system.h>

#include "../WebServerExtensions/WebServerExtensions.h"
#include "../web/LedSetup/PageLedSetupServerInvalidSettings.h"
#include "../web/LedSetup/PageLedSetupServerOk.h"
#include "../web/LedSetup/PageLedSetupServerRoot.h"

class LedSetup
{
public:
  static void setup();
  static void loadConfiguration();
  static int getNumLeds();
  static int getDataPin();
  static bool isConfigurationValid();

private:
  static void logDebug(String message);

  static void handleRoot(AsyncWebServerRequest *request);
  static void handlePostConfiguration(AsyncWebServerRequest *request);
  static bool validateAndReadSettings(AsyncWebServerRequest *request, int *dataPin, int *numLeds);

  static int numLeds;
  static int dataPin;
  static bool configurationValid;
  static bool doRestart;

  static const char *PREFERENCES_LEDSETUP;
  static const char *SETTING_LED_AMOUNT;
  static const char *SETTING_DATA_PIN;

  static AsyncWebServer *webServer;
};

#endif