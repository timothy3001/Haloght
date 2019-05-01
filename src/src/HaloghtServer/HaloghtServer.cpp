#include "HaloghtServer.h"

HaloghtServer::HaloghtServer(LedController *ledController)
{
    this->ledController = ledController;
    this->webServer = new WebServer(80);

    webServer->on("/", [&]() -> void { this->handleRoot(); });
    webServer->on("/setSolidColor", HTTP_POST, [&]() -> void { this->handleSetSolidColor(); });
    WebServerExtensions::registerBootstrap(*webServer);
    WebServerExtensions::registerNotFound(*webServer);

    webServer->begin();
}

HaloghtServer::~HaloghtServer()
{
    if (webServer)
        delete webServer;
}

void HaloghtServer::handleClient()
{
    webServer->handleClient();
}

void HaloghtServer::handleRoot()
{
    logDebug("Root called!");

    webServer->send(200, "text/html", pageHaloghtServerRoot);
}

void HaloghtServer::handleSetSolidColor()
{
    logDebug("SetSolidColor called!");

    String colorString = webServer->arg("color");
    if (colorString && colorString.length() == 7)
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        extractColorFromString(colorString, &red, &green, &blue);

        ledController->setSolidColor(red, green, blue);
        webServer->send(200, "text/plain", "OK");
    }
    else
    {
        webServer->send(400, "text/plain", "Wrong Format!");
    }
}

void HaloghtServer::extractColorFromString(String str, uint8_t *r, uint8_t *g, uint8_t *b)
{

    char color[8];
    str.toCharArray(color, 8);

    char redPart[3];
    char greenPart[3];
    char bluePart[3];

    strncpy(redPart, color + 1, 2);
    redPart[2] = 0;
    strncpy(greenPart, color + 3, 2);
    greenPart[2] = 0;
    strncpy(bluePart, color + 5, 2);
    bluePart[2] = 0;

    *r = strtol(redPart, NULL, 16);
    *g = strtol(greenPart, NULL, 16);
    *b = strtol(bluePart, NULL, 16);
}

void HaloghtServer::logDebug(String message)
{
#ifdef DEBUG
    Serial.print("HaloghtServer: ");
    Serial.println(message);
#endif
}